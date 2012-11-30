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

	std::vector<Objet* >* importer(std::string namefile);
	std::vector<Material* >* importerMaterial(std::string namefile);
private : 

	void sauterLigne(std::istream& is);
	bool sauterLigneCommentaire(std::istream& is);
	std::string getPath(std::string filename);

};

#endif
