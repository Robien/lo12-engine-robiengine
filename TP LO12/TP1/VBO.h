#ifndef _VBO_H
#define _VBO_H

#include <vector>
#include "Outil.h"
#include "Vector3d.h"
#include "Vector2d.h"
#include "Material.h"



class VBO
{
private: // il faut utiliser VBO manager pour créer des VBOs
	VBO(GLuint id);
	friend class VBOMangaer;
public:
		virtual ~VBO();

		void setMaterial(Material* material);
public:

	void addPoint(Vector3d<GLdouble>* point, Vector2d<GLdouble>* texture, Vector3d<GLdouble>* normale);
	void init();
	unsigned int affiche();
	unsigned int afficheFilted();
	bool isInit();

private:
	std::vector<GLdouble> _listePoints;
	std::vector<GLdouble> _listeTextures;
	std::vector<GLdouble> _listeNormales;
	GLuint _id;
	bool _isInit;

	Material* _material;

};

#endif