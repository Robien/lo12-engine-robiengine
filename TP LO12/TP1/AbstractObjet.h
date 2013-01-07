#ifndef _ABSTRACT_OBJ_H	
#define _ABSTRACT_OBJ_H

#include <vector>
#include "Matrice.h"
#include "const.h"
#include <iostream>
#include "Collider.h"
#include "Vector3d.h"
#include "AxeAnimation.h"

class Animation;

class AbstractObjet
{
public:
	AbstractObjet(std::string str = "nom_defaut");
	AbstractObjet(Matrice<GLdouble>* matrice, std::string str = "nom_defaut");
	virtual ~AbstractObjet();

	virtual unsigned int affiche();
	virtual void majPos();
	std::string getNom();
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
	void addPointCollsion(Vector3d<GLdouble>* pt);
	void addAxe(AxeAnimation* axe);
	bool isInCollisionWith(AbstractObjet* objet);
	Collider* getCollider();

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

public:
	virtual void toggleFilted();
	virtual void toggleVBO();

public:
	std::vector<AbstractObjet*>* getFils();
	AbstractObjet* getPere();
	virtual void majCollider();
	Vector3d<GLdouble>* getScale();

public:
	void setAnimation(Animation* anim);

protected:
	bool _isFilted;
	bool _isVboActive;
	Collider* _collider;
	std::string _nom;
	std::vector<Vector3d<GLdouble>* >& getListePointsCollision();

private:
	std::vector<AbstractObjet*> _fils;
	AbstractObjet* _pere;
	Matrice<GLdouble>* _matrice;
	std::vector<Vector3d<GLdouble>* > _listPointsCollision;
	std::vector<AxeAnimation* > _listAxes;
	Matrice<GLdouble>* _matriceAbsolue;
	virtual bool isInCollisionWithFace(AbstractObjet* objet);

protected:
	Animation* _animation;

};


#endif