#include "AnimationRotation.h"


AnimationRotation::AnimationRotation(AbstractObjet* objlie, Vector3d<int>* axe, GLdouble vitesse, bool actived): Animation(objlie), _axe(axe), _vitesse(vitesse)
{
	if (_axe == NULL)
	{
		_axe = new Vector3d<int>(0, 0, 1);
	}
	if (!actived)
	{
		setActif(false);
	}
}


AnimationRotation::~AnimationRotation()
{
}

void AnimationRotation::update()
{
	if(_actif)
	{
		getActeur()->getMatrice()->rotate(_vitesse ,_axe->getX(),_axe->getY(),_axe->getZ());
	}
}
