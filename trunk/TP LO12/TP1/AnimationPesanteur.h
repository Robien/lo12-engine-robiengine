#ifndef _ANIMATION_PESANTEUR_H	
#define _ANIMATION_PESENTEUR_H

#include "Animation.h"
#include "Vector3d.h"

class AnimationPesanteur : public Animation
{
public:
	AnimationPesanteur(AbstractObjet* objlie);
	virtual ~AnimationPesanteur();
	virtual void update();
	void setLimite(GLdouble min,GLdouble max);

private:
	Vector3d<GLdouble> _direction;
	Vector3d<GLdouble> _rotation;
	GLdouble _vitesseRotation;
	GLdouble _limiteMax;
	GLdouble _limiteMin;
};

#endif