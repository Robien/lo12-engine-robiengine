#pragma once
/*

Universite de Technologie de Compiegne

UV: LO12

FICHIER: Observateur.c

COMMENTAIRE:
Routines d'affichage

*/
#include "const.h"

class Scene;

class Observateur
{
public:
	Observateur();
	virtual ~Observateur();

public:
	enum TYPE_VIEW {POLAR_VIEW=1, PILOT_VIEW, LOOK_AT_VIEW,VIVE_LES_POMMES };
	struct PolarParam
	{
		double azimut;
		double elevation;
		double distance;
		double twist;
	};
	struct PilotParam
	{
		double posx;
		double posy;
		double posz;
		double roulis;
		double tangage;
		double lacet;
	};
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
	void maj();
	void resetVue();

public:

	/*void polarView(GLdouble distance, GLdouble azimut, GLdouble elevation, GLdouble twist);
	void pilotView(GLdouble planex, GLdouble planey, GLdouble planez, GLdouble roulis, GLdouble tangage, GLdouble lacet);*/

public:
	//void rotateAzimut(GLdouble angle);
	//void rotateHead(GLdouble angleLR, GLdouble angleUD);
	//void zoom(GLdouble facteur);
	//void translate (GLdouble x, GLdouble y, GLdouble z);

public :
	void polar_view(double azimut, double elevation, double distance, double twist);
	void pilot_view(double posx, double posy, double posz, double roulis, double tangage, double lacet);
	void place_observateur();
	void rotationZ_obs(double angle);
	void tourner_tete(int dir, double angle);
	void zoom(double pas);
	void translation_obs(int dir, double pas);
	void rotation3D(double angle, double* axeVect, double *axePt, double* monPt, double* result);
	void changeView();

private:
	//GLdouble _distance,  _azimut,  _elevation,  _twist;
	//GLdouble _planex,  _planey,  _planez,  _roulis,  _tangage,  _lacet;
	PolarParam _polarParam;
	PilotParam _pilotParam;
	LookAtParam _lookAtParam;
	TYPE_VIEW _typeView;
};

