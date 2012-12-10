#include "VBO.h"
#include "VBOMangaer.h"


VBO::VBO(GLuint id) : _id(id), _isInit(false)
{
}


VBO::~VBO()
{
}


void VBO::addPoint(Vector3d<GLdouble>* point, Vector2d<GLdouble>* texture)
{
	_listePoints.push_back(point->getX());
	_listePoints.push_back(point->getY());
	_listePoints.push_back(point->getZ());

	_listeTextures.push_back(texture->getX());
	_listeTextures.push_back(texture->getY());
}

bool VBO::isInit()
{
	return _isInit;
}
void VBO::init()
{

	VBOMangaer::get()->alloueEtCharge(_id, _listePoints.data(), _listePoints.size() * sizeof(GLdouble), _listeTextures.data(), _listeTextures.size() * sizeof(GLdouble));
	_isInit = true;


}
void VBO::affiche()
{


	GLdouble *pos_vbo = NULL;


	glBindBuffer(GL_ARRAY_BUFFER, _id);

	glVertexPointer(3, GL_DOUBLE, 0, BUFFER_OFFSET(0));
	glTexCoordPointer(2, GL_DOUBLE, 0, BUFFER_OFFSET(_listePoints.size() * sizeof(GLdouble)));
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	glDrawArrays(GL_POLYGON, 0, _listePoints.size()/3);


}

unsigned int VBO::afficheSome(unsigned int first)
{


	GLdouble *pos_vbo = NULL;


	glBindBuffer(GL_ARRAY_BUFFER, _id);

	glVertexPointer(3, GL_DOUBLE, 0, BUFFER_OFFSET(first));
	glTexCoordPointer(2, GL_DOUBLE, 0, BUFFER_OFFSET(first + _listePoints.size() * sizeof(GLdouble)));
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	glDrawArrays(GL_POLYGON, first, _listePoints.size()/3);

	return (_listePoints.size() + _listeTextures.size()) * sizeof(GLdouble);
}