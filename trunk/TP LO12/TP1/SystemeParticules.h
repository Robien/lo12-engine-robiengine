#ifndef _SYST_PARTICULES_H	
#define _SYST_PARTICULES_H

#include "AbstractObjet.h"
#include "Vector3d.h"
#include "const.h"
#include <iostream>
#include <list>


class Particules //classe particule
{
public:
	Particules();
	virtual ~Particules();
	void initParticles();
	void affiche();
	bool update();



private:
	bool _active; // Active
	GLdouble _dureeVie; // Durée de vie
	GLdouble _fade; // Vitesse de disparition
	Vector3d<GLdouble> _couleur; // Valeurs RGB pour la couleur
	Vector3d<GLdouble> _position; // Position
	Vector3d<GLdouble> _direction; // Vecteur de déplacement
	Vector3d<GLdouble> _gravite; // Gravité
};

class SystemeParticules : public AbstractObjet
{


public:
	SystemeParticules(bool boucle = true, int nombreParticules = 1000,  std::string name = "systeme_particule_defaut");
	virtual ~SystemeParticules();
	void restart();
	void start();
	void stop();
	virtual void affiche();
private:
	void initSysteme();
private:
	int _densite;
	bool _active;
	bool _boucle;
	std::list<Particules* > _listParticule;
};


#endif
