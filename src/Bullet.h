#pragma once


#include  "PhysxCircle.h"

class Bullet : public PhysxCircle
{
public:
	explicit Bullet(FPoint startPosition, FPoint Speed);
	
   ~Bullet();
	void Draw();
	void Update(float dt);

protected:
	void colision(math::Vector3 vNormal, float deep, PhysxObject* obj);
private:
	void Init();
	

private:
	float _timer;
	Render::Texture *_tex1;
	float hWidth; 
	float hHeight; 

	ParticleEffectPtr _eff;
};
