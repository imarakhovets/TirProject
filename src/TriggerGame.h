#pragma once


#include  "PhysxBox.h"

class TriggerGame : public PhysxBox
{
public:
	TriggerGame(FPoint startPosition, FPoint Speed, bool isRestart);
	void Draw();
	void Update(float dt);

protected:
	void colision(math::Vector3 vNormal, float deep, PhysxObject* obj);
private:
	void Init();
	

private:
	float _timer;


	float hWidth; 
	float hHeight; 
	bool _isRestart;

};
