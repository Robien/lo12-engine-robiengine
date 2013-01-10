#ifndef _CAMERAVAISSEAU_H	
#define _CAMERAVAISSEAU_H


#include "Camera.h"
#include "Interactions.h"
#include "InterfaceVitesse.h"


class CameraVaisseau : public Camera
{
public:
	CameraVaisseau();
	void setInterfaceVitesse(InterfaceVitesse* interfaceVitesse);
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
	void testaffiche();
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
	InterfaceVitesse* _interfaceVitesse;
};

#endif