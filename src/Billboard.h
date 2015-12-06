#pragma once

#include  "PhysxBox.h"

class Billboard : public PhysxBox
{
public:
	Billboard(FPoint startPosition, FPoint Speed, int nTarget, int nHit);

	void Draw();
	void Update(float dt);

protected:
	void colision(math::Vector3 vNormal, float deep, PhysxObject* obj);
private:
	void Init();
	

private:
	float _timer;
	int _nHit;
	int _nTarget;
	Render::Texture *_tex1;
	Render::Texture *_tex2;
	float hWidth; 
	float hHeight; 
};
