#include "stdafx.h"
#include "Chip.h"
#include "TirSpace.h"


Chip::Chip(const std::string& name, FPoint Position, FPoint Speed)
	: PhysxBox(name)
{
	Init();

	_speed = Speed;
	_fPosition = Position;
}

Chip::Chip(int type)
	: PhysxBox("Target")
{
	Init();
	_type = type;
	switch (_type)
	{
	case 0:
		_color = Color::RED;
		break;
	case 1:
		_color = Color::GREEN;
		break;
	case 2:
		_color = Color::BLUE;
		break;
	case 3:
		_color = Color(250,200,100);
		break;
	case 4:
		_color = Color(50, 200, 150);
		break;
	case 5:
		_color = Color(200, 100, 100);
		break;
	default:
		break;
	}

}

Chip::Chip(const std::string& name)
	: PhysxBox(name)
{
	Init();
}

bool Chip::MouseDown(const IPoint& mouse_pos)
{
	FRect rect(_fPosition.x - hWidth, _fPosition.x + hWidth, _fPosition.y - hHeight, _fPosition.y + hHeight);
	if (rect.Contains(mouse_pos))
	{
		//_color = Color::WHITE;
		_startCell = getCell(mouse_pos);
		_isDrag = true;
		_dragPosition = mouse_pos;
		//Boom();
		return true;
	}

	return false;
}

void Chip::MouseUp(const IPoint& mouse_pos)
{
	if (_isDrag)
	{

		_isDrag = false;
		_endCell = getCell(mouse_pos);

		swap(*(gameSpace->_chips[getIndex(_endCell)]));


		//swap(_startCell, _endCell);
		//gameSpace->checkMath3();
	}
}

void Chip::swap(IPoint cellA, IPoint cellB)
{
	int indexA = getIndex(cellA);
	int indexB = getIndex(cellB);
	Assert((indexA>=0) && (indexA < gameSpace->_chips.size()));
	Assert((indexB >= 0) && (indexB < gameSpace->_chips.size()));

	Chip* pChipA = gameSpace->_chips[indexA];
	Chip* pChipB = gameSpace->_chips[indexB];

	gameSpace->_chips[indexA] = pChipB;
	gameSpace->_chips[indexB] = pChipA;

	FPoint t = pChipA->_fPosition;
	pChipA->_fPosition = pChipB->_fPosition;
	pChipB->_fPosition = t;

	//chips[index]
}

bool Chip::swap(Chip &chip)
{
	Chip* pChipA = &chip;
	Chip* pChipB = this;

	//накладываем ограничения 
	IPoint dif = pChipA->getCell() - pChipB->getCell();
	if ((math::abs(dif.x) + math::abs(dif.y)) != 1)
		return false;

	//перестановка
	swap(pChipA, pChipB);

	//поверка на совпадение
	bool r = gameSpace->checkMath3(pChipA);
	bool r2 = gameSpace->checkMath3(pChipB);

	if (r || r2)
	{
		return true;
	}
	else
	{
		//откат
		swap(pChipA, pChipB);
		return false;
	}
}

void Chip::swap(Chip* chipA, Chip* chipB)
{
	//перестановка
	gameSpace->_chips[chipA->getIndex()] = chipB;
	gameSpace->_chips[chipB->getIndex()] = chipA;

	FPoint t = chipA->_fPosition;
	chipA->_fPosition = chipB->_fPosition;
	chipB->_fPosition = t;
}

int Chip::getIndex(IPoint cell)
{
	return cell.y * (7) + cell.x;
}

void Chip::MouseMove(const IPoint& mouse_pos)
{
	if (_isDrag)
		_dragPosition = mouse_pos;
}

void Chip::Update(float dt)
{
	upDateChipsTabs();
	PhysxObject::Update(dt);

	if (_timerStop > 0)
		_timerStop -= dt;
	else
		_isStop = true;
}

void Chip::upDateChipsTabs()
{
	if (this->_delete) return;

	if (gameSpace->_chips.size() != 0)
	{

		int index = getIndex(getCell(_fPosition));
		if (index >= gameSpace->_chips.size()) return;
		if (_lastIndex != index)
		{
			gameSpace->gameField[getCell(_fPosition).x][getCell(_fPosition).y] = this;
			gameSpace->setChipIndex(index, this);
			_lastIndex = index;
			_timerStop = 1.0;
			_isStop = false;
		}
	}
}

void Chip::setPosition(FPoint Position)
{
	_fPosition = Position;
}

float Chip::getSize()
{
	return hWidth*2;
}

void Chip::Init()
{
	_tex1 = Core::resourceManager. Get<Render::Texture>("Target");
	hWidth = _tex1->getBitmapRect().width/2;
	hHeight = _tex1->getBitmapRect().height/2;

	_role = ROLE_TARGET;
	//_radius = hHeight;
	_hWidth = hHeight;
	_hHeight = hHeight;
	_mass = 1.0;
	_bounce = 0.05;
	_useGravity = true;
	_isDrag = false;
	//_chipsTabs = 0;
	_lastIndex = -1;
	_isStop = true;
	_timerStop = 0;

	gameSpace = static_cast<TirSpace*>(space);
}

IPoint Chip::getCell()
{
	return getCell(_fPosition);
}

int Chip::getIndex()
{
	return getIndex(getCell(_fPosition));
}


IPoint Chip::getCell(FPoint pos)
{
	return getCell(pos.x, pos.y);
}
IPoint Chip::getCell(float x, float y)
{
	int i = math::round((x - 150) / (getSize() + 5));
	int j = math::round((y - 200) / (getSize() * 1.0));
	return IPoint(i, j);
}

void Chip::Draw()
{
	Render(_fPosition);

	if (_isDrag)
	{
		Render(_dragPosition);// = mouse_pos;

		Render::device.PushMatrix();
		Render::device.SetCurrentColor(Color::BLACK);
		Render::PrintString(500, 100, utils::lexical_cast(_startCell.x), 1.5f, LeftAlign);
		Render::PrintString(520, 100, utils::lexical_cast(_startCell.y), 1.5f, LeftAlign);
		Render::device.PopMatrix();
	}
}

void Chip::Render(FPoint pos)
{
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(math::Vector3(pos.x - hWidth, pos.y - hHeight, 0));
	Render::device.SetCurrentColor(_color);

	//FRect rect(0, 0, 1, 1);
	//_tex1->Draw(_fPosition.x, _fPosition.y, hWidth, hHeight, rect);
	_tex1->Draw();

	Render::device.SetCurrentColor(Color::WHITE);
	Render::PrintString(0, 0, utils::lexical_cast(getCell(pos).x), 1.5f, LeftAlign);
	Render::PrintString(50, 0, utils::lexical_cast(getCell(pos).y), 1.5f, LeftAlign);
	Render::device.PopMatrix();
}


void Chip::Boom()
{
	_eff = space->_effCont.AddEffect("FindCoin2");
	_eff->SetPos(this->_fPosition);
	_eff->Reset();

	MM::manager.PlaySample("Boom");
	this->_delete = true;

	int index = getIndex(getCell(_fPosition));
	if (index < gameSpace->_chips.size())
		gameSpace->_chips[index] = nullptr;
}

void Chip::colision(math::Vector3 vNormal, float deep, PhysxObject* obj)
{
	if (this->_delete) return;

	if ((obj->_role == ROLE_BORDER) || ((obj->_role == ROLE_TARGET)/* && obj->_stop*/))
	{

		PhysxBox::colision(vNormal, deep, obj);
		_stop = true;
		//_speed *= 0.25;
	}
	else
		if (obj->_role == ROLE_BULLET)
		{
			Boom();
		}
}