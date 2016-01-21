#include "stdafx.h"
#include "PhysxSpace.h"
#include "PhysxObject.h"
#include "PhysxSide.h"
#include "PhysxBox.h"


PhysxSpace::PhysxSpace(const std::string& name): Widget(name)
{
	PhysxObject::space = this;
	nObjects = 0;
}

PhysxSpace::~PhysxSpace()
{
	PhysxObject::space = 0;
}
void PhysxSpace::Draw()
{
	_effCont.Draw();
	Render::BindFont("default");
	Render::PrintString(900 + 100 / 2, 15,  "PhysxObjects: " + utils::lexical_cast(nObjects), 0.8f, CenterAlign);
}

void PhysxSpace::setGravity(FPoint Gravity)
{
	_gravity = Gravity;
}

#define PAIR(a,b) (((w1->_body == a) && ( w2->_body == b)) || ((w1->_body == b) && ( w2->_body == a)))
bool PhysxSpace::colisionCheck(PhysxObject *w1, PhysxObject *w2)
{
	math::Vector3 vC;
	math::Vector3 vC1(0,0,0);
	if ((w1->_body == PhysxObject::BODY_CIRCLE) && ( w2->_body == PhysxObject::BODY_CIRCLE))
	{
		vC = math::Vector3(PointToVector(w1->_fPosition - w2->_fPosition)).Normalized();
	}
	//else if ((w1->_body == PhysxObject::BODY_BOX) && (w2->_body == PhysxObject::BODY_BOX))
	//{
	//	vC = math::Vector3(1,0,0).Normalized();
	//	vC1 = math::Vector3(0, 1, 0).Normalized();
	//}
	else if PAIR(PhysxObject::BODY_SIDE,PhysxObject::BODY_CIRCLE)	
		//(((w1->_body == PhysxObject::BODY_SIDE) && ( w2->_body == PhysxObject::BODY_CIRCLE)) || ((w1->_body == PhysxObject::BODY_CIRCLE) && ( w2->_body == PhysxObject::BODY_SIDE)))
	{
		PhysxSide *p;
		if (w1->_body == PhysxObject::BODY_SIDE)
			p = static_cast<PhysxSide*>(w1);
		else
			p = static_cast<PhysxSide*>(w2);


		vC = PointToVector(p->_fDirection);
	}
	else  if PAIR(PhysxObject::BODY_SIDE,PhysxObject::BODY_BOX)
		//(((w1->_body == PhysxObject::BODY_SIDE) && ( w2->_body == PhysxObject::BODY_BOX)) || ((w1->_body == PhysxObject::BODY_BOX) && ( w2->_body == PhysxObject::BODY_SIDE))) 
	{
		PhysxSide *p;
		if (w1->_body == PhysxObject::BODY_SIDE)
			p = static_cast<PhysxSide*>(w1);
		else
			p = static_cast<PhysxSide*>(w2);


		vC = PointToVector(p->_fDirection);
	}
	else if (PAIR(PhysxObject::BODY_CIRCLE,PhysxObject::BODY_BOX) || ((w1->_body == PhysxObject::BODY_BOX) && (w2->_body == PhysxObject::BODY_BOX)))
	
	{
		PhysxBox *p;

		if (w1->_body == PhysxObject::BODY_BOX)
			p = static_cast<PhysxBox*>(w1);
		else
			p = static_cast<PhysxBox*>(w2);

		math::Vector3 vC[3];

		//упрощенный вариант стороны параллельны или перпендикул€рны ос€м координат
		vC[0] = math::Vector3(0,1,0).Normalized();
		vC[1] = math::Vector3(1,0,0).Normalized();

		vC[2] = math::Vector3(PointToVector(w1->_fPosition - w2->_fPosition)).Normalized();


		float _a1,b1,_a2,b2,  r1,r2, r;
		float deep;
		int rI = 0;

		for (int i = 0;i<3;  i++)
		{
			w1->getProjecToVector(&vC[i], &_a1, &b1);
			w2->getProjecToVector(&vC[i], &_a2, &b2);
			r1 = b1 - _a2;
			r2 =_a1 - b2;
			r = r1 * r2;

			if (r<0)
			{
				if (i == 0)
					deep = math::min(math::abs(r1), math::abs(r2));
				else
				{
					float tDeep = math::min(math::abs(r1), math::abs(r2));
					if (tDeep > math::abs(deep))
						continue;
					else
					{
						rI = i;
						deep = tDeep;
					}
				}

				if (math::abs(r1)>math::abs(r2))
					deep *= -1;
			}
			else
				//если хот€ бы на одной проекции нет пересечени€ то стокновени€ нет  
				return false;
		}


		w1->colision(vC[rI], deep, w2);
		w2->colision(vC[rI], -deep, w1);
		return false;
	}	
	else
		return false;

	float _a1,b1,_a2,b2;
	w1->getProjecToVector(&vC, &_a1, &b1);
	w2->getProjecToVector(&vC, &_a2, &b2);
	float r1 = b1 - _a2;
	float r2 =_a1 - b2;
	float r = r1 * r2;

	if (r<0)
	{
		float deep = math::min(math::abs(r1), math::abs(r2));
		if (math::abs(r1)>math::abs(r2))
			deep *= -1;
		w1->colision(vC, deep, w2);
		w2->colision(vC, -deep, w1);
	}

	return false;
}


void PhysxSpace::Update(float dt)
{
	_effCont.Update(dt);
	
	WidgetContainer& childs = this->getChildren();

	//поиск столкновении
	for(WidgetIterator iter = childs.begin(); iter != childs.end(); iter++)
	{

		
		PhysxObject *p = static_cast<PhysxObject*>(iter->get());

		if (p->_useGravity)
			p->_speed += _gravity * dt;

		for(WidgetIterator iter2 = iter+1; iter2 != childs.end(); iter2++)
		{
			PhysxObject *p2 = static_cast<PhysxObject*>(iter2->get());

			if ((p->_delete == true) || (p2->_delete == true))
				continue;

			//if ((!(p->_role == PhysxObject::ROLE_TARGET && p2->_role == PhysxObject::ROLE_TARGET)))// && (!(!p->_isTarget && !p2->_isTarget)))
				colisionCheck(p, p2);	
		}
	}


	//удаление объектов
	for(WidgetIterator iter = childs.begin(); iter != childs.end(); iter++)
	{
		PhysxObject *p = static_cast<PhysxObject*>(iter->get());


		if (p->_delete)
		{
			p->_isVisible  = false;
			childs.erase(iter);
			break;
		}
	}
}


