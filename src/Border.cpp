#include "stdafx.h"
#include "Border.h"

Border::Border(FPoint position, FPoint direction)
	: PhysxSide("Border",position, direction)
{
	_role = ROLE_BORDER;
	_mass = 1000000.0;
	_bounce = 0.1;
}


void Border::Draw() 
{
#ifdef _DEBUG
	if (_role !=ROLE_BORDER) return;
	Render::device.PushMatrix();
	Render::device.SetTexturing(false);

	Render::BeginColor(Color(255, 128, 0, 255));
	math::Vector3 temp = math::Vector3(_fDirection.x, _fDirection.y, 0)  * 3000;
	IPoint a = IPoint(_fPosition.x,_fPosition.y);
	IPoint b = IPoint(_fPosition.x,_fPosition.y) + IPoint(temp.y,-temp.x);
	Render::DrawLine(a, b);
	Render::DrawLine(IPoint(_fPosition.x,_fPosition.y), IPoint(_fPosition.x,_fPosition.y) + IPoint(-temp.y,temp.x));
	Render::EndColor();
	Render::device.SetTexturing(true);
	Render::device.PopMatrix();
#endif
}

void Border::colision(math::Vector3 vNormal, float deep, PhysxObject* obj)
{
 
}


