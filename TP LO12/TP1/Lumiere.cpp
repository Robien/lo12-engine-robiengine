#include "Lumiere.h"
#include "Shader.h"

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
Lumiere::Lumiere(GLenum id, std::string name) :AbstractObjet(name), _allure_faisceau(), _id(id)
{
	_afficheSphere = false;
	_active = false;
	_infini = false;
	_sphere = gluNewQuadric();
}

Lumiere::Lumiere(GLenum id, Matrice<GLdouble>* mat, Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, AllureFaisceau alf, bool infini, std::string name) : AbstractObjet(mat,name), _id(id)
{
	_infini = infini;
	_sphere = gluNewQuadric();
	_afficheSphere = true;
	_active = true;
	_ambiante = amb;
	_couleur = cou;
	_allure_faisceau = alf;
}
Lumiere::Lumiere(GLenum id, Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, AllureFaisceau alf, bool infini, std::string name) : AbstractObjet(name), _id(id)
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


void Lumiere::def_sources()
{            
	
	if(_active)
	{
		glPushMatrix();
		//glLoadIdentity();
		glMultMatrixd(matrice().getMat());
		//glLoadMatrixd(matriceAbsolue().getMat());
		GLfloat propc[4];
		propc[0] = _ambiante.getX();
		propc[1] = _ambiante.getY();
		propc[2] = _ambiante.getZ();
		propc[3] = 1; // alpha
		glLightfv(_id,GL_AMBIENT,propc);

		propc[0] = _couleur.getX();
		propc[1] = _couleur.getY();
		propc[2] = _couleur.getZ();
		glLightfv(_id,GL_DIFFUSE,propc);
		glLightfv(_id,GL_SPECULAR,propc);
		//_vect = matriceAbsolue().getPosition();

		/*GLdouble* newData = (GLdouble*) malloc(16*sizeof(GLdouble));
		glGetDoublev(GL_MODELVIEW_MATRIX, newData);
		Matrice<GLdouble> m(newData);
*/
		//m.print();
		//std::cout <<  m.getPosition().getX() << std::endl;
	//	GLfloat propp[4]; 
	//	propp[0] = 0;
	//	propp[1] =0;
	//	propp[2] = 0;
	////	std::cout <<  _vect.getZ() << std::endl;
	//	if(_infini)
	//	{propp[3] = 0;}
	//	else
	//	{propp[3] = 1;}
	//	
	//	glLightfv(_id,GL_POSITION,propp);
	//	//_vect = matriceAbsolue().getDirection();
	//	propp[0] = 1;
	//	propp[1] = 0;
	//	propp[2] = 0;
	//	propp[3] = 1;
	//	glLightfv(_id,GL_SPOT_DIRECTION,propp);
		glLightf(_id,GL_SPOT_CUTOFF,_allure_faisceau.getAngle());
		glLightf(_id,GL_SPOT_EXPONENT,_allure_faisceau.getCoefK());
		glEnable(_id);

		glPopMatrix();
	}
	else
	{
		glDisable(_id);
	}
}

unsigned int Lumiere::affiche()
{
	unsigned int nbPointAffiche = 0;
	if(_afficheSphere && _active)
	{
		glMatrixMode(GL_MODELVIEW);	
		ShaderEtat::get()->desactive(); //désactiver le shader
		glDisable(GL_LIGHTING);
		glColor3d(_couleur.getX(), _couleur.getY(), _couleur.getZ());				

		glPushMatrix();
		glMultMatrixd(getMatrice()->getMat());
		nbPointAffiche += 30; //ouais, c'est au hazard
		gluSphere(_sphere, 0.2, 10, 10);

		/*afficher la direction du vecteur*/
		glBegin(GL_LINES);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(1,0,0);
		glColor3f(1,1,1);
		glEnd();
		ShaderEtat::get()->active(); //activer le shader
		GLfloat propp[4]; 
		propp[0] = 0;
		propp[1] =0;
		propp[2] = 0;
	//	std::cout <<  _vect.getZ() << std::endl;
		if(_infini)
		{propp[3] = 0;}
		else
		{propp[3] = 1;}
		
		glLightfv(_id,GL_POSITION,propp);
		//_vect = matriceAbsolue().getDirection();
		propp[0] = 1;
		propp[1] = 0;
		propp[2] = 0;
		propp[3] = 1;
		glLightfv(_id,GL_SPOT_DIRECTION,propp);




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

 void Lumiere::init()
{
	glPushMatrix();
		glLoadMatrixd(matrice().getMat());
		GLfloat propp[4]; 
		propp[0] = 0;
		propp[1] = 0;
		propp[2] = 0;
		if(_infini)
		{propp[3] = 0;}
		else
		{propp[3] = 1;}
		
		glLightfv(_id,GL_POSITION,propp);
		propp[0] = 1;
		propp[1] = 0;
		propp[2] = 0;
		propp[3] = 1;
		glLightfv(_id,GL_SPOT_DIRECTION,propp);
	
		glPopMatrix();
}

