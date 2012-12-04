#ifndef _CAMERALOOKAT_H	
#define _CAMERALOOKAT_H

#include "Camera.h"
#include "const.h"


class CameraLookAt : public Camera
{
public:
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
	CameraLookAt();
	virtual ~CameraLookAt();

public:

	void resetVue();
	void affiche();
	void rotationZ_obs(double angle);
	void tourner_tete(int dir, double angle);
	void zoom(double pas); //permet d'avancer ou de reculer dans la scene
	void translation_obs(int dir, double pas);
	void rotation3D(double angle, double* axeVect, double* axePt, double* monPt, double* result);


private:

	LookAtParam _lookAtParam;




};


#endif;
