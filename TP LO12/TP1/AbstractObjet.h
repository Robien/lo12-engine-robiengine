#ifndef _ABSTRACT_OBJ_H	
#define _ABSTRACT_OBJ_H

#include <vector>
#include "Matrice.h"
#include "const.h"
#include <iostream>
#include "Collider.h"


class AbstractObjet
{
public:
	AbstractObjet(std::string str = "nom_defaut");
	AbstractObjet(Matrice<GLdouble>* matrice, std::string str = "nom_defaut");
	virtual ~AbstractObjet();

	virtual unsigned int affiche();
	virtual void majPos();

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
	Matrice<GLdouble>& matriceAbsolue()
	{
		return *_matriceAbsolue;
	}
	virtual void toggleFilted();
	virtual void toggleVBO();

public:
	std::vector<AbstractObjet*>* getFils();
	AbstractObjet* getPere();
	virtual void majCollider();

protected:
	bool _isFilted;
	bool _isVboActive;
	Collider* _collider;
	std::string _nom;

private:
	std::vector<AbstractObjet*> _fils;
	AbstractObjet* _pere;
	Matrice<GLdouble>* _matrice;

	Matrice<GLdouble>* _matriceAbsolue;
	


};


#endif