#ifndef _CAMERAPOLAR_H	
#define _CAMERAPOLAR_H

#include "Camera.h"
#include "const.h"
#include "Interactions.h"


class CameraPolarView : public Camera
{
public:
	struct PolarParam
	{
		double azimut;
		double elevation;
		double distance;
		double twist;
	};

public:
	CameraPolarView();
	virtual ~CameraPolarView();

public:

	void resetVue();
	void affiche();
	virtual void pause();
	virtual void unpause();
	void rotationZ_obs(double angle);
	void tourner_tete(int dir, double angle);
	void zoom(double pas); //permet d'avancer ou de reculer dans la scene
	void translation_obs(int dir, double pas);
	void rotation3D(double angle, double* axeVect, double* axePt, double* monPt, double* result);
	void polar_view(double azimut, double elevation, double distance, double twist);

	virtual void maj(){Camera::maj();}

private:

	PolarParam _polarParam;
	CB_Interraction* _interraction;
	


};


#endif;
