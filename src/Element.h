#pragma once

class Math3Space;

//Абстракция -------------------------
class Element
{
public:
	Element();
	virtual ~Element() {};

	virtual void Draw();
	virtual void Update(float dt);

	void MouseDown();

	void addTopElement(Element* topElement) { _topElement = topElement; }
	Element* getTopElement() { return _topElement; }

	bool isPermeable() { return _permeable; };
	FPoint getPosition() { return _position; };
	void setPosition(FPoint pos) { _position = pos; };
	void setSize(float size) { _size = size; };

	bool isStop() { return _stop; };
	void Stop() { _stop = true; };

	static Math3Space* math3Space;

protected:
	Element* _topElement;
	FPoint _position;
	float _size;
	bool _permeable;
	bool _stop;
	bool _isVisable;

	Render::Texture *_ico;
	ParticleEffectPtr _eff;
};

class StaticElement : public Element
{
public:
	StaticElement();
};

class DunamicElement : public Element
{
public:
	DunamicElement();
	~DunamicElement() override;
	virtual void Update(float dt) override;

	void setSpeed(FPoint speed) { _speed = speed; };
	void Start() { _stop = false; _speed = FPoint(0, -400); };
//	virtual void Draw();

static std::vector<DunamicElement*> _dunamicElements;

protected:
	FPoint _speed;
};

//Конкретика -------------------------

//Цели
class GoalElement : public StaticElement
{
public:
	enum TYPE
	{
		TYPE_GOLD,
		TYPE_SILVER
	};

	GoalElement(int type);

private:
	int _type;
};

//Препятствия
class ObstacleElement : public StaticElement
{
public:
	enum TYPE
	{
		TYPE_BOX,
		TYPE_ROCK
	};
	ObstacleElement(int type);
private:
	int _type;
};

//Фишки
class ChipElement : public DunamicElement
{
public:
	enum TYPE
	{
		TYPE_APPLE,
		TYPE_BLACKBERRY,
		TYPE_FLOWER,
		TYPE_LEAF,
		TYPE_PEAR,

		TYPE_END
	};

	ChipElement(int type);

private:
	int _type;
};