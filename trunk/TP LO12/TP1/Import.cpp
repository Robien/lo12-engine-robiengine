#include "Import.h"
#include "GestionnaireTexture.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include <sstream>

Import::Import(void)
{
}


Import::~Import(void)
{
}

std::vector<Objet* >* Import::importer(std::string namefile)
{
	std::vector<Objet* >* listObjet = new std::vector<Objet* >();
	std::vector<Material* >* listmat = NULL;
	std::vector<Vector2d<GLdouble>* > listPointUV;
	std::vector<Vector3d<GLdouble>* > listSommet;
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
			currentObjet = new Objet(supprimerEspaceAvant(nomObjet));
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
						int indiceText = atoi(listCoord.at(0).c_str())-1;
						facette->addPoint(listSommet.at(indice),listPointUV.at(indiceText));
					}
				}

			}
			//calcule des normal
			facette->calculeNormales();
			//Ajout de la face
			currentObjet->addFace(facette);

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


