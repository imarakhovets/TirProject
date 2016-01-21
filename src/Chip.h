#pragma once

//#include "PhysxObject.h"
//#include "PhysxCircle.h"
#include "PhysxBox.h"

///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///


class TirSpace;
class Chip : public PhysxBox //PhysxObject
{
	friend TirSpace;
public:
	Chip(const std::string& name, FPoint Position, FPoint Speed);
	Chip(const std::string& name);
	Chip(int type);

	void Draw();
	float getSize();
	void setPosition(FPoint Position);


	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void Update(float dt) override;
	void upDateChipsTabs();
	IPoint getCell();
	int getIndex();
	int getType() { return _type; }
	void Boom();

	static int getIndex(IPoint cell);
private:
	void Init();
	void Render(FPoint pos);
	void swap(IPoint cellA, IPoint cellB);
	bool swap(Chip &chip);
	void swap(Chip* chipA, Chip* chipB);
	
	virtual void colision(math::Vector3 vNormal, float deep, PhysxObject* obj);

	IPoint getCell(float x, float y);
	IPoint getCell(FPoint pos);
	

private:
	Render::Texture *_tex1;
	float hWidth; 
	float hHeight; 
	Color _color;
	int _type;
	int _lastIndex;
	bool _isStop;
	float _timerStop;

	std::vector<Chip*> *_chipsTabs;
	IPoint _startCell;
	IPoint _endCell;
	bool _isDrag;
	IPoint _dragPosition;
	TirSpace* gameSpace;

	ParticleEffectPtr _eff;
};
