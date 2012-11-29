#ifndef _ABSTRACT_OBJ_H	
#define _ABSTRACT_OBJ_H

class AbstractObjet
{
public:
	AbstractObjet();
	virtual ~AbstractObjet();

	void affiche() = 0;

};


#endif