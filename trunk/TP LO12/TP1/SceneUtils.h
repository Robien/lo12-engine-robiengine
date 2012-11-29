#ifndef SCENE_UTILS_H
#define SCENE_UTILS_H

#include "Scene.h"

class SceneUtils
{
public:
	SceneUtils();
	virtual ~SceneUtils();
public:

int read_scene_file(Scene* scene,char *filename);
void print_scene_data(Scene* scene);

private:
	int read_int(FILE *file,int *line,char *str,int num, int *value);
	int read_double(FILE *file,int *line,char *str,int num, double *value);
	int read_str(FILE *file,int *line,char *str,int num, char **pstr);
	int read_coord3d(FILE *file,int *line,char *str,Scene::MCOORD *coord);
	int read_coord4d(FILE *file,int *line,char *str,Scene::MCOORD *coord);
	int read_rgb3d(FILE *file,int *line,char *str,Scene::RGB *rgb);
	int read_transfo4x4d(FILE *file,int *line,char *str,Scene::MTRANSFO transfo);
	int read_allure2d(FILE *file, int *line, char *str, Scene::ALLURE_FAISCEAU *allure);

};

#endif
