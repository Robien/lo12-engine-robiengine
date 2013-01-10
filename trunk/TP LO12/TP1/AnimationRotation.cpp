#include "AnimationRotation.h"


AnimationRotation::AnimationRotation(AbstractObjet* objlie): Animation(objlie)
{
}


AnimationRotation::~AnimationRotation()
{
}

void AnimationRotation::update()
{
	if(_actif)
	{
		getActeur()->getMatrice()->rotate(2,0,0,1);
	}
}
