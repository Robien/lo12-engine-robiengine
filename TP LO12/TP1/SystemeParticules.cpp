#include "SystemeParticules.h"


SystemeParticules::SystemeParticules(bool boucle,int nombreParticules, std::string name) : AbstractObjet(name), _listParticule()
{
	_densite = nombreParticules;
	_boucle=boucle;
	_active = false;
	initSysteme();
}


SystemeParticules::~SystemeParticules()
{
	_listParticule.clear();
}
void SystemeParticules::start()
{
	if(_listParticule.size() == 0)
	{
		initSysteme();
	}
	_active = true;
}
void SystemeParticules::restart()
{
	initSysteme();
	_active = true;
}
void SystemeParticules::stop()
{
	_active = false;
}

void SystemeParticules::initSysteme()
{
	_listParticule.clear();
	for(int i = 0; i < _densite; ++i)
	{
		Particules* part = new Particules();
		_listParticule.push_back(part);
	}
}

void SystemeParticules::affiche()
{
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_DEPTH_TEST); //pour eviter des calculs
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glPushMatrix();
	glMultMatrixd(getMatrice()->getMat());
	if(_active)
	{
		for (std::list<Particules* >::iterator it = _listParticule.begin(); it != _listParticule.end(); ++it)
		{
			if (_isFilted)
			{
				glBegin(GL_LINE_LOOP); // affichage fils de fer
			}
			else
			{
				glBegin(GL_TRIANGLE_STRIP);
			}
				(*it)->affiche();
			glEnd();
			if(!(*it)->update())
			{
				if(_boucle)
				{
					(*it)->initParticles();
				}
				else
				{
					it = _listParticule.erase(it);
					--it;
				}
			}
		}
		if(_listParticule.size() == 0)
		{
			_active=false;
		}
	}

	//on affiche les objets fils
	for (unsigned int i = 0; i < getFils()->size(); ++i)
	{
		getFils()->at(i)->affiche();

	}

	glPopMatrix();

	
	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

}


/*---------------------Particule--------------------*/
Particules::Particules()
{
	initParticles();
}

Particules::~Particules()
{
}

void Particules::affiche()
{
	glColor4d(_couleur.getX(), _couleur.getY(), _couleur.getZ(), _dureeVie);
	//glBegin(GL_TRIANGLE_STRIP);
	glVertex3d(_position.getX()+0.1,_position.getY(),_position.getZ()+0.1); // Nord-Ouest
	glVertex3d(_position.getX()-0.1,_position.getY(),_position.getZ()+0.1); // Nord-Est
	glVertex3d(_position.getX()+0.1,_position.getY(),_position.getZ()-0.1); // Sud-Ouest
	glVertex3d(_position.getX()-0.1,_position.getY(),_position.getZ()-0.1); // Sud-Est
	//glEnd();
}



void Particules::initParticles()
{   
	_active = true;       // On rend la particule active
	_dureeVie = 1.0;   // Maximum de vie

	_fade = Outil::get()->random<GLdouble>(0.01,0.05);   // Vitesse de disparition aléatoire
	_couleur = Vector3d<GLdouble>(Outil::get()->random<GLdouble>(0.0,1.0),Outil::get()->random<GLdouble>(0.0,1.0),Outil::get()->random<GLdouble>(0.0,1.0));
	_position = Vector3d<GLdouble>(0,0,0);
	_direction = Vector3d<GLdouble>(Outil::get()->random<GLdouble>(-10.0,10.0),Outil::get()->random<GLdouble>(-10.0,10.0),Outil::get()->random<GLdouble>(10.0,20.0));
	_gravite = Vector3d<GLdouble>(0,0,-1);

}

bool Particules::update()
{   
	/* Déplacement */
	_position.setX(_position.getX() +  _direction.getX() /1000);
	_position.setY(_position.getY() +  _direction.getY() /1000);
	_position.setZ(_position.getZ() +  _direction.getZ() /1000);
	/* Gravité */
	_direction.setX(_direction.getX() + _gravite.getX());
	_direction.setY(_direction.getY() + _gravite.getY());
	_direction.setZ(_direction.getZ() + _gravite.getZ());

	/* "Vie" */
	_dureeVie -= _fade;

	return (_dureeVie>0); //retourne vrai si toujours vivante

}


