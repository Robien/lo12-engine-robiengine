#include "AnimationTracter.h"

AnimationTracter::AnimationTracter(AbstractObjet* objlie, AbstractObjet* objetSuivi): Animation(objlie), _objetSuivi(objetSuivi)
{
	getActeur()->setMatrice(_objetSuivi->getMatrice());
}


AnimationTracter::~AnimationTracter()
{
}

void AnimationTracter::update()
{
}

void AnimationTracter::proxEvent(GLdouble distance)
{
		if (distance < 80000 && !_proche)
		{
			_proche = true;
		}
		else if(distance >= 80000 && _proche)
		{
			_proche = false;
		}
}

void AnimationTracter::keyEvent(unsigned char key)
{
	switch(key)
		{
		case 'c' :  setActif(!_actif);
		break;
		}
}

void AnimationTracter::setActif(bool ac)
{
	if(ac != _actif)
	{
		_actif = ac;
		if(_actif)
		{
			std::vector<AbstractObjet*>* fils = getActeur()->getFils();
			for(unsigned int i=0 ; i<fils->size(); ++i)
			{
				fils->at(i)->setAnimationActive(false);
				
			}
			getActeur()->setMatrice(_objetSuivi->getMatrice());
		}
		else
		{
			Matrice<GLdouble>* mat = new Matrice<GLdouble>(*_objetSuivi->getMatrice());
			std::vector<AbstractObjet*>* fils = getActeur()->getFils();
			for(unsigned int i=0 ; i<fils->size(); ++i)
			{
				fils->at(i)->setAnimationActive(true);
			}
			getActeur()->setMatrice(mat);
		}

	}
}
