#include "Material.h"


Material::Material()
{
	_textured = false;
	_alpha = 1;
	_ambiante = new Vector3d<GLdouble>(0, 0, 0);
	_diffuse = new Vector3d<GLdouble>(0.8, 0.8, 0.8);
	_emission = new Vector3d<GLdouble>(0, 0, 0);
	_speculaire = new Vector3d<GLdouble>(0.8, 0.8, 0.8);
	_brillance = 0;
	_indiceTex =0;		
}

Material::Material(Material const& c)
{
	_textured = c._textured;
	_alpha = c._alpha;
	_ambiante = new Vector3d<GLdouble>(*(c._ambiante));
	_diffuse = new Vector3d<GLdouble>(*(c._diffuse));
	_emission = new Vector3d<GLdouble>(*(c._emission));
	_speculaire = new Vector3d<GLdouble>(*(c._speculaire));
	_brillance = c._brillance;
	_indiceTex = c._indiceTex;		
}

Material::~Material(void)
{
}

bool Material::isTextured()
{
	return _textured;
}
GLdouble Material::getAlpha()
{
	return _alpha;
}
Vector3d<GLdouble>*    Material::getAmbiante()
{
	return _ambiante;
}
Vector3d<GLdouble>*   Material::getDiffuse()
{
	return _diffuse;
}
Vector3d<GLdouble>*    Material::getEmission()
{
	return _emission;
}
Vector3d<GLdouble>*    Material::getSpeculaire()
{
	return _speculaire;
}
GLdouble Material::getBrillance()
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
void Material::getAlpha(GLdouble al)
{
	_alpha = al;
}
void Material::getAmbiante(Vector3d<GLdouble>* am)
{
	_ambiante = am;
}
void Material::getAmbiante(GLdouble r, GLdouble g, GLdouble b)
{
	_ambiante = new Vector3d<GLdouble>(r, g, b);
}
void Material::getDiffuse(Vector3d<GLdouble>* di)
{
	_diffuse = di;
}
void Material::getDiffuse(GLdouble r, GLdouble g, GLdouble b)
{
	_diffuse = new Vector3d<GLdouble>(r, g, b);
}
void Material::getEmission(Vector3d<GLdouble>* em)
{
	_emission = em;
}
void Material::getEmission(GLdouble r, GLdouble g, GLdouble b)
{
	_emission = new Vector3d<GLdouble>(r, g, b);
}
void Material::getSpeculaire(Vector3d<GLdouble>* sp)
{
	_speculaire = sp;
}
void Material::getSpeculaire(GLdouble r, GLdouble g, GLdouble b)
{
	_speculaire = new Vector3d<GLdouble>(r, g, b);
}
void Material::getBrillance(GLdouble br)
{
	_brillance = br;
}    
void Material::getIndiceTex(GLint num)
{
	_indiceTex = num;

}