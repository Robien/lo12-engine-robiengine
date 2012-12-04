#ifndef _GESTION_ECLAIRAGE_H
#define _GESTION_ECLAIRAGE_H

#include <iostream>
#include <vector>
#include "const.h"
#include "Singleton.h"
#include "Lumiere.h"
#include "Interactions.h"




class GestionnaireLumiere : public Singleton<GestionnaireLumiere>
{
public:
	GestionnaireLumiere();

	Lumiere* newLumiere(Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, GLdouble coefk, GLdouble angle, Matrice<GLdouble>* mat = NULL, bool infini = false, std::string name = "lumiere_defaut");
	void setLumiereAmbiante(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha = 1);
	void def_modele();
	void defAllSources();
	void toggleLumiere(unsigned int i);

private:
	GLenum lumiere_i(unsigned int i);
private:
	std::vector<Lumiere* > _listLumiere;
	GLfloat  _lumiereAmbiante[4];
};



class LumiereInterraction : public CB_Interraction
{
public:
	LumiereInterraction(){}
	virtual ~LumiereInterraction(){}
public:
	virtual void eventsSpecialKey(int key, int x, int y)
	{
		switch(key)
		{
		case GLUT_KEY_F8:	 GestionnaireLumiere::get()->toggleLumiere(0);	break;
		case GLUT_KEY_F9:	 GestionnaireLumiere::get()->toggleLumiere(1);	break;

		}
	}
	virtual void eventsKey(unsigned char key, int x, int y){}
	virtual void eventsMouse(int boutton, int etat, int x, int y){}
	virtual void eventsMotionMouse(int x, int y){}
	virtual void idle(){}
	virtual void reshape(int largeur, int hauteur){}
	virtual void dessine_scene(){}

};



#endif