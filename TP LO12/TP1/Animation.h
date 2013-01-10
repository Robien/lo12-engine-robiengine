#ifndef _ANIMATION_H	
#define _ANIMATION_H

#include "Interactions.h"
#include "AbstractObjet.h"

class Animation
{
public:
	Animation(AbstractObjet* objlie);
	virtual ~Animation();
	virtual void keyEvent(unsigned char key);
	virtual void update();
	virtual void proxEvent(GLdouble distance);
	AbstractObjet* getActeur();
	virtual void setActif(bool ac);
private: 
	AbstractObjet* _acteur; //objet qui effectue l'action
protected:
	bool _actif;
};

#endif