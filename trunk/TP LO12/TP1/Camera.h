#ifndef _CAMERA_H	
#define _CAMERA_H

#include "Matrice.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void affiche();
	virtual void maj();

public:
	Matrice<GLdouble>* getMatrice();
	Matrice<GLdouble>& matrice();

private:
	Matrice<GLdouble> _matrice;


};


#endif