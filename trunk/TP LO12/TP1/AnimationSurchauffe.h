#ifndef _ANIMATION_SURCHAUFFE_H	
#define _ANIMATION_SURCHAUFFE_H

#include "Animation.h"
#include "Vector3d.h"
#include "Texte.h"
#include "Interface.h"
#include "SystemeParticules.h"

class AnimationSurchauffe : public Animation
{
public:
	AnimationSurchauffe(AbstractObjet* objlie, Texte* tex, Interface* inter);
	virtual ~AnimationSurchauffe();
	virtual void update();
	void setActif(bool ac);

private:
	int _count;
	Texte* _texte;
	Interface* _background;
	SystemeParticules* _lienParticule;
	bool _actif;
};

#endif