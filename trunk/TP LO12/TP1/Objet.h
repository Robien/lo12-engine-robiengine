#ifndef _OBJET_H	
#define _OBJET_H

#include "AbstractObjet.h"
#include "Face.h"
#include "VBO.h"
#include <vector>

class Objet : public AbstractObjet
{
public:
	Objet(std::string = "nom_defaut");
	Objet(Matrice<GLdouble>* matrice);
	virtual ~Objet();

public:
	virtual unsigned int affiche();

	void addFace(Face* face);

	virtual void toggleFilted();
	virtual void toggleVBO();

private:
	std::vector<Face*> _listeFace;
	std::string name;
	std::vector<VBO*> _vbo;

private:
	Material* _oldMaterial;

	virtual bool isInCollisionWithFace(AbstractObjet* objet);

private:
	GLdouble* _mat;// pour ne pas a delete a chaque frame
};


#endif