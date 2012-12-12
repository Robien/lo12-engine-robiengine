#ifndef _CAMERAVAISSEAU_H	
#define _CAMERAVAISSEAU_H


#include "Camera.h"
#include "Interactions.h"


class CameraVaisseau : public Camera
{
public:
	CameraVaisseau();
	virtual ~CameraVaisseau();
	public:
	void resetVue();

	struct LookAtParam
	{
		double eyex;
		double eyey;
		double eyez;
		double centrex;
		double centrey;
		double centrez;
		double upx;
		double upy;
		double upz;

	};

public:

	void affiche();
	virtual void pause();
	virtual void unpause();
	void rotationZ_obs(double angle);
	void tourner_tete(int dir, double angle);
	void zoom(double pas); //permet d'avancer ou de reculer dans la scene
	void translation_obs(int dir, double pas);
	void rotation3D(double angle, double* axeVect, double* axePt, double* monPt, double* result);

public:

	LookAtParam _lookAtParam;
	CB_Interraction* _cb;
};

#endif