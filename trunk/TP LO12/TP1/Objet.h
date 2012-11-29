#ifndef _OBJET_H	
#define _OBJET_H

#include "AbstractObjet.h"

class Objet : AbstractObjet
{
public:
	Objet();
	virtual ~Objet();

	virtual void affiche();
};


#endif