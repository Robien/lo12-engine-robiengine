#ifndef _ANIMATION_ROTATION_H	
#define _ANIMATION_ROTATION_H

#include "Animation.h"
#include "Vector3d.h"

class AnimationRotation : public Animation
{
public:
	AnimationRotation(AbstractObjet* objlie, Vector3d<int>* axe = NULL, GLdouble vitesse = 2, bool actived = true);
	virtual ~AnimationRotation();
	virtual void update();

private:
	Vector3d<int>* _axe;
	GLdouble _vitesse;
};

#endif