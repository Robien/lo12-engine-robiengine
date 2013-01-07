#include "AnimationPorte.h"


AnimationPorte::AnimationPorte(AbstractObjet* objlie) : Animation(objlie)
{
	_isOpening = false;
	_isClosing = false;
	_isClose = true;
	_isOpen = false;
	_angle = 0;
}


AnimationPorte::~AnimationPorte()
{
}

void AnimationPorte::update()
{
	if (_isOpening)
	{
		_isOpen = false;
		_isClose = false;
		_angle += 0.5;
		getActeur()->getMatrice()->translate(
			getActeur()->getAxes().at(0)->getA()->getX(),
			getActeur()->getAxes().at(0)->getA()->getY(),
			getActeur()->getAxes().at(0)->getA()->getZ());
		getActeur()->getMatrice()->rotate(0.5,0,0,1);
				getActeur()->getMatrice()->translate(
			-getActeur()->getAxes().at(0)->getA()->getX(),
			-getActeur()->getAxes().at(0)->getA()->getY(),
			-getActeur()->getAxes().at(0)->getA()->getZ());
		if (_angle >= 85)
		{
			_isOpening = false;
			_isOpen = true;
		}
	} 
	else if (_isClosing)
	{
		_isOpen = false;
		_isClose = false;
		_angle -= 0.2;
				getActeur()->getMatrice()->translate(
			getActeur()->getAxes().at(0)->getA()->getX(),
			getActeur()->getAxes().at(0)->getA()->getY(),
			getActeur()->getAxes().at(0)->getA()->getZ());
		getActeur()->getMatrice()->rotate(-0.2,0,0,1);
				getActeur()->getMatrice()->translate(
			-getActeur()->getAxes().at(0)->getA()->getX(),
			-getActeur()->getAxes().at(0)->getA()->getY(),
			-getActeur()->getAxes().at(0)->getA()->getZ());
		if (_angle <= 0)
		{
			_isClosing = false;
			_isClose = true;
		}
	}
}

void AnimationPorte::proxEvent(GLdouble distance)
{
	if (distance < 80000 && !_isOpen)
	{
		_isOpening = true;
		_isClosing = false;
	}
	else if(distance >= 80000 && !_isClose)
	{
		_isOpening = false;
		_isClosing = true;
	}
}