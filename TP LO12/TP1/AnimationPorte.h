#ifndef _ANIMATION_PORTE_H	
#define _ANIMATION_PORTE_H

#include "const.h"
#include "animation.h"


class AnimationPorte : public Animation
{
public:
	AnimationPorte(AbstractObjet* objlie);
	virtual ~AnimationPorte();
	virtual void update();
	virtual void proxEvent(GLdouble distance);

private:
	bool _isOpening;
	bool _isClosing;
	bool _isClose;
	bool _isOpen;
	GLdouble _angle;
};

#endif