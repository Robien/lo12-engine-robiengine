#ifndef _CAMERAPILOT_H	
#define _CAMERAPILOT_H

#include "Camera.h"
#include "const.h"
#include "Interactions.h"


class CameraPilotView : public Camera
{
public:
	struct PilotParam
	{
		double posx;
		double posy;
		double posz;
		double roulis;
		double tangage;
		double lacet;
	};

public:
	CameraPilotView();
	virtual ~CameraPilotView();

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
	void pilot_view(double posx, double posy, double posz, double roulis, double tangage, double lacet);

	virtual void maj(){Camera::maj();}

private:

	PilotParam _pilotParam;
	CB_Interraction* _interraction;
	


};


#endif;
