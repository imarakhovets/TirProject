#pragma once

class PhysxObject;
class PhysxSide;

class PhysxSpace : public GUI::Widget
{
public:
	PhysxSpace(const std::string& name);
	~PhysxSpace();
    bool colisionCheck(PhysxObject *w1, PhysxObject *w2);

	void setGravity(FPoint Gravity);

	void Draw();
	

	void Update(float dt);
	int nObjects;

	EffectsContainer _effCont;

private :
	FPoint _gravity;
};
