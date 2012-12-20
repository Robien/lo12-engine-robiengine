#ifndef _AXE_ANIMATION_H	
#define _AXE_ANIMATION_H

#include "Vector3d.h"
#include "const.h"
#include <iostream>
#include <string>

class AxeAnimation
{
public:
	AxeAnimation(std::string nomA,std::string nomObjetlier);
	virtual ~AxeAnimation();

	std::string getNomAxe();
	std::string getNomObjetLie();
	void setPointA(Vector3d<GLdouble>* a);
	void setPointB( Vector3d<GLdouble>* b);
	Vector3d<GLdouble> getDirection();

private:
	std::string _nomObjet;
	std::string _nomAxe;
	Vector3d<GLdouble>* _pointA;
	Vector3d<GLdouble>* _pointB;
};

#endif