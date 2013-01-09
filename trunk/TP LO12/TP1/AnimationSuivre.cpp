#include "AnimationSuivre.h"

AnimationSuivre::AnimationSuivre(AbstractObjet* objlie, AbstractObjet* objetSuivi): Animation(objlie), _objetSuivi(objetSuivi)
{
	getActeur()->setMatrice(_objetSuivi->getMatrice());
}


AnimationSuivre::~AnimationSuivre()
{
}

void AnimationSuivre::update()
{
}

void AnimationSuivre::setActif(bool ac)
{
	if(ac != _actif)
	{
		_actif = ac;
		if(_actif)
		{

			getActeur()->setMatrice(_objetSuivi->getMatrice());
		}
		else
		{
			Matrice<GLdouble>* mat = new Matrice<GLdouble>(*_objetSuivi->getMatrice());
			getActeur()->setMatrice(mat);
		}

	}
}
