#include "stdafx.h"
#include "Gun.h"
#include "Bullet.h"

Gun::Gun(const std::string& name)
: Widget(name)
, _timer(0)
, _angle(0)
, _scale(0.f)
{
	Init();
}

Gun::Gun(const std::string& name, rapidxml::xml_node<>* elem)
: Widget(name)
, _timer(0)
, _angle(0)
, _scale(0.f)
{
	Init();
}

void Gun::Init()
{
	_tex1 = Core::resourceManager.Get<Render::Texture>("Muzzle");
	_tex2 = Core::resourceManager.Get<Render::Texture>("Gun");

	_angle = 0;
	setStatic(false);
	int width = _tex2->getBitmapRect().width;
	int height = _tex2->getBitmapRect().height;


	position.x = (Render::device.Width()-width)/2;
	baseOffsetPos.x = width/2;
	baseOffsetPos.y = 23;
	setClientRect(IRect(position.x,position.y,width,height));

	_rollback = 25;
	_rollbackNorm = 0;

	_timerShut = 0.0;
}

void Gun::Draw() 
{
	IPoint mouse_pos =  Core::mainInput.GetMousePos();

	Render::device.PushMatrix();

	Render::device.MatrixTranslate(math::Vector3((float)position.x, (float)position.y, 0));

	Render::device.MatrixTranslate(math::Vector3((float)baseOffsetPos.x, (float)baseOffsetPos.y, 0));
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), 180.0/math::PI * _angle);
	Render::device.MatrixTranslate(math::Vector3(-(float)baseOffsetPos.x, -(float)baseOffsetPos.y, 0));

	Render::device.MatrixTranslate(math::Vector3(0, -_rollback, 0));
	_tex1->Draw();
	Render::device.MatrixTranslate(math::Vector3(0, _rollback, 0));

	_tex2->Draw();
	Render::device.PopMatrix();
}

void Gun::Update(float dt)
{

	//стрельба
	if ((bulletSpeed > 0) && ((_timer>0.1) && (_timerShut<=0) && (Core::mainInput.GetMouseLeftButton())))
	{ 
		_timerShut = 1.2;
		//MM::manager.PlaySample("Shot");
		_bulletSpeed = bulletSpeed;
	}

	if (_timerShut>0)
	{
		_timerShut-=dt;
		if (_timerShut<=0)
		{
			_timer = 0;
			float y = math::sin(_angle + math::PI/2);
			float x = math::cos(_angle + math::PI/2);
			math::Vector3 _direct3(x,y,0);


			new Bullet(position + baseOffsetPos + FPoint(_direct3.x * 110,_direct3.y * 110).Rounded(), FPoint(_direct3.x,_direct3.y)*_bulletSpeed);
			//else
			//	MM::manager.FadeSample(_soundShut,0.5,0);
			_rollback = 25;
		}
	}

	_rollback = math::lerp(_rollback, _rollbackNorm, dt * 5);

	//вращение
	IPoint mouse_pos =  Core::mainInput.GetMousePos();

	IPoint direct =  mouse_pos - (position + baseOffsetPos);
	float angle = -math::atan(direct.x,direct.y);
	_angle = math::lerp(_angle, angle, dt * 5);

	//озвучка вращения
	float dif = math::abs(_angle-angle);

	if (dif>0.11)
	{
		if  (_sound == 0)
			_sound = MM::manager.PlaySample("Meh_1");

	}
	else
	{
		if (dif<0.11) 
		{
			if (_sound != 0)
			{
				MM::manager.StopSample(_sound);
				_sound = 0;
			}
		}
	}
	_timer += dt;
}