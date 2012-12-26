#include "VBO.h"
#include "VBOMangaer.h"


VBO::VBO(GLuint id) : _id(id), _isInit(false)
{
}


VBO::~VBO()
{
}


void VBO::addPoint(Vector3d<GLdouble>* point, Vector2d<GLdouble>* texture, Vector3d<GLdouble>* normale)
{
	_listePoints.push_back(point->getX());
	_listePoints.push_back(point->getY());
	_listePoints.push_back(point->getZ());

	if (texture != NULL)
	{
		_listeTextures.push_back(texture->getX());
		_listeTextures.push_back(texture->getY());
	}

	_listeNormales.push_back(normale->getX());
	_listeNormales.push_back(normale->getY());
	_listeNormales.push_back(normale->getZ());

	

}

bool VBO::isInit()
{
	return _isInit;
}
void VBO::init()
{

	VBOMangaer::get()->alloueEtCharge(_id, _listePoints.data(), _listePoints.size() * sizeof(GLdouble), _listeTextures.data(), _listeTextures.size() * sizeof(GLdouble),_listeNormales.data(), _listeNormales.size() * sizeof(GLdouble));
	
	_isInit = true;


}
unsigned int VBO::affiche()
{
	if (!_isInit)
	{
		init();
	}
	_material->appliqueTexture();
	_material->appliqueMatiere();
	

	glBindBuffer(GL_ARRAY_BUFFER, _id);

	glVertexPointer(3, GL_DOUBLE, 0, BUFFER_OFFSET(0));
	if (_material->isTextured())
	{
		glTexCoordPointer(2, GL_DOUBLE, 0, BUFFER_OFFSET(_listePoints.size() * sizeof(GLdouble)));
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glColor3f(1.0,0.0,0.0);
	}
	glNormalPointer(GL_DOUBLE, 0, BUFFER_OFFSET(_listePoints.size() * sizeof(GLdouble) + _listeTextures.size() * sizeof(GLdouble)));
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glEnableClientState(GL_NORMAL_ARRAY);

	glDrawArrays(GL_TRIANGLES, 0, _listePoints.size()/3);

	return  _listePoints.size()/3;
}


void VBO::setMaterial(Material* material)
{
	_material = material;
}