#pragma once

#include "PhysxObject.h"


class PhysxSide : public PhysxObject
{
	friend class PhysxSpace;
public:
	PhysxSide(const std::string& name, FPoint position, FPoint direction);

private:
	void getProjecToVector(math::Vector3 *vC, float *a, float *b);

protected:
	void colision(math::Vector3 vNormal, float deep, PhysxObject* obj);

protected:

	FPoint _fDirection;
};
