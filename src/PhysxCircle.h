#pragma once

#include "PhysxObject.h"

class PhysxCircle : public PhysxObject
{
	friend class PhysxSpace;
public:
	PhysxCircle(const std::string& name);

private:
	void getProjecToVector(math::Vector3 *vC, float *a, float *b);

protected:
	void colision(math::Vector3 vNormal, float deep, PhysxObject* obj);

protected:
	float _radius;
};
