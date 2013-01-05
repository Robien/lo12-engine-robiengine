#ifndef _ANIMATION_H	
#define _ANIMATION_H

#include "Interactions.h"
#include "AbstractObjet.h"

class Animation
{
public:
	Animation(AbstractObjet* objlie);
	virtual ~Animation();
	virtual void update();
	AbstractObjet* getActeur();
private: 
	AbstractObjet* _acteur; //objet qui effectue l'action
};

#endif