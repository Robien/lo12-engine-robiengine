#include "Material.h"
#include "Outil.h"


Material::Material()
{
	_textured = false;
	_nom = "";
	_alpha = 1;
	_ambiante = new Vector3d<GLfloat>(1, 1, 1);
	_diffuse = new Vector3d<GLfloat>(0.8, 0.8, 0.8);
	_emission = new Vector3d<GLfloat>(0, 0, 0);
	_speculaire = new Vector3d<GLfloat>(0.8, 0.8, 0.8);
	_brillance = 0;
	_indiceTex =0;		
}

Material::Material(std::string nom)
{
	_textured = false;
	_nom = nom;
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
	_nom = c._nom;
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
std::string Material::getNom()
{
	return _nom;
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
void Material::setNom(std::string n)
{
	_nom = n;
}
void Material::setAlpha(GLfloat al)
{
	_alpha = al;
}
void Material::setAmbiante(Vector3d<GLfloat>* am)
{
	_ambiante = am;
}
void Material::setAmbiante(GLfloat r, GLfloat g, GLfloat b)
{
	_ambiante = new Vector3d<GLfloat>(r, g, b);
}
void Material::setDiffuse(Vector3d<GLfloat>* di)
{
	_diffuse = di;
}
void Material::setDiffuse(GLfloat r, GLfloat g, GLfloat b)
{
	_diffuse = new Vector3d<GLfloat>(r, g, b);
}
void Material::setEmission(Vector3d<GLfloat>* em)
{
	_emission = em;
}
void Material::setEmission(GLfloat r, GLfloat g, GLfloat b)
{
	_emission = new Vector3d<GLfloat>(r, g, b);
}
void Material::setSpeculaire(Vector3d<GLfloat>* sp)
{
	_speculaire = sp;
}
void Material::setSpeculaire(GLfloat r, GLfloat g, GLfloat b)
{
	_speculaire = new Vector3d<GLfloat>(r, g, b);
}
void Material::setBrillance(GLfloat br)
{
	_brillance = br;
}    
void Material::setIndiceTex(GLint num)
{
	_indiceTex = num;

}

void Material::appliqueTexture()
{
	//Normalement pas besoin de tester si il y a une texture de set
	// dans face, on test d�j� si y'a des coordonn�es de textures appliqu� � la face.
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