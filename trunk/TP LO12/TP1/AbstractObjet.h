#ifndef _ABSTRACT_OBJ_H	
#define _ABSTRACT_OBJ_H

#include <list>
#include "Matrice.h"
#include "Outil.h"

class AbstractObjet
{
public:
	AbstractObjet();
	AbstractObjet(Matrice<GLdouble>* matrice);
	virtual ~AbstractObjet();

	virtual void affiche() = 0;

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
	std::list<AbstractObjet*> getFils();

private:
	std::list<AbstractObjet*> _fils;
	Matrice<GLdouble>* _matrice;

};


#endif