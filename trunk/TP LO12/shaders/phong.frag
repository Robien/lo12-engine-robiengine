#define nbLumiere 2
varying vec3 normal, lightDir[nbLumiere], eyeVec;

const float cos_outer_cone_angle = 0.8; // 36 degrees
uniform sampler2D tex;

void main (void)
{
	vec4 final_color;// =
	//(gl_FrontLightModelProduct.sceneColor * texture2D(tex,gl_TexCoord[0].st));// +
	//(gl_LightSource[0].ambient * texture2D(tex,gl_TexCoord[0].st));
	for (int i = 0; i < nbLumiere; ++i)
	{
		vec3 L = normalize(lightDir[i]);
		vec3 D = normalize(gl_LightSource[i].spotDirection);

		float cos_cur_angle = dot(-L, D);

		float cos_inner_cone_angle = gl_LightSource[i].spotCosCutoff;

		float cos_inner_minus_outer_angle = 
			  cos_inner_cone_angle - cos_outer_cone_angle;
		
		float spot = 0.0;
		spot = clamp((cos_cur_angle - cos_outer_cone_angle) / 
			   cos_inner_minus_outer_angle, 0.0, 1.0);

		vec3 N = normalize(normal);

		float lambertTerm =  max(dot(N,L), 0.0);
	//if (lambertTerm < 0.0){lambertTerm = - lambertTerm;}
		if(lambertTerm > 0.0)
		{
			final_color += gl_LightSource[i].diffuse *
				texture2D(tex,gl_TexCoord[0].st) *
				lambertTerm * spot;

			vec3 E = normalize(eyeVec);
			vec3 R = reflect(-L, N);

			float specular = pow( max(dot(R, E), 0.0),
				gl_FrontMaterial.shininess );

			final_color += gl_LightSource[i].specular *
				gl_FrontMaterial.specular *
				specular * spot;
		}
	}
	gl_FragColor = final_color;
// gl_FragColor = texture2D(tex,gl_TexCoord[0].st) * final_color;
}