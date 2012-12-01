#ifndef _ABSTRACT_OBJ_H	
#define _ABSTRACT_OBJ_H

#include <vector>
#include "Matrice.h"
#include "const.h"
#include <iostream>


class AbstractObjet
{
public:
	AbstractObjet(std::string str = "nom_defaut");
	AbstractObjet(Matrice<GLdouble>* matrice);
	virtual ~AbstractObjet();

	virtual void affiche();

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

public:
	Matrice<GLdouble>* getMatrice();
	void setMatrice(Matrice<GLdouble>* matrice);

protected:
	std::vector<AbstractObjet*>* getFils();

private:
	std::vector<AbstractObjet*> _fils;
	Matrice<GLdouble>* _matrice;
	std::string _nom;

};


#endif