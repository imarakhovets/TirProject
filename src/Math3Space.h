#pragma once

#include "StaticArray2D.h"
#include "Element.h"

const int MAX_FIELD_X = 15; //максимальное количество клеток по горизонтали
const int MAX_FIELD_Y = 10; //максимальное количество клеток по вертикали
typedef StaticArray2D<Element*, MAX_FIELD_X, MAX_FIELD_Y> GameField;		//массив клеток игрового поля

class Math3Space : public GUI::Widget
{
	friend class Element;

public:
	Math3Space(const std::string& name);
	Math3Space(const std::string& name, rapidxml::xml_node<>* elem);
	void Init();
	void Draw();
	void Update(float dt);
	bool MouseDown(const IPoint& mouse_pos) override;


private:
	void addElement(Element* element, int x, int y);
	void deleteElement(Element* element);
	bool rDeleteElement(Element* element);
	bool checkCollision(DunamicElement* dunamicElement);
	FPoint getFieldPosition(FPoint pos);
	FPoint getWorldPosition(FPoint fieldPos);

private:
	int _cFieldX;
	int _cFieldY;
	float _sizeField;

	EffectsContainer _effCont;
	Render::Texture *_black;
	GameField _gameField;
};
