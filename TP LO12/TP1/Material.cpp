#include "Material.h"
#include "Outil.h"


Material::Material()
{
	_textured = false;
	_alpha = 1;
	_ambiante = new Vector3d<GLfloat>(1, 1, 1);
	_diffuse = new Vector3d<GLfloat>(0.8, 0.8, 0.8);
	_emission = new Vector3d<GLfloat>(0, 0, 0);
	_speculaire = new Vector3d<GLfloat>(0.8, 0.8, 0.8);
	_brillance = 0;
	_indiceTex =0;		
}

Material::Material(Material const& c)
{
	_textured = c._textured;
	_alpha = c._alpha;
	_ambiante = new Vector3d<GLfloat>(*(c._ambiante));
	_diffuse = new Vector3d<GLfloat>(*(c._diffuse));
	_emission = new Vector3d<GLfloat>(*(c._emission));
	_speculaire = new Vector3d<GLfloat>(*(c._speculaire));
	_brillance = c._brillance;
	_indiceTex = c._indiceTex;		
}

Material::~Material(void)
{
	delete _ambiante;
	delete _diffuse;
	delete _emission;
	delete _speculaire;

}

bool Material::isTextured()
{
	return _textured;
}
GLfloat Material::getAlpha()
{
	return _alpha;
}
Vector3d<GLfloat>*    Material::getAmbiante()
{
	return _ambiante;
}
Vector3d<GLfloat>*   Material::getDiffuse()
{
	return _diffuse;
}
Vector3d<GLfloat>*    Material::getEmission()
{
	return _emission;
}
Vector3d<GLfloat>*    Material::getSpeculaire()
{
	return _speculaire;
}
GLfloat Material::getBrillance()
{
	return _brillance;
}      
GLint Material::getIndiceTex()
{
	return _indiceTex;
}

void Material::setTextured(bool ist)
{
	_textured = ist;
}
void Material::getAlpha(GLfloat al)
{
	_alpha = al;
}
void Material::getAmbiante(Vector3d<GLfloat>* am)
{
	_ambiante = am;
}
void Material::getAmbiante(GLfloat r, GLfloat g, GLfloat b)
{
	_ambiante = new Vector3d<GLfloat>(r, g, b);
}
void Material::getDiffuse(Vector3d<GLfloat>* di)
{
	_diffuse = di;
}
void Material::getDiffuse(GLfloat r, GLfloat g, GLfloat b)
{
	_diffuse = new Vector3d<GLfloat>(r, g, b);
}
void Material::getEmission(Vector3d<GLfloat>* em)
{
	_emission = em;
}
void Material::getEmission(GLfloat r, GLfloat g, GLfloat b)
{
	_emission = new Vector3d<GLfloat>(r, g, b);
}
void Material::getSpeculaire(Vector3d<GLfloat>* sp)
{
	_speculaire = sp;
}
void Material::getSpeculaire(GLfloat r, GLfloat g, GLfloat b)
{
	_speculaire = new Vector3d<GLfloat>(r, g, b);
}
void Material::getBrillance(GLfloat br)
{
	_brillance = br;
}    
void Material::getIndiceTex(GLint num)
{
	_indiceTex = num;

}

void Material::appliqueTexture()
{
	//Normalement pas besoin de tester si il y a une texture de set
	// dans face, on test déjà si y'a des coordonnées de textures appliqué à la face.
	glBindTexture(GL_TEXTURE_2D, getIndiceTex());
}

void Material::appliqueMatiere()
{
	//TODO : free ...
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _ambiante->getCStyle());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,_diffuse->getCStyle());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _speculaire->getCStyle());
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _brillance);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,_emission->getCStyle());

}