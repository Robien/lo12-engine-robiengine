#pragma once

#include "Observateur.h"
#include "Scene.h"
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
	Scene* _scene;/* description de la scene */
	Outil* _gestionTexture;

};





