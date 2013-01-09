#include "AnimationSurchauffe.h"
#include "Outil.h"

AnimationSurchauffe::AnimationSurchauffe(AbstractObjet* objlie, Texte* tex, Interface* inter): Animation(objlie), _texte(tex), _background(inter)
{
	
}


AnimationSurchauffe::~AnimationSurchauffe()
{
}

void AnimationSurchauffe::update()
{
	if(_actif)
	{
		_count++;
		if(_count>10)
		{
			_count =0;
			_texte->setActif(!_texte->getActif());
			_background->setActif(!_background->getActif());
		}
	}
}

void AnimationSurchauffe::setActif(bool ac)
{
	if(ac != _actif)
	{
		_actif = ac;
		if(_actif)
		{
			((SystemeParticules*)getActeur())->restart();
			_count =0;
			_texte->setActif(true);
			_background->setActif(true);
		}
		else
		{
			((SystemeParticules*)getActeur())->stop();
			_texte->setActif(false);
			_background->setActif(false);
		}

	}
}