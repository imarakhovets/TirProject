#include "stdafx.h"
#include "PhysxSide.h"


PhysxSide::PhysxSide(const std::string& name, FPoint Position, FPoint Direction)
: PhysxObject(name),_fDirection(Direction)
{
	_fPosition = Position;
	_body = BODY_SIDE;	
}


void PhysxSide::getProjecToVector(math::Vector3 *vC, float *a, float *b)
{
	//math::Vector3 vector =  vC;
	*a = vC->DotProduct(PointToVector(_fPosition));
	*b = vC->DotProduct(PointToVector(_fPosition - _fDirection * 200));
}

void PhysxSide::colision(math::Vector3 vNormal, float deep, PhysxObject* obj)
{
	PhysxObject::colision(vNormal, deep, obj);
}

