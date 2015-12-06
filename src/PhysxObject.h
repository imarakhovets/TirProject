#pragma once

#include "PhysxSpace.h"

class PhysxObject : public GUI::Widget
{
	friend class PhysxSpace;

public:
	PhysxObject(const std::string& name);
	~PhysxObject();

	void Update(float dt);
	void setSpeed(IPoint Speed  = IPoint(0,0));
	void setPosition(IPoint Position);
	void setTimeLive(float Time);
	void destroy();


public:
	enum ROLE
	{
		ROLE_TARGET,
		ROLE_BULLET,
		ROLE_BORDER,
		ROLE_BILLBOARD,
		ROLE_NONE
	} _role;

	enum BODY
	{
		BODY_CIRCLE,
		BODY_BOX,
		BODY_SIDE,
		BODY_NONE
	} _body;

private:
	virtual void getProjecToVector(math::Vector3 *vC, float *a, float *b) = 0;

protected:
	virtual void colision(math::Vector3 vNormal, float deep, PhysxObject* obj);

protected:
	FPoint _fPosition;
	FPoint _lastSpeed;
	FPoint _speed;
	bool _useGravity;

	bool _autoDelete;
	float _timeLive;
	bool _delete;
	float _mass;
	
	static PhysxSpace* space;
};
