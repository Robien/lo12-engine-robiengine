#ifndef _GESTIONNAIRE_TEXTURE_H	
#define _GESTIONNAIRE_TEXTURE_H

#include "Singleton.h"
#include "Texture.h"
#include <vector>
#include <string>


class GestionnaireTexture : public Singleton<GestionnaireTexture>
{
public:

	GLuint addTexture(std::string filename);
	int exist(std::string* filename); //retourne son indice dans la listTexture ou -1 si n'existe pas

private:
	std::vector<Texture *> _listTexture;
};

#endif