#ifndef _ABSTRACT_OBJ_H	
#define _ABSTRACT_OBJ_H

#include <list>

class AbstractObjet
{
public:
	AbstractObjet();
	virtual ~AbstractObjet();

	virtual void affiche() = 0;

public:
	void addFils(AbstractObjet* fils);
	inline void attache(AbstractObjet* fils)
	{
		addFils(fils);
	}
	void removeFils(AbstractObjet* fils);
	inline void dettache(AbstractObjet* fils)
	{
		removeFils(fils);
	}

protected:
	std::list<AbstractObjet*> getFils();

private:
	std::list<AbstractObjet*> _fils;

};


#endif