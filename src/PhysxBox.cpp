#include "stdafx.h"
#include "PhysxBox.h"


PhysxBox::PhysxBox(const std::string& name, int hWidth, int hHeight)
	: PhysxObject(name)
{
	 _hWidth = hWidth;
	 _hHeight = hHeight;
	_body = BODY_BOX;



}

void PhysxBox::getProjecToVector(math::Vector3 *vC, float *a, float *b)
{
	
	float cProject0 = vC->DotProduct(PointToVector(_fPosition + IPoint(_hWidth,_hHeight)));
	float cProject1 = vC->DotProduct(PointToVector(_fPosition + IPoint(_hWidth,-_hHeight)));
	float cProject2 = vC->DotProduct(PointToVector(_fPosition + IPoint(-_hWidth,-_hHeight)));
	float cProject3 = vC->DotProduct(PointToVector(_fPosition + IPoint(-_hWidth,_hHeight)));
	/*math::Vector3 vector =  vC;
	float cProject0 = vector.DotProduct(_fPosition + IPoint(_hWidth,_hHeight));
	float cProject1 = vector.DotProduct(_fPosition + IPoint(_hWidth,-_hHeight));
	float cProject2 = vector.DotProduct(_fPosition + IPoint(-_hWidth,-_hHeight));
	float cProject3 = vector.DotProduct(_fPosition + IPoint(-_hWidth,_hHeight));*/

	*a = math::max(math::max(cProject0,cProject1), math::max(cProject2,cProject3));
	*b = math::min(math::min(cProject0,cProject1), math::min(cProject2,cProject3));

	//	*a = cProject + _radius;
	//*b = cProject - _radius;
}

void PhysxBox::colision(math::Vector3 vNormal, float deep, PhysxObject* obj)
{
	PhysxObject::colision(vNormal, deep, obj);
}


PhysxBox::~PhysxBox()
{

}
