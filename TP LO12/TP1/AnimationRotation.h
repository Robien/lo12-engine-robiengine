#ifndef _ANIMATION_ROTATION_H	
#define _ANIMATION_ROTATION_H

#include "Animation.h"

class AnimationRotation : public Animation
{
public:
	AnimationRotation(AbstractObjet* objlie);
	virtual ~AnimationRotation();
	virtual void update();
};

#endif