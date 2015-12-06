#include "stdafx.h"
#include "Target.h"
#include "TirSpace.h"


Target::Target(const std::string& name, FPoint Position, FPoint Speed)
	: PhysxCircle(name)
{
	Init();

	_speed = Speed;
	_fPosition = Position;
}

void Target::Init()
{
	_tex1 = Core::resourceManager. Get<Render::Texture>("Target");
	hWidth = _tex1->getBitmapRect().width/2;
	hHeight = _tex1->getBitmapRect().height/2;

	_role = ROLE_TARGET;
	_radius = 46;
	_mass = 1.0;
}

void Target::Draw() 
{
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(math::Vector3(_fPosition.x - hWidth, _fPosition.y - hHeight, 0));

	if (_speed.x<0)
	{
		Render::device.MatrixTranslate(math::Vector3( hWidth,   hHeight, 0));
		Render::device.MatrixRotate(math::Vector3(0, 1, 0), 180);
		Render::device.MatrixTranslate(math::Vector3(- hWidth,  - hHeight, 0));
	}
	_tex1->Draw();
	Render::device.PopMatrix();
}

void Target::colision(math::Vector3 vNormal, float deep, PhysxObject* obj)
{
	if (this->_delete) return;

	if (obj->_role == ROLE_BORDER)
		PhysxCircle::colision(vNormal, deep, obj);
	else
		if (obj->_role == ROLE_BULLET)
		{
			//_eff =  space->_effCont.AddEffect("FindItem");
			_eff =  space->_effCont.AddEffect("FindCoin2");
			_eff->SetPos(this->_fPosition);
			_eff->Reset();

			MM::manager.PlaySample("Boom");
			this->_delete = true;

			TirSpace* tirSpace =  static_cast<TirSpace*>(space);
			tirSpace->_gameTargets--;
		}
}