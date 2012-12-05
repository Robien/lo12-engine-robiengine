#ifndef _ABSTRACT_OBJ_H	
#define _ABSTRACT_OBJ_H

#include <vector>
#include "Matrice.h"
#include "const.h"
#include <iostream>
#include "Collider.h"

class Collider;

class AbstractObjet
{
public:
	AbstractObjet(std::string str = "nom_defaut");
	AbstractObjet(Matrice<GLdouble>* matrice, std::string str = "nom_defaut");
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

public:
	Matrice<GLdouble>* getMatrice();
	void setMatrice(Matrice<GLdouble>* matrice);
	Matrice<GLdouble>& matrice()
	{
		return *_matrice;
	}
	virtual void toggleFilted();

public:
	std::vector<AbstractObjet*>* getFils();
	AbstractObjet* getPere();
	void majCollider();

protected:
	bool _isFilted;
	Collider* _collider;

private:
	std::vector<AbstractObjet*> _fils;
	AbstractObjet* _pere;
	Matrice<GLdouble>* _matrice;
	std::string _nom;

	


};


#endif