#include "stdafx.h"
#include "Element.h"
#include "Math3Space.h"

std::vector<DunamicElement*> DunamicElement::_dunamicElements;
Math3Space* Element::math3Space;

Element::Element():_stop(true), _topElement(0), _isVisable(true)
{
	_ico = Core::resourceManager.Get<Render::Texture>("golden");
}

void Element::Draw()
{
	if (_isVisable)
	_ico->Draw(_position.x, _position.y, _size, _size, FRect(0, 1, 0, 1));
}

void Element::MouseDown()
{
	if (_topElement)
		_topElement->MouseDown();
	else
	{
		_eff = math3Space->_effCont.AddEffect("FindCoin2");
		_eff->SetPos(_position + FPoint(_size, _size)*0.5);
		_eff->Reset();

		MM::manager.PlaySample("Boom");
		math3Space->deleteElement(this);
	}
}

void Element::Update(float dt)
{

}

DunamicElement::DunamicElement():_speed(FPoint(0,-400))
{
	_stop = false;
	_permeable = false;
	_ico = Core::resourceManager.Get<Render::Texture>("apple");
	_dunamicElements.push_back(this);
}

DunamicElement::~DunamicElement()
{
	for (std::vector<DunamicElement*>::iterator i = _dunamicElements.begin(); i < _dunamicElements.end(); i++)
	{
		if (*i._Ptr == this)
		{
			_dunamicElements.erase(i);
			break;
		}
	}	
}

void DunamicElement::Update(float dt)
{
	_position += _speed * dt;
}

StaticElement::StaticElement()
{
	_ico = Core::resourceManager.Get<Render::Texture>("box");
	_permeable = false;
}

ObstacleElement::ObstacleElement(int type) : _type(type)
{
	if (type == TYPE_BOX)
		_ico = Core::resourceManager.Get<Render::Texture>("box");
	else if (type == TYPE_ROCK)
		_ico = Core::resourceManager.Get<Render::Texture>("rock");
}

GoalElement::GoalElement(int type):_type(type)
{
	if (type == TYPE_GOLD)
		_ico = Core::resourceManager.Get<Render::Texture>("golden");
	else if (type == TYPE_SILVER)
		_ico = Core::resourceManager.Get<Render::Texture>("silver");
	_permeable = true;
}

ChipElement::ChipElement(int type) :_type(type)
{
	if (type == TYPE_APPLE)
		_ico = Core::resourceManager.Get<Render::Texture>("apple");
	else if (type == TYPE_BLACKBERRY)
		_ico = Core::resourceManager.Get<Render::Texture>("blackberry");
	else if (type == TYPE_FLOWER)
		_ico = Core::resourceManager.Get<Render::Texture>("flower");
	else if (type == TYPE_LEAF)
		_ico = Core::resourceManager.Get<Render::Texture>("leaf");
	else if (type == TYPE_PEAR)
		_ico = Core::resourceManager.Get<Render::Texture>("pear");
}
