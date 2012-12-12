#ifndef _CAMERA_H	
#define _CAMERA_H

#include "Matrice.h"
#include "AbstractObjet.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void affiche();
	virtual unsigned int afficheFils();
	virtual void maj();

public:
	Matrice<GLdouble>* getMatrice();
	Matrice<GLdouble>& matrice();

public:
	void addFils(AbstractObjet* fils);
	inline void attache(AbstractObjet* fils)
	{
		addFils(fils);
	}
	void removeFils(AbstractObjet* fils);
	inline void dettache(AbstractObjet* fils)
	{
		removeFils(fils);
	}

	void addFils(std::vector<AbstractObjet*>* fils);
	inline void attache(std::vector<AbstractObjet*>* fils)
	{
		addFils(fils);
	}
	void removeFils(std::vector<AbstractObjet*>* fils);
	inline void dettache(std::vector<AbstractObjet*>* fils)
	{
		removeFils(fils);
	}

	std::vector<AbstractObjet*>* getFils();

private:
	Matrice<GLdouble> _matrice;
	std::vector<AbstractObjet*> _fils;

};


#endif