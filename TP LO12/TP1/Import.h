#ifndef _IMPORT_H	
#define _IMPORT_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Objet.h"
#include "Material.h"

class Import
{
public:
	Import(void);
	virtual ~Import(void);

	std::vector<AbstractObjet* >* importer(std::string namefile);
	
private : 
	std::vector<Material* >* importerMaterial(std::string namefile);

	//fonctions outil
	void sauterLigne(std::istream& is);
	bool sauterLigneCommentaire(std::istream& is);
	std::string getPath(std::string filename);
	std::string doubleSlash(std::string s);
	std::string remplacerSlash(std::string s);
	std::vector<std::string> splitEspace(std::string s);
	std::string supprimerEspaceAvant(std::string s);

};

#endif
