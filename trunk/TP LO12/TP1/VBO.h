#ifndef _VBO_H
#define _VBO_H

#include <vector>
#include "Outil.h"
#include "Vector3d.h"
#include "Vector2d.h"



class VBO
{
private: // il faut utiliser VBO manager pour créer des VBOs
	VBO(GLuint id);
	friend class VBOMangaer;
public:
		virtual ~VBO();
public:

	void addPoint(Vector3d<GLdouble>* point, Vector2d<GLdouble>* texture);
	void init();
	void affiche();
	bool isInit();

private:
	std::vector<GLdouble> _listePoints;
	std::vector<GLdouble> _listeTextures;
	GLuint _id;
	bool _isInit;

};

#endif