#pragma once

#include  "PhysxSide.h"

class Border : public PhysxSide
{
public:
	Border(FPoint position, FPoint direction);

	void Draw();

protected:
	void colision(math::Vector3 vNormal, float deep, PhysxObject* obj);
};
