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
	_afficheSphere = false;
	_active = false;
	_infini = false;
	_sphere = gluNewQuadric();
}

Lumiere::Lumiere(Matrice<GLdouble>* mat, Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, AllureFaisceau alf, bool infini, std::string name) : AbstractObjet(mat,name)
{
	_infini = infini;
	_sphere = gluNewQuadric();
	_afficheSphere = true;
	_active = true;
	_ambiante = amb;
	_couleur = cou;
	_allure_faisceau = alf;
}
Lumiere::Lumiere(Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, AllureFaisceau alf, bool infini, std::string name) : AbstractObjet(name)
{
	_infini = infini;
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
		_vect = getMatrice()->getPosition();
		GLfloat propp[4]; 
		propp[0] = _vect.getX();
		propp[1] = _vect.getY();
		propp[2] = _vect.getZ();
		if(_infini)
		{propp[3] = 0;}
		else
		{propp[3] = 1;}
		
		glLightfv(source,GL_POSITION,propp);
		_vect = getMatrice()->getDirection();
		propp[0] = _vect.getX();
		propp[1] = _vect.getY();
		propp[2] = _vect.getZ();
		propp[3] = 1;
		glLightfv(source,GL_SPOT_DIRECTION,propp);
		glLightf(source,GL_SPOT_CUTOFF,_allure_faisceau.getAngle());
		glLightf(source,GL_SPOT_EXPONENT,_allure_faisceau.getCoefK());
		glEnable(source);

	}
	else
	{
		glDisable(source);
	}
}

unsigned int Lumiere::affiche()
{
	unsigned int nbPointAffiche = 0;
	if(_afficheSphere && _active)
	{
		glMatrixMode(GL_MODELVIEW);	
		glDisable(GL_LIGHTING);
		glColor3d(_couleur.getX(), _couleur.getY(), _couleur.getZ());				

		glPushMatrix();
		glMultMatrixd(getMatrice()->getMat());
		nbPointAffiche += 30; //ouais, c'est au hazard
		gluSphere(_sphere, 0.1, 10, 10);
		/*afficher la direction du vecteur*/
		_vect = getMatrice()->getDirection();
		glBegin(GL_LINES);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(_vect.getX(),_vect.getY(),_vect.getZ());
		glColor3f(1,1,1);
		glEnd();

		glEnable(GL_LIGHTING);
		//on affiche les objets fils
		 for (unsigned int i = 0; i < getFils()->size(); ++i)
		 {
			 nbPointAffiche += getFils()->at(i)->affiche();
		 }

		glPopMatrix();
	}
	else
	{
		nbPointAffiche += AbstractObjet::affiche();
	}

	return nbPointAffiche;
}

void  Lumiere::toggle()
{
	_active = !_active;
}



