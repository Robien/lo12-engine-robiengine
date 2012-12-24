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