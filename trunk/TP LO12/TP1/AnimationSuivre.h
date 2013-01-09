#ifndef _ANIMATION_SUIVRE_H	
#define _ANIMATION_SUIVRE_H

#include "Animation.h"
#include "Vector3d.h"

class AnimationSuivre : public Animation
{
public:
	AnimationSuivre(AbstractObjet* objlie, AbstractObjet* objetSuivi);
	virtual ~AnimationSuivre();
	virtual void update();
	void setActif(bool ac);
private:
	AbstractObjet* _objetSuivi;
	bool _actif;
};

#endif