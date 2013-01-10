#include "AnimationTracter.h"

AnimationTracter::AnimationTracter(AbstractObjet* objlie, AbstractObjet* objetSuivi): Animation(objlie), _objetSuivi(objetSuivi)
{
	_actif =false;
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
	/*switch(key)
		{
		case 'c' :  setActif(!_actif);
		break;
		}*/
}

void AnimationTracter::setActif(bool ac)
{
	if(ac != _actif)
	{
		_actif = ac;
		if(_actif)
		{
			std::cout << "active" << std::endl;
			getActeur()->setAnimationActive(false);
			std::vector<AbstractObjet*>* fils = getActeur()->getFils();
			for(unsigned int i=0 ; i<fils->size(); ++i)
			{
				fils->at(i)->setAnimationActive(false);
			}
			getActeur()->setMatrice(_objetSuivi->getMatrice());
		}
		else
		{
			std::cout << "desactive" << std::endl;
			getActeur()->setAnimationActive(true);
			std::vector<AbstractObjet*>* fils = getActeur()->getFils();
			for(unsigned int i=0 ; i<fils->size(); ++i)
			{
				fils->at(i)->setAnimationActive(true);
			}
			Matrice<GLdouble>* mat = new Matrice<GLdouble>(*_objetSuivi->getMatrice());
			getActeur()->setMatrice(mat);
		}

	}
}
