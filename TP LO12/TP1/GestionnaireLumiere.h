#pragma once
class GestionnaireLumiere
{
public:
	GestionnaireLumiere();
	virtual ~GestionnaireLumiere();

	void def_sources(int i);
	void def_modele();
	void def_matiere(int i);
	void defAllSources();
};

