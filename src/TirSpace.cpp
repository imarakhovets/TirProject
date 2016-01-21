#include "stdafx.h"
#include "TirSpace.h"
#include "PhysxObject.h"
#include "Border.h"
#include "Chip.h"
#include "Billboard.h"
#include "TriggerGame.h"

#include "IO/Stream.h"

int Gun::bulletSpeed;
const int rows = 5;
const int cols = 7;

TirSpace::TirSpace(const std::string& name, rapidxml::xml_node<>* elem): PhysxSpace("TirSpace")
{
	setStatic(true);
	_back = Core::resourceManager.Get<Render::Texture>("Back");

	_cGameTargets = 20;
	_gunBulletSpeed = 1150;
	Gun::bulletSpeed = _gunBulletSpeed;
	_cGameTimer = 14;

	int sWidth = Render::device.Width();
	int sHeight = Render::device.Height();
	int offset = 10;

	setPosition(IPoint(0, 0));

//	new Border(FPoint(0,sHeight-offset),FPoint(0.0,-1.0));
	new Border(FPoint(0,offset+150),FPoint(0.0,1.0));
	_right = new Border(FPoint(sWidth-offset,0),FPoint(-1,0.0));
	_left = new Border(FPoint(offset,0),FPoint(1.0,0.0));

	setGravity(FPoint(0,-9.8*1));
    resetTarget();
}

void TirSpace::resetLevel()
{
	_reset = true;
}

void TirSpace::checkMath3() 
{
	for (std::vector<Chip*>::iterator i = _chips.begin(); i < _chips.end(); i++)
	{
		if (*i._Ptr)
			checkMath3(*i._Ptr);
		//static_cast<Chip*>(*i._Ptr)->Boom();
	}

	
}

bool TirSpace::checkMath3(Chip *chip)
{
	if ((chip->_delete) || (!chip->_isStop)) return false;
	std::vector<Chip*> mathElemantsH;
	std::vector<Chip*> mathElemantsV;
	IPoint p = chip->getCell();

	//левее
	int type = chip->getType();
	for (int i = p.x - 1; i >= 0; i--)
	{
		int index = Chip::getIndex(IPoint(i, p.y));
		if (_chips[index] && (_chips[index]->getType() == type) && _chips[index]->_isStop)
			mathElemantsH.push_back(_chips[index]); else break;
	}
	//правее
	for (int i = p.x + 1; i < 7; i++)
	{
		int index = Chip::getIndex(IPoint(i, p.y));
		if (_chips[index] &&  (_chips[index]->getType() == type) && _chips[index]->_isStop)
			mathElemantsH.push_back(_chips[index]); else break;	
	}
	//выше
	for (int i = p.y - 1; i >= 0; i--)
	{
		int index = Chip::getIndex(IPoint(p.x, i));
		if (_chips[index] && (_chips[index]->getType() == type) && _chips[index]->_isStop)
			mathElemantsV.push_back(_chips[index]); else break;
	}
	//ниже
	for (int i = p.y + 1; i < 5; i++)
	{
		int index = Chip::getIndex(IPoint(p.x, i));
		if (_chips[index] && (_chips[index]->getType() == type) && _chips[index]->_isStop)
			mathElemantsV.push_back(_chips[index]); else break;
	}



	bool result = false;

	if (mathElemantsH.size() >= 2)
	{
		
		for (std::vector<Chip*>::iterator i = mathElemantsH.begin(); i < mathElemantsH.end(); i++)
		{
			static_cast<Chip*>(*i._Ptr)->Boom();
		}

		chip->Boom();
		result = true;
	}

	if (mathElemantsV.size() >= 2)
	{

		for (std::vector<Chip*>::iterator i = mathElemantsV.begin(); i < mathElemantsV.end(); i++)
		{
			static_cast<Chip*>(*i._Ptr)->Boom();
		}

		chip->Boom();
		result = true;
	}

	
	mathElemantsH.clear();
	mathElemantsV.clear();

	return result;
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

	math::RandomValue<int> randType(5, 0.0, 1.0);

	_gameTargets = _cGameTargets;
	_gameTimer = _cGameTimer;

	for (int i = 0; i < rows; i++)
	{
		//randomX.Update(0.5);
		//randomY.Update(0.5);
		//speed.Update(0.5);
		//direct.Update(0.5);
		for (int j = 0; j < cols; j++)
		{
			randType.Update(0.1);
			
			Chip* chip = new Chip(randType.get());
			
			int offsetX = 150 + (chip->getSize()+5) * j;
			int offsetY = Render::device.Height() / 2 + chip->getSize() * 1.5 * i;
			chip->setPosition(IPoint(offsetX, offsetY));
			
			_chips.push_back(0);
		}
	}

	_gameActive  = true;
	_reset = false;

	_timerAddChips = 1.0;
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

bool TirSpace::MouseDown(const IPoint& mouse_pos)
{
	if (mouse_pos.x > 915 && mouse_pos.y < 74)
	{
		resetTarget();
		return true;
	}
	return false;
}
void TirSpace::Update(float dt)
{
	if (_reset)
		resetTarget();
	
	if ((_gameTimer<=0) || (_gameTargets == 0))
		endLevel();
	//else
	//	_gameTimer -= dt;
	if (_timerAddChips > 0)
	{
		_timerAddChips -= dt;
	}
	else
	{
		math::RandomValue<int> randType(5, 0.0, 1.0);
		for (int j = 0; j < cols; j++)
		{
			if (_chips[4 * (cols)+j] == nullptr)
			{
				randType.Update(0.1);

				Chip* chip = new Chip(randType.get());

				int offsetX = 150 + (chip->getSize() + 5) * j;
				int offsetY = Render::device.Height() / 2 + chip->getSize() * 2 + 50;
				chip->setPosition(IPoint(offsetX, offsetY));

				//_chips.push_back(0);
			}
		}
	}



	checkMath3();
	//for (int i = 0; i < rows; i++)
	//{
	//	for (int j = 0; j < cols; j++)
	//	{
	//		_chips[i *(cols) + j] = nullptr;
	//	}
	//}

	PhysxSpace::Update(dt);
}

void TirSpace::setChipIndex(int index, Chip* chip)
{
	if (index < _chips.size())
	{
		if (_chips[index] != chip)
		{
			_chips[index] = chip;
			int s = _chips.size();
			bool r = (chip->_lastIndex < s);
			Assert(r);

			if ((chip->_lastIndex!=-1) && (_chips[chip->_lastIndex] == chip))
				_chips[chip->_lastIndex] = nullptr;
			_timerAddChips = 1.0;

			checkMath3(chip);
		}
	}
}

void TirSpace::Draw()
{
	Render::device.PushMatrix();
	_back->Draw();
	Render::BindFont("default");
	Render::PrintString(900 + 100 / 2, 50, utils::lexical_cast((int)_gameTimer), 2.f, CenterAlign);
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (_chips[i * cols + j])
				Render::PrintString(20 + 15 * j, 50 + 15 * i, utils::lexical_cast((int)1), 1.5f, LeftAlign);
			else
				Render::PrintString(20 + 15 * j, 50 + 15 * i, utils::lexical_cast((int)0), 1.5f, LeftAlign);
		}
	}



	//gameField

		for (int x = 0; x < Match3::MAX_FIELD_X; x++)
		{
			for (int y = 0; y < Match3::MAX_FIELD_Y; y++)
			{
				if (gameField[x][y])
					Render::PrintString(200 + 15 * x, 50 + 15 * y, utils::lexical_cast((int)1), 1.5f, LeftAlign);
				else
					Render::PrintString(200 + 15 * x, 50 + 15 * y, utils::lexical_cast((int)0), 1.5f, LeftAlign);
			}
		}





	Render::device.PopMatrix();
	PhysxSpace::Draw();
}
