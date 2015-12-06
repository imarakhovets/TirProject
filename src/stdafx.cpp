// stdafx.cpp : source file that includes just the standard includes
// test.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

math::Vector3 PointToVector(FPoint point)
{
	return math::Vector3(point.x, point.y, 0);
}
