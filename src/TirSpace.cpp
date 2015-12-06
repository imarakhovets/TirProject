#include "stdafx.h"
#include "TirSpace.h"
#include "PhysxObject.h"
#include "Border.h"
#include "Target.h"
#include "Billboard.h"
#include "TriggerGame.h"

#include "IO/Stream.h"

int Gun::bulletSpeed;

TirSpace::TirSpace(const std::string& name, rapidxml::xml_node<>* elem): PhysxSpace("TirSpace")
{
	setStatic(true);
	_back = Core::resourceManager.Get<Render::Texture>("Back");

	//File::c_file settings("../input.txt");

	//IO::InputStreamPtr settings = File::OpenRead("../input.txt");
	//settings.get()->
	/*
	if (settings.is_open())
	{
		std::string str = settings.getline();
		while (!str.empty())
		{
			std::string name, value;
			if (utils::ReadNvp(str, name, value))
			{
				if (name == "CountTarget")
					_cGameTargets = utils::lexical_cast<int>(value);
				else if (name == "Speed")
				{
					_gunBulletSpeed = utils::lexical_cast<int>(value);
					Gun::bulletSpeed =  _gunBulletSpeed;
				}
					else if (name == "Time")
					_cGameTimer = utils::lexical_cast<int>(value);
			}
			str = settings.getline();
		}
	}*/


	_cGameTargets = 20;

	_gunBulletSpeed = 1150;
	Gun::bulletSpeed = _gunBulletSpeed;


	_cGameTimer = 14;



	int sWidth = Render::device.Width();
	int sHeight = Render::device.Height();
	int offset = 10;

	new Border(FPoint(0,sHeight-offset),FPoint(0.0,-1.0));
	new Border(FPoint(0,offset+150),FPoint(0.0,1.0));
	_right = new Border(FPoint(sWidth-offset,0),FPoint(-1,0.0));
	_left = new Border(FPoint(offset,0),FPoint(1.0,0.0));

	setGravity(FPoint(0,-9.8*100));
    resetTarget();

	
	setPosition(IPoint(0,0));
}

void TirSpace::resetLevel()
{
	_reset = true;
}

void TirSpace::resetTarget()
{
	_right->_role = PhysxObject::ROLE_BORDER;
	_left->_role = PhysxObject::ROLE_BORDER;

	WidgetContainer& childs = this->getChildren();

	for(WidgetIterator iter = childs.begin(); iter != childs.end(); iter++)
	{
		PhysxObject *p = static_cast<PhysxObject*>(iter->get());
		if (p->_role != PhysxObject::ROLE_BORDER)
			p->destroy();
	}

	math::RandomValue<int> randomX(Render::device.Width()-120,0.5,0.8);
	math::RandomValue<int> randomY(Render::device.Height()/3,0.5,0.8);
    math::RandomValue<int> speed(200,0.5,0.8);
	math::RandomValue<int> direct(2,0.5,0.8);

	_gameTargets = _cGameTargets;
	_gameTimer = _cGameTimer;

	for(int i = 0; i<_gameTargets;i++)
	{	
		randomX.Update(0.5);
		randomY.Update(0.5);
		speed.Update(0.5);
		direct.Update(0.5);
		int offsetX = 60 + randomX.get();
		int offsetY = randomY.get() - Render::device.Height()/8;
		IPoint dir(0,0);
		if (direct.get()==1)
			dir.x = (250 + speed.get() - 100)*(-1);
		else
			dir.x = (250 + speed.get() - 100);

		new Target("Target",IPoint(offsetX,500 + offsetY),dir);
	}

	_gameActive  = true;
	_reset = false;
}

void TirSpace::endLevel()
{
	if (_gameActive)
	{
		WidgetContainer& childs = this->getChildren();
		for(WidgetIterator iter = childs.begin(); iter != childs.end(); iter++)
		{
			PhysxObject *p = static_cast<PhysxObject*>(iter->get());
			if (p->_role == PhysxObject::ROLE_TARGET)
				p->setTimeLive(6);
		}


		new Billboard(IPoint(1124,500),IPoint(-100 ,0),_cGameTargets, _cGameTargets - _gameTargets);
		new TriggerGame(IPoint(1200,420),IPoint(-100 ,0),false);
		new TriggerGame(IPoint(1070,420),IPoint(-100 ,0),true);

		_right->_role = PhysxObject::ROLE_NONE;
		_left->_role = PhysxObject::ROLE_NONE;

		_gameActive = false;
	}
}


void TirSpace::Update(float dt)
{
	if (_reset)
		resetTarget();
	
	if ((_gameTimer<=0) || (_gameTargets == 0))
		endLevel();
	else
		_gameTimer -= dt;

	PhysxSpace::Update(dt);
}

void TirSpace::Draw()
{
	Render::device.PushMatrix();
	_back->Draw();
	Render::BindFont("default");
	Render::PrintString(900 + 100 / 2, 50, utils::lexical_cast((int)_gameTimer), 2.f, CenterAlign);
	Render::device.PopMatrix();
	PhysxSpace::Draw();
}
