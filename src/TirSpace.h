#pragma once


#include "PhysxSpace.h"
#include "Gun.h"

class PhysxObject;
class Border;

class TirSpace : public PhysxSpace
{
	friend class Target;

public:
	TirSpace(const std::string& name, rapidxml::xml_node<>* elem);

	void resetLevel();
	void Update(float dt);
	void Draw();

private:
	void resetTarget();
	void endLevel();

	bool _gameActive;
	float _levelEndTimer;

	int _gameTargets;
	float _gameTimer;
	int _gunBulletSpeed;

	int _cGameTargets;
	float _cGameTimer;
	bool _reset;

	Render::Texture *_back;

	Border *_left;
	Border *_right;
};
