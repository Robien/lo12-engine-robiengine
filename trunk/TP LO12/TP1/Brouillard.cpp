#include "Brouillard.h"


Brouillard::Brouillard() : _couleur(0,0,0)
{
	_densite = 0.35;
	_debut = 1.0;
	_fin = 500.0;
	_active = true;
	maj();
}


Brouillard::~Brouillard()
{
}


void Brouillard::setActive(bool ac)
{
	_active = false;
	maj();
}

void Brouillard::setDensite(float de)
{
	if(de < 0)
	{de=0;}
	_densite = de;
	maj();
}

void Brouillard::maj()
{
	if(_active)
	{
		glClearColor(_couleur.getX(),_couleur.getY(),_couleur.getZ(),1.0f);          // We'll Clear To The Color Of The Fog ( Modified )
		glFogi(GL_FOG_MODE, GL_LINEAR);        // Fog Mode
		glFogfv(GL_FOG_COLOR, _couleur.getCStyle());            // Set Fog Color
		glFogf(GL_FOG_DENSITY, _densite);              
		glHint(GL_FOG_HINT, GL_DONT_CARE);     
		glFogf(GL_FOG_START,_debut);             // Fog Start Depth
		glFogf(GL_FOG_END, _fin);               // Fog End Depth
		glEnable(GL_FOG);                   // Enables GL_FOG
	}
	else
	{
		glDisable(GL_FOG);  
	}
}