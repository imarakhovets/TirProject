#pragma once

//#include "PhysxObject.h"
#include "PhysxCircle.h"

///
/// ������ - �������� ���������� ������� �� ������.
/// �� ������������ ����, � ����� ����� ��������� ������ �������.
///


class Target : public PhysxCircle //PhysxObject
{
public:
	Target(const std::string& name, FPoint Position, FPoint Speed);

	void Draw();

private:
	void Init();
	virtual void colision(math::Vector3 vNormal, float deep, PhysxObject* obj);

private:
	Render::Texture *_tex1;
	float hWidth; 
	float hHeight; 

	
	ParticleEffectPtr _eff;
};
