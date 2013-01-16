#include "AnimationTranslation.h"
#include "Outil.h"


AnimationTranslation::AnimationTranslation(AbstractObjet* objlie): Animation(objlie), _direction()
{
	setLimite(-100,100);
	_direction.setX(Outil::get()->random<GLdouble>(-2,2)/100);
	_direction.setY( Outil::get()->random<GLdouble>(-2,2)/100);
	_direction.setZ( Outil::get()->random<GLdouble>(-2,2)/100);
}


AnimationTranslation::~AnimationTranslation()
{
}

void AnimationTranslation::update()
{
	if(_actif)
	{
		Vector3d<GLdouble> position = getActeur()->getMatrice()->getPosition();
		if(position.getX() > _limiteMax || position.getX() < _limiteMin)
		{
			_direction.setX(-_direction.getX());
		}
		if(position.getY() > _limiteMax || position.getY() < _limiteMin)
		{
			_direction.setY(-_direction.getY());
		}
		if(position.getZ() > _limiteMax || position.getZ() < _limiteMin)
		{
			_direction.setZ(-_direction.getZ());
		}
		getActeur()->getMatrice()->translate(_direction.getX(),_direction.getY(),_direction.getZ());
	}
}

void AnimationTranslation::setLimite(GLdouble min,GLdouble max)
{
	_limiteMax = max;
	_limiteMin = min;
}

void AnimationTranslation::proxEvent(GLdouble distance)
{
	std::cout << "distance : " << distance << std::endl;
}