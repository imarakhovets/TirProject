#include "stdafx.h"
#include "PhysxObject.h"

PhysxSpace* PhysxObject::space;

PhysxObject::PhysxObject(const std::string& name)
	: Widget(name),_delete(false),_useGravity(false),_autoDelete(false)
{
	if (space!=0)
	{
		space->AddChild(this);
		space->nObjects++;
	}

	setStatic(true);

	_role = ROLE_NONE;
	_body = BODY_NONE;
}

void PhysxObject::setTimeLive(float Time)
{
	_autoDelete = true;
	_timeLive = Time;
}

void PhysxObject::destroy()
{
	_autoDelete = false;
	_delete = true;
}

void PhysxObject::colision(math::Vector3 vNormal, float deep, PhysxObject* obj)
{
	//выдавливание из колизии
	_fPosition += FPoint(vNormal.x,vNormal.y) * deep/2;

	float a1 = vNormal.DotProduct(PointToVector(_lastSpeed));
	float a2 = vNormal.DotProduct(PointToVector(obj->_lastSpeed));
	float optimizedP = (2.0 * (a1 - a2))/(_mass + obj->_mass);

	math::Vector3 nSpeed1 = math::Vector3(PointToVector(_lastSpeed)) - optimizedP * obj->_mass * vNormal;
//	math::Vector3 nSpeed2 = math::Vector3(w2->_lastSpeed) + optimizedP * w1->_mass * vC;

	_speed = FPoint(nSpeed1.x,nSpeed1.y);
	//w2->_speed = FPoint(nSpeed2.x,nSpeed2.y);
}


void PhysxObject::setSpeed(IPoint Speed)
{
	_speed = Speed;
}

void PhysxObject::setPosition(IPoint Position)
{
	_fPosition = Position;
}


void PhysxObject::Update(float dt)
{
	_lastSpeed  = _speed;
	_fPosition += _speed * dt;

	if (_autoDelete)
	{
		if (_timeLive>0)
			_timeLive -=dt;
		else
			destroy();
	}
}


PhysxObject::~PhysxObject()
{
	if (space!=0)
		space->nObjects--;
}
