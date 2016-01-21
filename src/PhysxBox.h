#pragma once

#include "PhysxObject.h"

class PhysxBox : public PhysxObject
{
	friend class PhysxSpace;
public:
	PhysxBox(const std::string& name, int hWidth, int hHeight);
	PhysxBox(const std::string& name);
	~PhysxBox();

private:
	void getProjecToVector(math::Vector3 *vC, float *a, float *b);

protected:
	void colision(math::Vector3 vNormal, float deep, PhysxObject* obj);

protected:
	int  _hWidth;
	int _hHeight;
};
