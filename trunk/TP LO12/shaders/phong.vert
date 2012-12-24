#define nbLumiere 2
varying vec3 normal, lightDir[nbLumiere], eyeVec;

void main()
{	
	normal = gl_NormalMatrix * gl_Normal;

	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);

	for (int i = 0; i < nbLumiere; ++i)
	{
		lightDir[i] = vec3(gl_LightSource[i].position.xyz - vVertex);
	}
	eyeVec = -vVertex;

	gl_Position = ftransform();		
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	
}

