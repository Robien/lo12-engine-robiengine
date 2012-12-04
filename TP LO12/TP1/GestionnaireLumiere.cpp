#include "GestionnaireLumiere.h"

GestionnaireLumiere::GestionnaireLumiere() : _listLumiere()
{
	_lumiereAmbiante[0] = 0.8;
	_lumiereAmbiante[1] = 0.8;
	_lumiereAmbiante[2] = 0.8;
	_lumiereAmbiante[3] = 1;
	Interactions::get()->addEventCallBack(new LumiereInterraction());
}

Lumiere* GestionnaireLumiere::newLumiere(Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, GLdouble coefk, GLdouble angle, Matrice<GLdouble>* mat,  bool infini, std::string name )
{
	Lumiere* lu;
	if(mat == NULL)
	{
		lu = new Lumiere(amb,cou, AllureFaisceau(coefk, angle),infini,name);
	}
	else
	{
		lu = new Lumiere(mat,amb,cou,AllureFaisceau(coefk, angle),infini, name);
	}
	_listLumiere.push_back(lu);
	return lu;
}

void GestionnaireLumiere::def_modele()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,_lumiereAmbiante);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}


void GestionnaireLumiere::defAllSources()
{
	for (unsigned int i = 0; i < _listLumiere.size(); ++i)
	{
		_listLumiere.at(i)->def_sources(lumiere_i(i));

	}
}

GLenum GestionnaireLumiere::lumiere_i(unsigned int i)
{
	GLenum source;
	switch (i) {
	case 0:
		source=GL_LIGHT0;
		break;
	case 1:
		source=GL_LIGHT1;
		break;
	case 2:
		source=GL_LIGHT2;
		break;
	case 3:
		source=GL_LIGHT3;
		break;
	case 4:
		source=GL_LIGHT4;
		break;
	case 5:
		source=GL_LIGHT5;
		break;
	case 6:
		source=GL_LIGHT6;
		break;
	case 7:
		source=GL_LIGHT7;
		break;
	}

	if (i<=7)
	{  
		return(source);	
	}
	else 
	{
		std::cout << "Attention : le nombre de sources lumineuses est depassé" << std::endl;
		return ((GLenum)GL_LIGHT7);
	}
}

void GestionnaireLumiere::setLumiereAmbiante(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
	_lumiereAmbiante[0] = r;
	_lumiereAmbiante[1] = g;
	_lumiereAmbiante[2] = b;
	_lumiereAmbiante[3] = alpha;
}

void GestionnaireLumiere::toggleLumiere(unsigned int i)
{
	_listLumiere.at(i)->toggle();
}