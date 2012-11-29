#ifndef _IMPORT_H	
#define _IMPORT_H

#include "Objet.h"
#include <iostream>
#include <vector>

class Import
{
public:
	Import(void);
	virtual ~Import(void);

	std::vector<Objet*>* importer(std::string namefile);

};

#endif
