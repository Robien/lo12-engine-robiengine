#include "Import.h"
#include "GestionnaireTexture.h"


Import::Import(void)
{
}


Import::~Import(void)
{
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
			mat = new Material(nomMaterial);

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
			sauterLigne(ifs);
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
