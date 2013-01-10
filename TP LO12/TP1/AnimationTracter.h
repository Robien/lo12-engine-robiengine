#ifndef _ANIMATION_TRACTER_H	
#define _ANIMATION_TRACTER_H

#include "Animation.h"
#include "Vector3d.h"

class AnimationTracter : public Animation
{
public:
	AnimationTracter(AbstractObjet* objlie, AbstractObjet* objetSuivi);
	virtual ~AnimationTracter();
	virtual void update();
	virtual void proxEvent(GLdouble distance);
	virtual void keyEvent(unsigned char key);
	virtual void setActif(bool ac);
private:
	AbstractObjet* _objetSuivi;
	bool _proche;
};

#endif