#include "stdafx.h"
#include "Math3Space.h"
#include "Bullet.h"

Math3Space::Math3Space(const std::string& name)
: Widget(name)

{
	Init();
}

Math3Space::Math3Space(const std::string& name, rapidxml::xml_node<>* elem)
: Widget(name)
{
	Init();
}

void Math3Space::Init()
{
	Element::math3Space = this;

	_cFieldX = MAX_FIELD_X;
	_cFieldY = MAX_FIELD_Y;
	_sizeField = 50;
	position = IPoint(150, 200);
	_black = Core::resourceManager.Get<Render::Texture>("blackW");
	// Element* e = new DunamicElement();


	//Цели
	addElement(new GoalElement(GoalElement::TYPE_SILVER), 5, 5);
	addElement(new GoalElement(GoalElement::TYPE_GOLD), 7, 5);
	addElement(new GoalElement(GoalElement::TYPE_GOLD), 6, 0);

	//Препятствия
	addElement(new ObstacleElement(ObstacleElement::TYPE_ROCK), 4, 0);
	addElement(new ObstacleElement(ObstacleElement::TYPE_BOX), 8, 0);

	//Фишки
	addElement(new ChipElement(ChipElement::TYPE_FLOWER), 6, 4);


	addElement(new ChipElement(ChipElement::TYPE_FLOWER), 6, 6);

	//addElement(new ChipElement(ChipElement::TYPE_LEAF), 6, 6);
	
	for (int i = 0; i < _cFieldX; i++)
		addElement(new ChipElement(math::random(ChipElement::TYPE_END)), i, _cFieldY - 1);
	for (int i = 0; i < _cFieldX; i++)
		addElement(new ChipElement(math::random(ChipElement::TYPE_END)), i, _cFieldY - 2);

}

void Math3Space::addElement(Element* element,int x, int y)
{
	element->setPosition(FPoint(x * _sizeField, y * _sizeField));
	element->setSize(_sizeField);
	if (element->isStop())
		_gameField[x][y] = element;
}

void Math3Space::deleteElement(Element* element)
{
	FPoint pos = getFieldPosition(element->getPosition());
	IPoint iPos = IPoint((int)pos.x, (int)pos.y);

	//Уничтожение дочернего элемента
	if (_gameField[iPos.x][iPos.y]->getTopElement())
	{
		if (rDeleteElement(_gameField[iPos.x][iPos.y]->getTopElement()))
			_gameField[iPos.x][iPos.y]->addTopElement(0);
	}
	else //Полное освобождение ячейки
	{
		delete _gameField[iPos.x][iPos.y];
		_gameField[iPos.x][iPos.y] = nullptr;

		//вывести из состояния покоя все динамическое что выше этой ячейки
		for (int i = iPos.y + 1; i < _cFieldY; i++)
		{
			if (_gameField[iPos.x][i])
			{
				DunamicElement* d = dynamic_cast<DunamicElement*>(_gameField[iPos.x][i]);
				if (d)
				{
					d->Start();
					_gameField[iPos.x][i] = nullptr;
				}
			}
				
		}
	}
}

bool Math3Space::rDeleteElement(Element* element)
{
	if (element->getTopElement())
	{
		if (rDeleteElement(element->getTopElement()))
			element->addTopElement(0);
		return false;
	}
	else
	{
		delete element;
		return true;
	}
}

void Math3Space::Draw()
{
	IPoint mouse_pos =  Core::mainInput.GetMousePos();
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(math::Vector3(position.x, position.y, 0));
	for (int x = 0; x < _cFieldX; x++)
	{
		for (int y = 0; y < _cFieldY; y++)
		{
			Render::device.SetTexturing(false);
			Render::device.SetCurrentColor(Color::RED);
			Render::DrawFrame(IRect(IPoint(x * _sizeField, y * _sizeField), _sizeField, _sizeField));
			Render::device.SetTexturing(true);
			Render::device.SetCurrentColor(Color::WHITE);
			_black->Draw(x * _sizeField, y * _sizeField, _sizeField, _sizeField, FRect(0, 1, 0, 1));

			if (_gameField[x][y])
				_gameField[x][y]->Draw();
		}
	}

	for (int i = 0; i < DunamicElement::_dunamicElements.size(); i++)
	{
		DunamicElement::_dunamicElements[i]->Draw();
	}

	_effCont.Draw();

	Render::device.PopMatrix();
}


bool Math3Space::MouseDown(const IPoint& mouse_pos)
{
	FPoint pos = Math3Space::getFieldPosition(mouse_pos - position);
	IPoint iPos = IPoint((int)pos.x, (int)pos.y);
	IRect r(0, 0, _cFieldX, _cFieldY);

	if (r.Contains(iPos) && _gameField[iPos.x][iPos.y])
	{
		_gameField[iPos.x][iPos.y]->MouseDown();
	}
	return true;
}

void Math3Space::Update(float dt)
{
	dt = math::min<float>(dt, 0.02);
	//for (int x = 0; x < _cFieldX; x++)
	//{
	//	for (int y = 0; y < _cFieldY; y++)
	//	{
	//		if (_gameField[x][y])
	//			_gameField[x][y]->Update(dt);
	//	}
	//}

	for (int i = 0; i < DunamicElement::_dunamicElements.size(); i++)
	{
		checkCollision(DunamicElement::_dunamicElements[i]);
		DunamicElement::_dunamicElements[i]->Update(dt);
	}

	_effCont.Update(dt);
}
FPoint Math3Space::getFieldPosition(FPoint worldPos)
{
	return worldPos / _sizeField;
}

FPoint Math3Space::getWorldPosition(FPoint fieldPos)
{
	return fieldPos * _sizeField;
}

bool Math3Space::checkCollision(DunamicElement* dunamicElement)
{
	if (dunamicElement->isStop()) return false;
	FPoint wPos = dunamicElement->getPosition();
	//простой выход за пределы;
	if (wPos.y < 0)
	{
		FPoint fPos = getFieldPosition(wPos);
		dunamicElement->setSpeed(FPoint());
		dunamicElement->Stop();
		dunamicElement->setPosition(FPoint(wPos.x,0));

		if (_gameField[fPos.x][0])
			_gameField[fPos.x][0]->addTopElement(dunamicElement);
		else
			_gameField[fPos.x][0] = dunamicElement;
		return true;
	}
	//непроходимый элемент
	FPoint fPos = getFieldPosition(wPos);
	int y = (int)fPos.y;
	if (_gameField[fPos.x][y] &&
		(
			(!_gameField[fPos.x][y]->isPermeable()) ||
			(_gameField[fPos.x][y]->getTopElement() && !_gameField[fPos.x][y]->getTopElement()->isPermeable())//кастыль для вложенных
			)
		)
	{
			dunamicElement->setSpeed(FPoint());
			dunamicElement->Stop();
			dunamicElement->setPosition(getWorldPosition(FPoint(fPos.x, y + 1)));
			_gameField[fPos.x][y + 1] = dunamicElement;
			return true;
	}

	return false;
}


