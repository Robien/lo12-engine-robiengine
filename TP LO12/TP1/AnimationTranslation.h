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
	void setLimite(GLdouble min,GLdouble max);
	virtual void proxEvent(GLdouble distance);

private:
	Vector3d<GLdouble> _direction;
	GLdouble _limiteMax;
	GLdouble _limiteMin;
};

#endif