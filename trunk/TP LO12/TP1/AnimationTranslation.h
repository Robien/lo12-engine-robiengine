#ifndef _ANIMATION_TRANSLATION_H	
#define _ANIMATION_TRANSLATION_H

#include "Animation.h"
#include "Vector3d.h"

class AnimationTranslation : public Animation
{
public:
	AnimationTranslation(AbstractObjet* objlie);
	virtual ~AnimationTranslation();
	virtual void update();
	void setLimite(float min,float max);

private:
	Vector3d<GLdouble> _direction;
	float _limiteMax;
	float _limiteMin;
};

#endif