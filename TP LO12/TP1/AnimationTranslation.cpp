#include "AnimationTranslation.h"
#include "Outil.h"


AnimationTranslation::AnimationTranslation(AbstractObjet* objlie): Animation(objlie), _direction()
{

	_direction.setX(Outil::get()->random<GLdouble>(0.0,2.0)-1.0 );
	//_direction.setY( Outil::get()->random<GLdouble>(0.0,2.0)-1.0);
//	_direction.setZ( Outil::get()->random<GLdouble>(0.0,2.0)-1.0);
}


AnimationTranslation::~AnimationTranslation()
{
}

void AnimationTranslation::update()
{
	getActeur()->getMatrice()->translate(1,0,0);

}

void AnimationTranslation::setLimite(float min,float max)
{
	_limiteMax = max;
	_limiteMin = min;
}