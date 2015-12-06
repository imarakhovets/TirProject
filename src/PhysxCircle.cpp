#include "stdafx.h"
#include "PhysxCircle.h"


PhysxCircle::PhysxCircle(const std::string& name)
	: PhysxObject(name)
{
	_body = BODY_CIRCLE;
}

void PhysxCircle::getProjecToVector(math::Vector3 *vC, float *a, float *b)
{
	/*math::Vector3 center = _fPosition;
	math::Vector3 vector =  vC;
	float cProject = vector.DotProduct(center);*/

	float cProject = vC->DotProduct(PointToVector(_fPosition));
	*a = cProject + _radius;
	*b = cProject - _radius;
}

void PhysxCircle::colision(math::Vector3 vNormal, float deep, PhysxObject* obj)
{
	PhysxObject::colision(vNormal, deep, obj);
}

