#pragma once

#include "Observateur.h"
#include "Affiche.h"
#include "Scene.h"
#include "Eclairage.h"
#include "Outil.h"

class Tp 
{

public:
	Tp();
	virtual ~Tp();

public:
	void run(char* filename, int verbose);

private:
	void init();

private:

	Observateur* _ob;
	Affiche* _affiche;
	Scene* _scene;/* description de la scene */
	Eclairage* _eclairage;
	Outil* _gestionTexture;

};





