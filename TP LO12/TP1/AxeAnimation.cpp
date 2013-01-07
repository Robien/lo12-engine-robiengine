#include "AxeAnimation.h"


AxeAnimation::AxeAnimation(std::string nomA,std::string nomObjetlier)
{
	_nomObjet = nomObjetlier;
	_nomAxe = nomA;
}


AxeAnimation::~AxeAnimation(void)
{
}


std::string AxeAnimation::getNomAxe()
{
	return _nomAxe;
}
std::string AxeAnimation::getNomObjetLie()
{
	return _nomObjet;
}

void AxeAnimation::setPointA(Vector3d<GLdouble>* a)
{
	_pointA = a;

}
	
void AxeAnimation::setPointB( Vector3d<GLdouble>* b)
{

	_pointB = b;
}
	
Vector3d<GLdouble> AxeAnimation::getDirection()
{
	return *_pointB-*_pointA;
}
Vector3d<GLdouble>* AxeAnimation::getA()
{
	return _pointA;
}