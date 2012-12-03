#include "GestionnaireTexture.h"
#include "Pngloader.h"
#include "Texture.h"


GLuint GestionnaireTexture::addTexture(std::string filename)
{
	Texture* texture = new Texture();
	texture->setFilename(filename);

	// verifier si la texture n'est pas déja chargée
	int idexist = exist(&filename);
	if (idexist != -1)
	{
		std::cout << "Texture " << filename << " deja charge avec le numero :\t" <<  _listTexture.at(idexist) << std::endl; 
		delete texture;
		return _listTexture.at(idexist)->getGlnum();
	}

	if(Pngloader::ReadPNGFromFile(texture))
	{
		std::cout << "Fichiers introuvables ! : " << filename << std::endl;
		return -1;
	}

	glGenTextures(1, texture->getPtGlnum());

	std::cout << "Nouvelle texture : "<< filename << " numero :\t" << texture->getGlnum() << std::endl; 
	glBindTexture(GL_TEXTURE_2D,texture->getGlnum());
	glTexImage2D(GL_TEXTURE_2D, 0,texture->getInternalFormat(), texture->getWidth(), texture->getHeight(), 0, texture->getFormat(), GL_UNSIGNED_BYTE, texture->getTexels());
	/* filtre normal
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	*/
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBindTexture(GL_TEXTURE_2D, 0);
	_listTexture.push_back(texture);

	return texture->getGlnum();
}


int GestionnaireTexture::exist(std::string* filename)
{
	int res = -1;

	for (unsigned int i = 0; (res==-1) && i < _listTexture.size(); ++i)
	{
		if (_listTexture.at(i)->getFilename() == *filename)
		{
			res = i;
		}
	}
	return res;
}