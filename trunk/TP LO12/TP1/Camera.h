#ifndef _CAMERA_H	
#define _CAMERA_H

#include "Matrice.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void affiche();
private:
	Matrice<GLdouble> _matrice;
};


#endif