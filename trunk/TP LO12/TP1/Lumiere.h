#ifndef _LUMIERE_H	
#define _LUMIERE_H

#include "AbstractObjet.h"

class Lumiere :	AbstractObjet
{
public:
	Lumiere(void);
	virtual ~Lumiere(void);

	void affiche();
};

#endif