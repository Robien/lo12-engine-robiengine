

#include <string.h>
#include <iostream>


#include "Tp.h"
#include "DatUtils.h"

void main(int argc, char**argv)
{
	int i,verbose=1;
	char   default_filename[80] = MODELS_PATH SCENE_FILE_NAME;
	char *filename=default_filename;

	Tp tp;


        for(i=1;i<argc;i++)
		{
                if(!strcmp("-v",argv[i]))
				{
                        verbose=1;
				}
                if(!strcmp("-f",argv[i]))
				{
                        if(i+1<argc)
						{
                                filename=argv[i+1];
						}
                }
        }
		 glutInit(&argc, argv);




		 tp.run(filename, verbose);


}