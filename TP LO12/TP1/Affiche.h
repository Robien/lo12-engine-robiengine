#ifndef AFFICHE_H
#define AFFICHE_H

#include "Scene.h"
#include "Eclairage.h"


class Affiche
{

public:
	Affiche(Scene* scene, Eclairage* eclairage);
	virtual ~Affiche();

public:

	void dessine_face(Scene::INDICE_FACE iface);
	void dessine_objet(Scene::OBJET objet);
	void dessine_scene();
	void dessine_skybox(Scene::MCOORD pos);

private:
	void dessine_repere();

	Scene* _scene;
	Eclairage* _eclairage;


};
#endif

