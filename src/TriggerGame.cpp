#include "stdafx.h"
#include "TriggerGame.h"
#include "TirSpace.h"

TriggerGame::TriggerGame(FPoint startPosition, FPoint Speed, bool isRestart)
: PhysxBox("TriggerGame",45,10)
{
	_fPosition = startPosition;
	_isRestart = isRestart;
	_speed = Speed;
	Init();
}
void TriggerGame::Init()
{
	_timer = 0;
	_mass = 1.0;
	_role = ROLE_BILLBOARD;
}

void TriggerGame::Draw() 
{
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(math::Vector3(_fPosition.x, _fPosition.y, 0));

	Render::BindFont("default");
	if (_isRestart)
		Render::PrintString(0, 0,  "RESTART", 1.5f, CenterAlign);
	else
		Render::PrintString(0, 0,  "EXIT", 1.5f, CenterAlign);
	Render::device.PopMatrix();
}


void TriggerGame::colision(math::Vector3 vNormal, float deep, PhysxObject* obj)
{
	if (obj->_role == ROLE_BORDER)
		PhysxBox::colision(vNormal, deep, obj);
	else if ((obj->_role == ROLE_BULLET))
	{
		ParticleEffectPtr _eff = space->_effCont.AddEffect("FindCoin2");
		_eff->SetPos(this->_fPosition);
		_eff->Reset();
		MM::manager.PlaySample("Boom");
		this->_delete = true;

		if (_isRestart)
		{
			TirSpace* tir = (TirSpace*)space;
			tir->resetLevel();
		}
		else
			Core::appInstance->Stop();
	}
}

void TriggerGame::Update(float dt)
{
	PhysxObject::Update(dt);

	_timer += dt;

	if ((_timer > 6.2) && (_timer < 7))
		setSpeed();
}


