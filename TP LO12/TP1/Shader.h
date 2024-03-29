#ifndef _SHADER_H	
#define _SHADER_H

#include "const.h"
#include "Singleton.h"

class Shader
{
public:
	Shader(std::string name);
	virtual ~Shader();
	virtual void init();
	virtual GLboolean isValide();

	virtual void active();
	virtual void desactive();

	virtual void setIdTexture(GLuint id);


private:
	void loadSource(const GLchar** source, bool isVertex);
	void link();
protected:


	const GLchar* _vertex;
	const GLchar* _pixel;

private:
	GLuint _idVertex;
	GLuint _idPixel;
	GLuint _idProgram;
};

class ShaderEtat : public Singleton<ShaderEtat>
{
public:
	ShaderEtat();
	void active();
	void desactive();

	void activeTotal();
	void desactiveTotal();

	void activeNoLight();
	void desactiveNoLight();
	void toggleNoLight();

	void setShader(Shader* shad);
	void setIdTexture(GLuint id);
private:
	Shader* _shaderCourant;
	bool _isActived;
	bool _isNoLightActived;
};

#endif