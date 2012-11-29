#ifndef _CAMERA_H	
#define _CAMERA_H

#include "AbstractObjet.h"

class Camera : AbstractObjet
{
public:
	Camera(void);
	virtual ~Camera(void);

	void affiche();
};


#endif