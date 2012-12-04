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
	void run();

private:

	Scene* _scene;/* description de la scene */

};





