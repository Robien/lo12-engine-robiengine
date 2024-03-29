#ifndef _IMPORT_H	
#define _IMPORT_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Objet.h"
#include "Material.h"
#include "Percent.h"

class Import
{
public:
	Import();
	virtual ~Import();

	std::vector<AbstractObjet* >* importer(std::string namefile);
	int addSizeOfFile(std::string namefile);
	void endImport();
private : 
	void setAvancement(int avan);
	std::vector<Material* >* importerMaterial(std::string namefile);
	bool isAxe(std::string nomObjet);
	std::vector<std::string> extraireNomAxe(std::string s);
	//fonctions outil
	void sauterLigne(std::istream& is);
	bool sauterLigneCommentaire(std::istream& is);
	std::string getPath(std::string filename);
	std::string doubleSlash(std::string s);
	std::string remplacerSlash(std::string s);
	std::vector<std::string> splitEspace(std::string s);
	std::string supprimerEspaceAvant(std::string s);

private : 
	bool _chargementCree;
	int _tailleFichierTotal;
	int _avancement;
	Percent* _pourcent;

};

#endif
