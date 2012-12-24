#include "ShaderPhong.h"


ShaderPhong::ShaderPhong() : Shader("rien")
{
	_vertex = "varying vec3 normal, eyeVec;\n"
"#define MAX_LIGHTS 8\n"
"#define NUM_LIGHTS 1\n"
"varying vec3 lightDir[MAX_LIGHTS];\n"
"void main()\n"
"{	\n"
  "gl_Position = ftransform();		\n"
  "normal = gl_NormalMatrix * gl_Normal;\n"
  "vec4 vVertex = gl_ModelViewMatrix * gl_Vertex;\n"
  "eyeVec = -vVertex.xyz;\n"
  "int i;\n"
  "for (i=0; i<NUM_LIGHTS; ++i)\n"
  "  lightDir[i] = \n"
  "    vec3(gl_LightSource[i].position.xyz - vVertex.xyz);\n"
"}\n";
_pixel = "varying vec3 normal, eyeVec;\n"
"#define MAX_LIGHTS 8\n"
"#define NUM_LIGHTS 1\n"
"varying vec3 lightDir[MAX_LIGHTS];\n"
"void main (void)\n"
"{"
  "vec4 final_color = \n"
   "    gl_FrontLightModelProduct.sceneColor;\n"
  "vec3 N = normalize(normal);\n"
  "int i;\n"
  "for (i=0; i<NUM_LIGHTS; ++i)\n"
  "{  \n"
  "  vec3 L = normalize(lightDir[i]);\n"
  "  float lambertTerm = dot(N,L);\n"
  "  if (lambertTerm > 0.0)\n"
  "  {\n"
  "    final_color += \n"
  "      gl_LightSource[i].diffuse * \n"
  "      gl_FrontMaterial.diffuse * \n"
  "      lambertTerm;	\n"
  "    vec3 E = normalize(eyeVec);\n"
  "    vec3 R = reflect(-L, N);\n"
  "    float specular = pow(max(dot(R, E), 0.0), \n"
  "                         gl_FrontMaterial.shininess);\n"
  "    final_color += \n"
  "      gl_LightSource[i].specular * \n"
  "      gl_FrontMaterial.specular * \n"
  "      specular;	\n"
  "  }\n"
  "}\n"
  "gl_FragColor = final_color;			\n"
"}\n";









_vertex = "varying vec3 normal, lightDir, eyeVec;\n"

"void main()\n"
"{	\n"
"	normal = gl_NormalMatrix * gl_Normal;\n"
"\n"
"	vec3 vVertex = vec3(gl_ModelViewMatrix * gl_Vertex);\n"
"\n"
"	lightDir = vec3(gl_LightSource[0].position.xyz - vVertex);\n"
"	eyeVec = -vVertex;\n"
"\n"
"	gl_Position = ftransform();		\n"
" gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"
"}\n";




_pixel = "varying vec3 normal, lightDir, eyeVec;\n"
"\n"
"const float cos_outer_cone_angle = 0.8; // 36 degrees\n"
"uniform sampler2D tex;\n"
"\n"
"void main (void)\n"
"{\n"
"	vec4 final_color;// =\n"
"	//(gl_FrontLightModelProduct.sceneColor * texture2D(tex,gl_TexCoord[0].st));// +\n"
"	//(gl_LightSource[0].ambient * texture2D(tex,gl_TexCoord[0].st));\n"
"\n"
"	vec3 L = normalize(lightDir);\n"
"	vec3 D = normalize(gl_LightSource[0].spotDirection);\n"
"\n"
"	float cos_cur_angle = dot(-L, D);\n"
"\n"
"	float cos_inner_cone_angle = gl_LightSource[0].spotCosCutoff;\n"
"\n"
"	float cos_inner_minus_outer_angle = \n"
"	      cos_inner_cone_angle - cos_outer_cone_angle;\n"
"	\n"
"	float spot = 0.0;\n"
"	spot = clamp((cos_cur_angle - cos_outer_cone_angle) / \n"
"	       cos_inner_minus_outer_angle, 0.0, 1.0);\n"
"\n"
"	vec3 N = normalize(normal);\n"
"\n"
"	float lambertTerm =  max(dot(N,L), 0.0);\n"
"//if (lambertTerm < 0.0){lambertTerm = - lambertTerm;}\n"
"	if(lambertTerm > 0.0)\n"
"	{\n"
"		final_color += gl_LightSource[0].diffuse *\n"
"			texture2D(tex,gl_TexCoord[0].st) *\n"
"			lambertTerm * spot;\n"
"\n"
"		vec3 E = normalize(eyeVec);\n"
"		vec3 R = reflect(-L, N);\n"
"\n"
"		float specular = pow( max(dot(R, E), 0.0),\n"
"			gl_FrontMaterial.shininess );\n"
"\n"
"		final_color += gl_LightSource[0].specular *\n"
"			gl_FrontMaterial.specular *\n"
"			specular * spot;\n"
"	}\n"
"	gl_FragColor = final_color;\n"
"// gl_FragColor = texture2D(tex,gl_TexCoord[0].st) * final_color;\n"
"}\n";











}


ShaderPhong::~ShaderPhong()
{
}
