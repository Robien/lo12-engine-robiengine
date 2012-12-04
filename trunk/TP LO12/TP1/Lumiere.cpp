#include "Lumiere.h"

/*----------------------Definition Allure Faisceau-----------------------------*/
AllureFaisceau::AllureFaisceau(GLdouble k, GLdouble theta)
{
	_k = k;
	_theta = theta;
}
AllureFaisceau::~AllureFaisceau()
{
}
GLdouble AllureFaisceau::getCoefK()
{
	return _k;
}
GLdouble AllureFaisceau::getAngle()
{
	return _theta;
}

/*----------------------Definition Lumiere-----------------------------*/
Lumiere::Lumiere(std::string name) :AbstractObjet(name), _allure_faisceau()
{
	_sphere = gluNewQuadric();
}

Lumiere::Lumiere(Matrice<GLdouble>* mat, Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, AllureFaisceau alf, std::string name) : AbstractObjet(mat,name)
{
	_sphere = gluNewQuadric();
	_afficheSphere = true;
	_active = true;
	_ambiante = amb;
	_couleur = cou;
	_allure_faisceau = alf;
}
Lumiere::Lumiere(Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, AllureFaisceau alf, std::string name) : AbstractObjet(name)
{
	_sphere = gluNewQuadric();
	_afficheSphere = true;
	_active = true;
	_ambiante = amb;
	_couleur = cou;
	_allure_faisceau = alf;
}

Lumiere::~Lumiere()
{
	gluDeleteQuadric(_sphere);
}

void Lumiere::setAfficheSphere(bool aff)
{
	_afficheSphere=aff;
}


void Lumiere::def_sources(GLenum source)
{            

	if(_active)
	{
		GLfloat propc[4];
		propc[0] = _ambiante.getX();
		propc[1] = _ambiante.getY();
		propc[2] = _ambiante.getZ();
		propc[3] = 1; // alpha
		glLightfv(source,GL_AMBIENT,propc);

		propc[0] = _couleur.getX();
		propc[1] = _couleur.getY();
		propc[2] = _couleur.getZ();
		glLightfv(source,GL_DIFFUSE,propc);
		glLightfv(source,GL_SPECULAR,propc);
		Vector3d<GLdouble>* vect = new Vector3d<GLdouble>();
		*vect = getMatrice()->getPosition();
		GLfloat propp[4]; 
		propp[0] = vect->getX();
		propp[1] = vect->getY();
		propp[2] = vect->getZ();
		propp[3] = 1;
		glLightfv(source,GL_POSITION,propp);
		//vect = new Vector3d<GLdouble>();
		*vect = getMatrice()->getDirection();
		propp[0] = vect->getX();
		propp[1] = vect->getY();
		propp[2] = vect->getZ();
		propp[3] = 1;
		glLightfv(source,GL_SPOT_DIRECTION,propp);
		glLightf(source,GL_SPOT_CUTOFF,_allure_faisceau.getAngle());
		glLightf(source,GL_SPOT_EXPONENT,_allure_faisceau.getCoefK());
		glEnable(source);
		//TODO : y'a une fuite ici, je ne sais pas trop pourquoi comment, mais le delete fait crash
		//delete vect;

	}
	else
	{
		glDisable(source);
	}
}

void Lumiere::affiche()
{
	if(_afficheSphere && _active)
	{
		glMatrixMode(GL_MODELVIEW);	
		glDisable(GL_LIGHTING);
		glColor3d(_couleur.getX(), _couleur.getY(), _couleur.getZ());				

		glPushMatrix();
		glMultMatrixd(getMatrice()->getMat());
		gluSphere(_sphere, 0.1, 10, 10);
		glEnable(GL_LIGHTING);
		//on affiche les objets fils
		 for (unsigned int i = 0; i < getFils()->size(); ++i)
		 {
			 getFils()->at(i)->affiche();
		 }

		glPopMatrix();
	}
	else
	{
		AbstractObjet::affiche();
	}

}

void  Lumiere::toggle()
{
	_active = !_active;
}



