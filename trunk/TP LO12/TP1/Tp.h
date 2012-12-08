#ifndef _TP_H	
#define _TP_H

#include "Scene.h"

// Une classe qui configure le jeu
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


#endif


