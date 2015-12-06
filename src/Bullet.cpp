#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(FPoint startPosition, FPoint Speed)
	: PhysxCircle("Bullet")
{
	_fPosition = startPosition;

	_speed = Speed;
	Init();
}
void Bullet::Init()
{
	_tex1 = Core::resourceManager.Get<Render::Texture>("Kernel");
	hWidth = _tex1->getBitmapRect().width/2;
	hHeight = _tex1->getBitmapRect().height/2;

	_useGravity = true;

	_timer = 0;
	_role = ROLE_BULLET;
	_radius = 9;
	_mass = 0.01;

	setTimeLive(4);

	_eff = space->_effCont.AddEffect("Iskra2");
	_eff->SetPos(_fPosition);
	_eff->Reset();
}

void Bullet::Draw() 
{
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(math::Vector3(_fPosition.x - hWidth, _fPosition.y - hHeight, 0));
	_tex1->Draw();
	Render::device.PopMatrix();
}

void Bullet::colision(math::Vector3 vNormal, float deep, PhysxObject* obj)
{
	if (obj->_role == ROLE_TARGET)
	{
		this->_delete = true;
	}
	else if (obj->_role == ROLE_BILLBOARD)
		PhysxCircle::colision(vNormal, deep, obj);
}

void Bullet::Update(float dt)
{
	PhysxObject::Update(dt);
	_eff->SetPos(_fPosition);
}


Bullet::~Bullet()
{
	_eff->Finish();
}

