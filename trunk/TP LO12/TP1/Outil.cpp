#include "Outil.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

int Outil::getHauteurFenetre()
{
	GLint m_viewport[4];
	glGetIntegerv( GL_VIEWPORT, m_viewport );
	return m_viewport[3];
}

int Outil::getLargeurFenetre()
{
	GLint m_viewport[4];

	glGetIntegerv( GL_VIEWPORT, m_viewport );
	return m_viewport[2];
}


std::string Outil::readFile(std::string fileName)
{
	std::ifstream fichier(fileName.c_str(), std::ios::in);

	if(fichier.fail())
	{
		std::cout << "Le fichier " << fileName << " n'existe pas !" << std::endl;
		getchar();
		exit(0);
	}
	
    std::string ligne;
	std::ostringstream oss;
	while(getline(fichier, ligne))
	{
		oss << ligne << std::endl;

	}

	 return oss.str();
}


Vector3d<GLdouble> Outil::mult(Vector3d<GLdouble>& vect, Matrice<GLdouble>& mat)
{
	Vector3d<GLdouble> res;

	res.setX(vect.getX() * mat.getVector16().at(0) + vect.getY() * mat.getVector16().at(1) + vect.getZ() * mat.getVector16().at(2));
	res.setY(vect.getX() * mat.getVector16().at(3) + vect.getY() * mat.getVector16().at(4) + vect.getZ() * mat.getVector16().at(5));
	res.setZ(vect.getX() * mat.getVector16().at(6) + vect.getY() * mat.getVector16().at(7) + vect.getZ() * mat.getVector16().at(8));

	return res;
}