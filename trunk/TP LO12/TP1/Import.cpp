#include "Import.h"
#include "GestionnaireTexture.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include <sstream>
#include "AxeAnimation.h"

Import::Import()
{
}


Import::~Import()
{
}

int Import::sizeOfFile(std::string namefile)
{	
	//ouverture du fichier
	int fileSize;
	std::ifstream ifs(namefile.c_str(), std::ios::in | std::ios::ate);
	if (!ifs)
	{
		std::cerr << "Erreur dans l'ouverture du fichier : " << namefile << std::endl;
		return 0;
	}
	fileSize = ifs.tellg();
	//positionne au debut du fichier
	ifs.seekg(0, std::ios::beg);
	//fermeture du fichier
	ifs.close();
	return fileSize;
}

void Import::setAvancement(int avan)
{
	int progression  = avan - avancement;
	avancement = avan;
	//appeler le callback de chenillard en envoyant progression
}

std::vector<AbstractObjet* >* Import::importer(std::string namefile)
{
	std::vector<AbstractObjet* >* listObjet = new std::vector<AbstractObjet* >();
	std::vector<Material* >* listmat = NULL;
	std::vector<Vector2d<GLdouble>* > listPointUV;
	std::vector<Vector3d<GLdouble>* > listSommet;
	bool isAxeObjet = false;
	std::vector<AxeAnimation* > listAxes;
	std::ifstream ifs((namefile).c_str(), std::ios::in);

	if (!ifs)
	{
		std::cerr << "Erreur, impossible de lire le fichier : " << namefile << std::endl;
		return listObjet;
	}
	//positionne au debut du fichier
	ifs.seekg(0, std::ios::beg);

	std::string ele_id;
	Material* currentMat = NULL;
	Objet* currentObjet = NULL;

	GLdouble x, y, z;

	while(sauterLigneCommentaire(ifs) && (ifs >> ele_id))
	{
		setAvancement(ifs.tellg());
		if ("mtllib" == ele_id) //nom du fichier de texture .MTL
		{
			std::string pathFileName;
			getline(ifs, pathFileName);
			pathFileName = supprimerEspaceAvant(pathFileName);
			if(!pathFileName.empty())
			{
				listmat = this->importerMaterial(getPath(namefile)+pathFileName); //importer les materials
			}
		}
		else if ("usemtl" == ele_id) //material a appliquer au face suivante
		{
			//TODO Verifier que ca fonctionne si material vide
			std::string strMtlName;
			getline(ifs, strMtlName);
			strMtlName = supprimerEspaceAvant(strMtlName);
			unsigned int i = 0;
			while(i < listmat->size() && listmat->at(i)->getNom() != strMtlName) //recherche de la material correspondante
			{
				++i;
			}
			if(i < listmat->size()) //si elle existe elle sera utilisé pour les prochaines faces
			{
				currentMat = listmat->at(i);
			}
			else //si aucune texture, utiliser une par défaut
			{
				currentMat = new Material("Texture_defaut");
			}
		}
		else if ("o" == ele_id) //coordonnée d'un sommet
		{
			if (currentObjet != NULL)
			{
				listObjet->push_back(currentObjet);
			}

			std::string nomObjet;
			getline(ifs, nomObjet);

			//nom de l'objet
			nomObjet = supprimerEspaceAvant(nomObjet);

			//Si c'est un axe
			isAxeObjet = isAxe(nomObjet);
			if(isAxeObjet)
			{
				std::vector<std::string> listnom = extraireNomAxe(nomObjet);
				if(listnom.size()>1)
				{	
					listAxes.push_back(new AxeAnimation(listnom.at(1),listnom.at(0)));
				}
				else
				{
					std::cerr << "Problème de nom d'Axe : "<< nomObjet <<", il doit etre de la forme @nomObjetLié@_@nomAxe@"<< std::endl;
					listAxes.push_back(new AxeAnimation("erreur","erreur"));
				}
			}
			else //sinon c'est un nouvelle objet
			{
				currentObjet = new Objet(nomObjet);
			}
		}
		else if ("v" == ele_id) //coordonnée d'un sommet
		{
			ifs >> x >> y >> z;
			listSommet.push_back(new Vector3d<GLdouble >(x,y,z));
		}
		else if ("vt" == ele_id) //coordonnée d'un point d'une texture
		{
			ifs >> x >> y;
			listPointUV.push_back(new Vector2d<GLdouble >(x,y));
		}
		else if ("f" == ele_id) // information sur une face pour un matériau
		{
			if(isAxeObjet)
			{
				std::string coordonnees;
				getline(ifs, coordonnees);

				std::vector<std::string> listIndices = splitEspace(coordonnees);
				for(unsigned int nbcoord=0; nbcoord < listIndices.size() || nbcoord < 2; ++nbcoord)
				{
					std::vector<std::string> listCoord = splitEspace( remplacerSlash( doubleSlash( listIndices.at(nbcoord) ) ) );
					if(!listCoord.empty())
					{
						if(nbcoord == 0) //il y a seulement des sommet
						{
							int indice = atoi(listCoord.at(0).c_str()) -1;
							listAxes.at(listAxes.size()-1)->setPointA(listSommet.at(indice));
						}
						else
						{
							int indice = atoi(listCoord.at(0).c_str()) -1;
							listAxes.at(listAxes.size()-1)->setPointB(listSommet.at(indice));
						}

					}

				}
			}
			else
			{
				Face* facette = new Face(currentMat);
				std::string coordonnees;
				getline(ifs, coordonnees);

				std::vector<std::string> listIndices = splitEspace(coordonnees);
				for(unsigned int nbcoord=0; nbcoord < listIndices.size(); ++nbcoord)
				{
					std::vector<std::string> listCoord = splitEspace( remplacerSlash( doubleSlash( listIndices.at(nbcoord) ) ) );
					if(!listCoord.empty())
					{
						if(listCoord.size()<2 || listCoord.at(1) == "0") //il y a seulement des sommet
						{
							int indice = atoi(listCoord.at(0).c_str()) -1;
							facette->addPoint(listSommet.at(indice));
						}
						else 
						{
							int indice = atoi(listCoord.at(0).c_str())-1;
							int indiceText = atoi(listCoord.at(1).c_str())-1;
							facette->addPoint(listSommet.at(indice),listPointUV.at(indiceText));
						}
					}

				}
				//calcule des normal
				facette->calculeNormales();

				//calcul du centre de gravité d'un point
				if(facette->getListePoints().size() >= 3)
				{
					currentObjet->addPointCollsion(Outil::get()->centreGravite(facette->getListePoints().at(0),facette->getListePoints().at(1),facette->getListePoints().at(2)));
				}

				//Ajout de la face
				currentObjet->addFace(facette);
			}
		}
		else
		{	sauterLigne(ifs);	}
	}

	if (currentObjet != NULL)
	{
		listObjet->push_back(currentObjet);
	}

	//fermeture du fichier
	ifs.close();

	for(unsigned int i = 0; i < listObjet->size(); ++i)
	{
		for(unsigned int j = 0; j < listAxes.size(); ++j)
		{
			if(listObjet->at(i)->getNom()==listAxes.at(j)->getNomObjetLie())
			{
				listObjet->at(i)->addAxe(listAxes.at(j));
			}
		}
	}

	return listObjet;

}




std::vector<Material* >* Import::importerMaterial(std::string namefile)
{
	std::vector<Material* >* listMat = new std::vector<Material* >();

	std::ifstream ifs((namefile).c_str(), std::ios::in);

	if (!ifs)
	{
		std::cerr << "Erreur, impossible de lire le fichier : " << namefile << std::endl;
		return listMat;
	}
	//positionne au debut du fichier
	ifs.seekg(0, std::ios::beg);

	std::string ele_id;
	Material* mat = NULL;
	GLfloat x, y, z;

	while(sauterLigneCommentaire(ifs) && (ifs >> ele_id))
	{
		if ("newmtl" == ele_id) //nom d'un matériau
		{		
			if (mat != NULL)
			{
				listMat->push_back(mat);
			}

			std::string nomMaterial;
			getline(ifs, nomMaterial);
			mat = new Material(supprimerEspaceAvant(nomMaterial));

		} 
		else if ("Ns" == ele_id) //specular Coefficient
		{
			ifs >> x;
			mat->setBrillance(x);
		}
		else if ("Ka" == ele_id) //ambiant
		{
			ifs >> x >> y >> z;
			mat->setAmbiante(x,y,z);
		} 
		else if ("Kd" == ele_id) //diffuse
		{
			ifs >> x >> y >> z;
			mat->setDiffuse(x,y,z);
		}
		else if ("Ks" == ele_id) //specular
		{
			ifs >> x >> y >> z;
			mat->setSpeculaire(x,y,z);
		}
		else if ("d" == ele_id || "Tr" == ele_id) //transparent
		{
			ifs >> x;
			mat->setAlpha(x);
		}
		else if ("map_Kd" == ele_id) //texture
		{
			std::string strMtlName;
			ifs >> strMtlName;
			mat->setIndiceTex(GestionnaireTexture::get()->addTexture(getPath(namefile) + strMtlName));
			mat->setTextured(true);
		} 
		else
		{	sauterLigne(ifs);	}
	}

	if (mat != NULL)
	{
		listMat->push_back(mat);
	}

	//fermeture du fichier
	ifs.close();

	return listMat;

}

bool Import::isAxe(std::string nomObjet)
{
	bool isObjetAxe = false;
	size_t found;
	found=nomObjet.find("@");
	if (found!=std::string::npos)
	{
		found=nomObjet.find("@",found+1);
		if (found!=std::string::npos)
		{
			return isObjetAxe = true;
		}
	}

	return isObjetAxe;
}


//      sauter une ligne
void Import::sauterLigne(std::istream& is)
{
	char carac;
	is >> std::noskipws;
	while ((is >> carac) && ('\n' != carac));
}

//      Sauter les ligne de commentaire
bool Import::sauterLigneCommentaire(std::istream& is)
{
	char carac;
	while (is >> std::skipws >> carac)
	{
		is.putback(carac);
		if ('#' == carac)
		{sauterLigne(is);}
		else
		{return true;}
	}
	return false;
}

std::string Import::getPath(std::string filename)
{
	std::string s1="",s2="";
	for(unsigned int i=0;i<filename.size();i++)
	{
		if(filename[i]=='/'||filename[i]=='\\')
		{
			s1+=s2+"/";
			s2="";
		}
		else
			s2+=filename[i];
	}
	return s1;
}

std::string Import::doubleSlash(std::string s)
{
	//Remplace "//" par "/0/".
	std::string s1="";
	for(unsigned int i=0;i<s.size();i++)
	{
		if(i<s.size()-1&&s[i]=='/'&&s[i+1]=='/')
		{
			s1+="/0/";
			i++;
		}
		else
		{ s1+=s[i];}
	}
	return s1;
}

std::string Import::remplacerSlash(std::string s)
{
	//Remplace les '/' par des espaces.
	std::string ret="";
	for(unsigned int i=0;i<s.size();i++)
	{
		if(s[i]=='/')
		{   ret+=' ';}
		else
		{   ret+=s[i];}
	}
	return ret;
}

std::vector<std::string> Import::splitEspace(std::string s)
{
	//Eclate une chaîne au niveau de ses espaces.
	std::vector<std::string> ret;
	std::string s1="";
	for(unsigned int i=0;i<s.size();i++)
	{
		if(s[i]==' '||i==s.size()-1)
		{
			if(i==s.size()-1)
			{ s1+=s[i]; }
			if(s1!="")
			{ 
				ret.push_back(s1);
				s1="";
			}
		}
		else
		{  s1+=s[i]; }
	}
	return ret;
}

std::string Import::supprimerEspaceAvant(std::string s)
{
	//supprimer les espaces avant le nom de fichier.
	std::string s1="";
	for(unsigned int i=0;i<s.size();i++)
	{
		if(s[i]!=' ' || s1.size()>0)
		{
			s1+=s[i]; 
		}
	}
	return s1;
}

//fonction permettant de recuperer le nom de l'axe et de l'objet qui est lier
std::vector<std::string> Import::extraireNomAxe(std::string s)
{

	//Eclate une chaîne au niveau de ses espaces.
	std::vector<std::string> ret;
	std::string s1="";
	for(unsigned int i=0;i<s.size();i++)
	{
		if(s[i]=='@'||i==s.size()-1)
		{
			if(i==s.size()-1 && s[i]!='@')
			{ s1+=s[i]; }
			if(s1=="_")
			{ 
				s1="";
			}
			if(s1!="")
			{ 
				ret.push_back(s1);
				s1="";
			}
		}
		else
		{  s1+=s[i]; }
	}
	return ret;
}