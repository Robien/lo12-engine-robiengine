#define nbLumiere 4
varying vec3 normal, lightDir[nbLumiere], eyeVec;

void main()
{	
	normal = gl_NormalMatrix * gl_Normal;

	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);

	for (int i = 0; i < nbLumiere; ++i)
	{
		if (gl_LightSource[i].spotCosCutoff != 0)
		{
			lightDir[i] = vec3(gl_LightSource[i].position.xyz - vVertex);
		}
		else
		{
			lightDir[i] = gl_LightSource[i].position.xyz;
		}
	}
	eyeVec = -vVertex;

	gl_Position = ftransform();		
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	
}

