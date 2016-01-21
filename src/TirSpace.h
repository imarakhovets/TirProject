#pragma once


#include "PhysxSpace.h"
#include "Gun.h"
#include "StaticArray2D.h"
#include "Chip.h"


//максимальное количество клеток по вертикали

namespace Match3 {
	const int MAX_FIELD_X = 7;				//максимальное количество клеток по горизонтали
	const int MAX_FIELD_Y = 5;
	typedef StaticArray2D<Chip*, MAX_FIELD_X, MAX_FIELD_Y> GameField;		//массив клеток игрового поля
}

class PhysxObject;
class Border;

class TirSpace : public PhysxSpace
{
	friend class Target;
	friend class Chip;

public:
	TirSpace(const std::string& name, rapidxml::xml_node<>* elem);

	void resetLevel();
	void Update(float dt);
	void Draw();
	bool MouseDown(const IPoint& mouse_pos) override;

private:

	void checkMath3();
	bool checkMath3(Chip *chip);

	void setChipIndex(int index, Chip* chip);
	void resetTarget();
	void endLevel();

	bool _gameActive;
	float _levelEndTimer;

	int _gameTargets;
	float _gameTimer;
	int _gunBulletSpeed;

	int _cGameTargets;
	float _cGameTimer;
	bool _reset;
	float _timerAddChips;

	Render::Texture *_back;

	Match3::GameField gameField;
	std::vector<Chip*> _chips;
	Border *_left;
	Border *_right;
};
