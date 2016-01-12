#include "stdafx.h"
#include "Billboard.h"

Billboard::Billboard(FPoint startPosition, FPoint Speed, int nTarget, int nHit)
	: PhysxBox("Billboard",105,65)
{
	_fPosition = startPosition;
	_nHit = nHit;
	_nTarget = nTarget;
	_speed = Speed;
	Init();
}
void Billboard::Init()
{
	_tex1 = Core::resourceManager.Get<Render::Texture>("Billboard");
	_tex2 = Core::resourceManager.Get<Render::Texture>("Target");
	hWidth = _tex1->getBitmapRect().width/2;
	hHeight = _tex1->getBitmapRect().height/2;
	_timer = 0;
	_mass = 5.0;
	_role = ROLE_BILLBOARD;
}

void Billboard::Draw() 
{
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(math::Vector3(_fPosition.x - hWidth, _fPosition.y - hHeight, 0));
	_tex1->Draw();
	_tex2->Draw(IPoint(15,15));
	Render::BindFont("default");
	Render::PrintString(160, 50, utils::lexical_cast(_nHit) + "/" + utils::lexical_cast(_nTarget), 1.5f, CenterAlign);
	Render::device.PopMatrix();
}

void Billboard::colision(math::Vector3 vNormal, float deep, PhysxObject* obj)
{
	if (obj->_role == ROLE_BORDER)
		PhysxBox::colision(vNormal, deep, obj);
	else if ((obj->_role == ROLE_BULLET))
	{
		MM::manager.PlaySample("Rikoshet");
		//PhysxBox::colision(vNormal, deep, obj);
	} 
}

void Billboard::Update(float dt)
{
	PhysxObject::Update(dt);

	_timer += dt;

	if ((_timer > 6.2) && (_timer < 7))
		setSpeed();
}


