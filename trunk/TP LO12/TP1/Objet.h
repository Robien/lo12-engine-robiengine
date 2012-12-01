#ifndef _OBJET_H	
#define _OBJET_H

#include "AbstractObjet.h"
#include "Face.h"

class Objet : public AbstractObjet
{
public:
	Objet(std::string = "nom_defaut");
	Objet(Matrice<GLdouble>* matrice);
	virtual ~Objet();

	virtual void affiche();

	void addFace(Face* face);

private:
	std::vector<Face*> _listeFace;
	std::string name;
};


#endif