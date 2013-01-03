#include "Shader.h"
#include "Outil.h"
#include <sstream>


Shader::Shader(std::string name)
{
	std::string* fuiteMemoire1 = new std::string();//TODO utiliser copy
	std::string* fuiteMemoire2 = new std::string();

	{
		std::ostringstream oss;
		oss << "shaders/" << name << ".vert";
		*fuiteMemoire1 =  Outil::get()->readFile(oss.str());
		_vertex = fuiteMemoire1->c_str();

	}

	{
		std::ostringstream oss;
		oss << "shaders/" << name << ".frag";
		*fuiteMemoire2 =  Outil::get()->readFile(oss.str());
		_pixel = fuiteMemoire2->c_str();
	}


	_idVertex = glCreateShader(GL_VERTEX_SHADER);
	_idPixel = glCreateShader(GL_FRAGMENT_SHADER);
	_idProgram = glCreateProgram();

}


Shader::~Shader()
{
	if (_idVertex != 0)
	{
		glDeleteShader(_idVertex);
	}
	if (_idPixel != 0)
	{
		glDeleteShader(_idPixel);
	}
	if (_idProgram != 0)
	{
		glDeleteProgram(_idProgram);
	}

}

GLboolean Shader::isValide()
{
	return glIsShader(_idVertex) && glIsShader(_idPixel);
}

void Shader::loadSource(const GLchar** source, bool isVertex)
{
	if (isVertex)
	{
		glShaderSource(_idVertex, 1, source, NULL);
		glCompileShader(_idVertex);
		GLint compile_status;
		glGetShaderiv(_idVertex, GL_COMPILE_STATUS, &compile_status);
		if(compile_status != GL_TRUE)
		{
			/* erreur a la compilation recuperation du log d'erreur */

			/* on recupere la taille du message d'erreur */
			GLsizei logsize;
			glGetShaderiv(_idVertex, GL_INFO_LOG_LENGTH, &logsize);

			/* on alloue un espace memoire dans lequel OpenGL ecrira le message */
			char *log = NULL;
			log = (char*) malloc(logsize + 1);
			/* initialisation du contenu */
			memset(log, '\0', logsize + 1);

			glGetShaderInfoLog(_idVertex, logsize, &logsize, log);
			std::cout << "impossible de compiler le shader" << log <<  std::endl;


			/* ne pas oublier de liberer la memoire et notre shader */
			free(log);
			glDeleteShader(_idVertex);
			getchar();
			exit(0);
		}
		glAttachShader(_idProgram, _idVertex);
		//std::cout << "Vertex shader loaded" << std::endl;
	}
	else
	{
		glShaderSource(_idPixel, 1, source, NULL);
		glCompileShader(_idPixel);
		GLint compile_status;
		glGetShaderiv(_idPixel, GL_COMPILE_STATUS, &compile_status);
		if(compile_status != GL_TRUE)
		{
			/* erreur a la compilation recuperation du log d'erreur */

			/* on recupere la taille du message d'erreur */
			GLsizei logsize;
			glGetShaderiv(_idPixel, GL_INFO_LOG_LENGTH, &logsize);

			/* on alloue un espace memoire dans lequel OpenGL ecrira le message */
			char *log = NULL;
			log = (char*) malloc(logsize + 1);
			/* initialisation du contenu */
			memset(log, '\0', logsize + 1);

			glGetShaderInfoLog(_idPixel, logsize, &logsize, log);
			std::cout << "impossible de compiler le shader" << log <<  std::endl;


			/* ne pas oublier de liberer la memoire et notre shader */
			free(log);
			glDeleteShader(_idPixel);
			getchar();
			exit(0);
		}

		glAttachShader(_idProgram, _idPixel);
		//	std::cout << "Pixel shader loaded" << std::endl;
	}


}

void Shader::link()
{
	glLinkProgram(_idProgram);
	//std::cout << "programme compilé " << std::endl;
	GLint compile_status;
	glGetProgramiv(_idProgram, GL_LINK_STATUS, &compile_status);
	if(compile_status != GL_TRUE)
	{
		/* erreur a la compilation recuperation du log d'erreur */

		/* on recupere la taille du message d'erreur */
		GLsizei logsize;
		glGetProgramiv(_idProgram, GL_INFO_LOG_LENGTH, &logsize);


		/* on alloue un espace memoire dans lequel OpenGL ecrira le message */
		char *log = NULL;
		log = (char*) malloc(logsize + 1);
		/* initialisation du contenu */
		memset(log, '\0', logsize + 1);

		glGetProgramInfoLog(_idProgram, logsize, &logsize, log);
		std::cout << "impossible de link les shader : " << log <<  std::endl;


		/* ne pas oublier de liberer la memoire et notre shader */
		free(log);
		getchar();
		exit(0);
	}


}

void Shader::active()
{
	//std::cout << "programme activé" << std::endl;
	glUseProgram(_idProgram);
}
void Shader::desactive()
{
	glUseProgram(0);
}

void Shader::init()
{
	if (_vertex != NULL)
	{
		loadSource(&_vertex, true);
	}

	if (_pixel != NULL)
	{
		loadSource(&_pixel, false);
	}
	link();





}

void Shader::setIdTexture(GLuint id)
{
	int my_sampler_uniform_location = glGetUniformLocation(_idProgram, "tex");
	glUniform1i(my_sampler_uniform_location,id);
}





///------------------------ShaderEtat--------------------//
ShaderEtat::ShaderEtat()
{
	_shaderCourant = NULL;
}

void ShaderEtat::active()
{
	if(_shaderCourant != NULL)
	{
		_shaderCourant->active();
	}
	else
	{
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
	}
}
void ShaderEtat::desactive()
{
	if(_shaderCourant != NULL)
	{
		_shaderCourant->desactive();
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
	}	
}

void ShaderEtat::setShader(Shader* shad)
{
	desactive();
	_shaderCourant = shad;
	active();
}

void ShaderEtat::setIdTexture(GLuint id)
{
	if(_shaderCourant != NULL)
	{
		_shaderCourant->setIdTexture(id);
	}
}