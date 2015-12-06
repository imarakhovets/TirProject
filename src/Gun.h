#pragma once


class Gun : public GUI::Widget
{
public:
	Gun(const std::string& name);
	Gun(const std::string& name, rapidxml::xml_node<>* elem);

	void Draw();
	void Update(float dt);

	static int bulletSpeed;
private:
	void Init();

private:
	float _timer;
	float _timerShut;
	bool _isMain;

	int _bulletSpeed;
	int _sound;
	
	float _scale;
	float _angle;
	float _rollback;
	float _rollbackNorm;

	IPoint baseOffsetPos;
	
	Render::Texture *_tex1;
	Render::Texture *_tex2;
};
