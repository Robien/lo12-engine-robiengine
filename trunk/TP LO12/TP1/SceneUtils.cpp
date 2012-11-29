/*
 
        Universite de Technologe de Compiegne
        
        UV: LO12
        
        FICHIER: SceneUtils.c
 
        COMMENTAIRE:
                Lecture du fichier Scene (Haut Niveau)
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scene.h"
#include "SceneUtils.h"
#include "DatUtils.h"

#ifdef _MSC_VER
#define SNPRINTF _snprintf
#else
#define SNPRINTF snprintf
#endif

SceneUtils::SceneUtils()
{
}
SceneUtils::~SceneUtils()
{
}

/**************************************************************************************/
/* lecture du contenu de la scene dans un fichier et stockage dans la structure scene */
/**************************************************************************************/

/*Lit #num int de la ligne courante et le stocke dans le tableau d'int value*/
int SceneUtils::read_int(FILE *file,int *line,char *str,int num, int *value)
{
        int i;
        ValueList *vlf,*vl;
        vlf=vl=readNextLine(file,line);
        if(vl==NULL) {
                printf("ERREUR ligne %d lecture de %s, impossible de lire le fichier\n",*line,str);
                return -1;
        }
        for(i=0;i<num && vl;i++,vl=vl->next) {
                if(vl->type!=INT_VALUE) {
                        printf("ERREUR ligne %d lecture de %s, elements %d, type incompatible\n",*line,str,i);
                        printf("J'attends un INT et je lis: ");
                        printValue(vl);
                        printf("\n");
                        freeValueList(vlf);
                        return -1;
                }
                value[i]=vl->intValue;
        }
        if(i!=num) {
                printf("ERREUR ligne %d lecture de %s, trop peu d'elements\n",*line,str);
                printf("J'attends %d INT et je lis: ",num);
                printValueList(vlf);
                freeValueList(vlf);
                return -1;
        }
        if(vl!=NULL) {
                printf("ATTENTION ligne %d lecture de %s, trop d'elements\n",*line,str);
                printf("J'attends %d INT et je lis: ",num);
                printValueList(vlf);
        }
        freeValueList(vlf);
        return 0;
}


/*Lit #num double de la ligne courante et le stocke dans le tableau de double value*/
int SceneUtils::read_double(FILE *file,int *line,char *str,int num, double *value)
{
        int i;
        ValueList *vlf,*vl;
        vlf=vl=readNextLine(file,line);
        if(vl==NULL) {
                printf("ERREUR ligne %d lecture de %s, impossible de lire le fichier\n",*line,str);
                return -1;
        }
        for(i=0;i<num && vl;i++,vl=vl->next) {
                if(vl->type!=DOUBLE_VALUE) {
                        printf("ERREUR ligne %d lecture de %s, elements %d, type incompatible\n",*line,str,i);
                        printf("J'attends un DOUBLE et je lis: ");
                        printValue(vl);
                        printf("\n");
                        freeValueList(vlf);
                        return -1;
                }
                value[i]=vl->doubleValue;
        }
        if(i!=num) {
                printf("ERREUR ligne %d lecture de %s, trop peu d'elements\n",*line,str);
                printf("J'attends %d DOUBLE et je lis: ",num);
                printValueList(vlf);
                freeValueList(vlf);
                return -1;
        }
        if(vl!=NULL) {
                printf("ATTENTION ligne %d lecture de %s, trop d'elements\n",*line,str);
                printf("J'attends %d DOUBLE et je lis: ",num);
                printValueList(vlf);
        }
        freeValueList(vlf);
        return 0;
}

/*Lit #num str de la ligne courante et le stocke dans le tableau de char * pstr */
int SceneUtils::read_str(FILE *file,int *line,char *str,int num, char **pstr)
{
        int i;
        ValueList *vlf,*vl;
        vlf=vl=readNextLine(file,line);
        if(vl==NULL) {
                printf("ERREUR ligne %d lecture de %s, impossible de lire le fichier\n",*line,str);
                return -1;
        }
        for(i=0;i<num && vl;i++,vl=vl->next) {
                if(vl->type!=STR_VALUE) {
                        printf("ERREUR ligne %d lecture de %s, elements %d, type incompatible\n",*line,str,i);
                        printf("J'attends un STR et je lis: ");
                        printValue(vl);
                        printf("\n");
                        freeValueList(vlf);
                        return -1;
                }
                pstr[i]=(char*)malloc(strlen(vl->strValue)+1);
                strcpy(pstr[i],vl->strValue);
        }
        if(i!=num) {
                printf("ERREUR ligne %d lecture de %s, trop peu d'elements\n",*line,str);
                printf("J'attends %d STR et je lis: ",num);
                printValueList(vlf);
                freeValueList(vlf);
                return -1;
        }
        if(vl!=NULL) {
                printf("ATTENTION ligne %d lecture de %s, trop d'elements\n",*line,str);
                printf("J'attends %d STR et je lis: ",num);
                printValueList(vlf);
        }
        freeValueList(vlf);
        return 0;
}


/*Lit un MTEXCOORD (en 2 double) dans la ligne courante et le stocke dans coord (à faire pour le TP texture)
int read_texcoord2d(FILE *file,int *line,char *str,MTEXCOORD *coord)
{
}
*/

/*Lit un Scene::MCOORD (en 3 double) dans la ligne courante et le stocke dans coord*/
int SceneUtils::read_coord3d(FILE *file,int *line,char *str,Scene::MCOORD *coord)
{
        double buff[3];
        if(read_double(file,line,str,3,buff))
                return -1;
        coord->x=buff[0];
        coord->y=buff[1];
        coord->z=buff[2];
        coord->w=1;
        return 0;
}

/*Lit un Scene::MCOORD (en 4 double) dans la ligne courante et le stocke dans coord*/
int SceneUtils::read_coord4d(FILE *file,int *line,char *str,Scene::MCOORD *coord)
{
        double buff[4];
        if(read_double(file,line,str,4,buff))
                return -1;
        coord->x=buff[0];
        coord->y=buff[1];
        coord->z=buff[2];
        coord->w=buff[3];
        return 0;
}

/*Lit un RGB (en 3 double) dans la ligne courante et le stocke dans rgb  */
int SceneUtils::read_rgb3d(FILE *file,int *line,char *str,Scene::RGB *rgb)
{
        double buff[3];
        if(read_double(file,line,str,3,buff))
                return -1;
        rgb->r=buff[0];
        rgb->g=buff[1];
        rgb->b=buff[2];
        return 0;
}

/*Lit un MTRANSFO (en 4*4 double) à partir de la ligne courante et le stocke dans transfo  */
int SceneUtils::read_transfo4x4d(FILE *file,int *line,char *str,Scene::MTRANSFO transfo)
{
        double buff[4];
        if(read_double(file,line,str,4,buff))
                return -1;
        transfo[0]=buff[0];
        transfo[4]=buff[1];
        transfo[8]=buff[2];
        transfo[12]=buff[3];
        if(read_double(file,line,str,4,buff))
                return -1;
        transfo[1]=buff[0];
        transfo[5]=buff[1];
        transfo[9]=buff[2];
        transfo[13]=buff[3];
        if(read_double(file,line,str,4,buff))
                return -1;
        transfo[2]=buff[0];
        transfo[6]=buff[1];
        transfo[10]=buff[2];
        transfo[14]=buff[3];
        if(read_double(file,line,str,4,buff))
                return -1;
        transfo[3]=buff[0];
        transfo[7]=buff[1];
        transfo[11]=buff[2];
        transfo[15]=buff[3];
        return 0;
}


/*Lit un ALLURE_FAISCEAU  (en 2 double) dans la ligne courante et le stocke dans allure  */
int SceneUtils::read_allure2d(FILE *file, int *line, char *str, Scene::ALLURE_FAISCEAU *allure)
{
        double buff[2];
        if(read_double(file,line,str,2,buff))
                return -1;
        allure->k=buff[0];
        allure->theta=buff[1];
        return 0;
}

int SceneUtils::read_scene_file(Scene *scene,char *filename)
{
        FILE *file;                    	/* identificateur du fichier */
        int   i, line=0;
        char signe[256];


        /*-----------------------------------------------------------------------*/

        file = fopen(filename, "r");

        if (!file) {
                fprintf(stderr, "\007\nProbleme a l'ouverture du fichier %s\n", filename);
                return(-1);
        }

        if(read_int(file,&line,"Nombre de points",1,&(scene->nbpt) ))
                return -1;
        if(read_int(file,&line,"Nombre de matieres",1,&(scene->nbmat)))
                return -1;
        if(read_int(file,&line,"Nombre de faces",1,&(scene->nbface) ))
                return -1;
        if(read_int(file,&line,"Nombre d'objets",1,&(scene->nbobj)))
                return -1;
        if(read_int(file,&line,"Nombre de sources",1,&(scene->nbsource)) )
                return -1;

        scene->tabpt = (Scene::MCOORD *)malloc(scene->nbpt * sizeof(Scene::MCOORD));

        for (i = 0 ; i < scene->nbpt ; i++)    /* boucle sur les points */
        {
                SNPRINTF(signe,255,"Point %d",i);
                if(read_coord3d(file,&line,signe,&(scene->tabpt[i])))
                        return -1;
        }

        scene->tabmat = (Scene::MATIERE *)malloc( scene->nbmat * sizeof(Scene::MATIERE));

        for (i = 0 ; i < scene->nbmat ; i++)    /* boucle sur les Scene::MATIEREs */
        {
                SNPRINTF(signe,255,"Matiere %d (alpha)",i);
                if(read_double(file,&line,signe,1,&(scene->tabmat[i].alpha)) )
                        return -1;
                SNPRINTF(signe,255,"Matiere %d (ambiante)",i);
                if(read_rgb3d(file,&line,signe,&(scene->tabmat[i].ambiante)))
                        return -1;
                SNPRINTF(signe,255,"Matiere %d (diffuse)",i);
                if(read_rgb3d(file,&line,signe,&(scene->tabmat[i].diffuse)))
                        return -1;
                SNPRINTF(signe,255,"Matiere %d (emission)",i);
                if(read_rgb3d(file,&line,signe,&(scene->tabmat[i].emission)))
                        return -1;
                SNPRINTF(signe,255,"Matiere %d (speculaire)",i);
                if(read_rgb3d(file,&line,signe,&(scene->tabmat[i].speculaire)))
                        return -1;
                SNPRINTF(signe,255,"Matiere %d (brillance)",i);
                if(read_double(file,&line,signe,1,&(scene->tabmat[i].brillance)))
                        return -1;
        }



        scene->tabface = (Scene::FACE *)malloc(scene->nbface * sizeof(Scene::FACE));

        for (i = 0 ; i < scene->nbface ; i++)    /* boucle sur les Scene::FACEs */
        {
                SNPRINTF(signe,255,"Face %d (nombre de points)",i);
                if(read_int(file,&line,signe,1,&(scene->tabface[i].nbpt)))
                        return -1;
                /* on reserve de la place pour scene->tabface[i].nbpt  Scene::INDICE_PT */
                scene->tabface[i].tabpt =
                        (Scene::INDICE_PT *)malloc(scene->tabface[i].nbpt * sizeof(Scene::INDICE_PT));
                SNPRINTF(signe,255,"Face %d (liste de points)",i);
                if(read_int(file,&line,signe,scene->tabface[i].nbpt,scene->tabface[i].tabpt) )
                        return -1;
                SNPRINTF(signe,255,"Face %d (indice Matiere)",i);
                if(read_int(file,&line,signe,1,&(scene->tabface[i].imat)) )
                        return -1;
        }

        /* ------------------------------------------------------------------------- */

        /* on reserve de la place pour un tableau de nbobj OBJET */
        scene->tabobj = (Scene::OBJET *)malloc(scene->nbobj * sizeof(Scene::OBJET));
        for (i = 0 ; i < scene->nbobj ; i++)    /* boucle sur les nbobj objets */
        {
                SNPRINTF(signe,255,"Objet %d (nombre de Scene::FACEs)",i);
                if(read_int(file,&line,signe,1,&(scene->tabobj[i].nbface)) )
                        return -1;
                /* on reserve de la place pour un tableau
                   scene->tabobj[i].nbface de Scene::INDICE_FACE */
                scene->tabobj[i].tabface =
                        (Scene::INDICE_FACE *)malloc(scene->tabobj[i].nbface * sizeof(Scene::INDICE_FACE));
                SNPRINTF(signe,255,"Objet %d (liste de Scene::FACEs)",i);
                if(read_int(file,&line,signe,scene->tabobj[i].nbface,scene->tabobj[i].tabface) )
                        return -1;
                SNPRINTF(signe,255,"Objet %d (matrice de transformation)",i);
                if(read_transfo4x4d(file,&line,signe,scene->tabobj[i].transfo) )
                        return -1;

        }

        /*-----------------------------------------------------------------------*/

        /* on reserve de la place pour un tableau de nbsource Scene::SOURCE */
        scene->tabsource = (Scene::SOURCE *)malloc(scene->nbsource * sizeof(Scene::SOURCE));

        for (i = 0 ; i < scene->nbsource ; i++)    /* boucle sur nbsource Scene::SOURCEs */
        {

                SNPRINTF(signe,255,"Source %d (ambiante)",i);
                if(read_rgb3d(file,&line,signe,&(scene->tabsource[i].ambiante)))
                        return -1;
                SNPRINTF(signe,255,"Source %d (couleur)",i);
                if(read_rgb3d(file,&line,signe,&(scene->tabsource[i].couleur)))
                        return -1;
                SNPRINTF(signe,255,"Source %d (position)",i);
                if(read_coord4d(file,&line,signe,&(scene->tabsource[i].position)))
                        return -1;
                SNPRINTF(signe,255,"Source %d (allure faisceau)",i);
                if(read_allure2d(file,&line,signe,&(scene->tabsource[i].allure_faisceau)))
                        return -1;
                SNPRINTF(signe,255,"Source %d (direction)",i);
                if(read_coord3d(file,&line,signe,&(scene->tabsource[i].direction)))
                        return -1;
        }

        /* ------------------------------------------------------------------------- */

        if (fclose(file) == EOF)       /* si il y a un probleme avec
                                                                                                                                                                            la fermeture du fichier */
        {
                fprintf(stderr, "\007impossible de fermer le fichier %s\n", filename);
                return(-1);                   /* ca s'est mal passe */
        } else
                return(0); /* tout s'est bien passe */

}



/*-----------------------------------------------------------------------*/
/* affichage des donnees */
/*-----------------------------------------------------------------------*/

void SceneUtils::print_scene_data(Scene *scene)
{
        int i,j;

        printf("---------------------------------------------\n");
        printf("scene lue :\n");
        printf("nombre de points :\t%d\n",   scene->nbpt);
        printf("nombre de Matieres :\t%d\n", scene->nbmat);
        printf("nombre de Faces :\t%d\n",    scene->nbface);
        printf("nombre d'objets :\t%d\n",    scene->nbobj);
        printf("nombre de Sources :\t%d\n",  scene->nbsource);
        printf("---------------------------------------------\n");


        for (i = 0 ; i < scene->nbpt ; i++)  /* boucle sur les nombre de pt */
        {
                printf("point no %d :\t%lf\t%lf\t%lf\t%lf\n",
                       i,
                       scene->tabpt[i].x,
                       scene->tabpt[i].y,
                       scene->tabpt[i].z,
                       scene->tabpt[i].w);
        }
        printf("---------------------------------------------\n");

        for (i = 0 ; i < scene->nbmat ; i++) {
                printf("Matiere no %d :\n", i);
                printf("\talpha \t\t= %lf\n",scene->tabmat[i].alpha);
                printf("\tambiante \t= %lf\t%lf\t%lf\n",
                       scene->tabmat[i].ambiante.r,
                       scene->tabmat[i].ambiante.g,
                       scene->tabmat[i].ambiante.b);
                printf("\tdiffuse \t= %lf\t%lf\t%lf\n",
                       scene->tabmat[i].diffuse.r,
                       scene->tabmat[i].diffuse.g,
                       scene->tabmat[i].diffuse.b);
                printf("\temission \t= %lf\t%lf\t%lf\n",
                       scene->tabmat[i].emission.r,
                       scene->tabmat[i].emission.g,
                       scene->tabmat[i].emission.b);

                printf("\tspeculaire \t= %lf\t%lf\t%lf\n",
                       scene->tabmat[i].speculaire.r,
                       scene->tabmat[i].speculaire.g,
                       scene->tabmat[i].speculaire.b);

                printf("\tbrillance \t= %lf\n", scene->tabmat[i].brillance);
        }
        printf("---------------------------------------------\n");


        for (i = 0 ; i < scene->nbface ; i++)      /* boucle sur les nbface Scene::FACEs */
        {
                printf("Face %d : %d points\n",i , scene->tabface[i].nbpt);
                printf("\t\tindices des points : ");
                for (j = 0 ; j < scene->tabface[i].nbpt ; j++) /* boucle sur les nbpt
                                                                                                                                                                                                                                                                points de la Scene::FACE */
                        printf("\t%d",scene->tabface[i].tabpt[j]);
                printf("\n\tindice Matiere : \t%d\n", scene->tabface[i].imat);
        }
        printf("---------------------------------------------\n");


        for (i = 0 ; i < scene->nbobj ; i++) {
                printf("objet %d : %d Faces\n",i, scene->tabobj[i].nbface);
                for (j = 0 ; j < scene->tabobj[i].nbface ; j++) {
                        printf("\tindices des Faces : ");
                        printf( "\t%d\n",scene->tabobj[i].tabface[j]);
                }

                printf("\tMatrice:\n\t%lf\t%lf\t%lf\t%lf\n",
                       scene->tabobj[i].transfo[0],
                       scene->tabobj[i].transfo[4],
                       scene->tabobj[i].transfo[8],
                       scene->tabobj[i].transfo[12]);
                printf("\t%lf\t%lf\t%lf\t%lf\n",
                       scene->tabobj[i].transfo[1],
                       scene->tabobj[i].transfo[5],
                       scene->tabobj[i].transfo[9],
                       scene->tabobj[i].transfo[13]);
                printf("\t%lf\t%lf\t%lf\t%lf\n",
                       scene->tabobj[i].transfo[2],
                       scene->tabobj[i].transfo[6],
                       scene->tabobj[i].transfo[10],
                       scene->tabobj[i].transfo[14]);
                printf("\t%lf\t%lf\t%lf\t%lf\n",
                       scene->tabobj[i].transfo[3],
                       scene->tabobj[i].transfo[7],
                       scene->tabobj[i].transfo[11],
                       scene->tabobj[i].transfo[15]);


        }
        printf("---------------------------------------------\n");


        for (i = 0 ; i < scene->nbsource ; i++) {
                printf("Scene no %d :\n", i);
                printf("\tambiante \t: %lf\t%lf\t%lf\n",
                       scene->tabsource[i].ambiante.r,
                       scene->tabsource[i].ambiante.g,
                       scene->tabsource[i].ambiante.b);

                printf("\tcouleur \t: %lf\t%lf\t%lf\n",
                       scene->tabsource[i].couleur.r,
                       scene->tabsource[i].couleur.g,
                       scene->tabsource[i].couleur.b);

                printf("\tposition \t: %lf\t%lf\t%lf\t%lf\n",
                       scene->tabsource[i].position.x,
                       scene->tabsource[i].position.y,
                       scene->tabsource[i].position.z,
                       scene->tabsource[i].position.w);

                printf("\tallure faisc. \t: %lf\t%lf\n",
                       scene->tabsource[i].allure_faisceau.k,
                       scene->tabsource[i].allure_faisceau.theta);

                printf("\tdirection \t: %lf\t%lf\t%lf\n",
                       scene->tabsource[i].direction.x,
                       scene->tabsource[i].direction.y,
                       scene->tabsource[i].direction.z);
                printf("---------------------------------------------\n");
        }
}

/*-------------------------------------------------------------------------*/
