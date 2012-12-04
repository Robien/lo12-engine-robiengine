

#include <string.h>
#include <iostream>


#include "Tp.h"

void main(int argc, char**argv)
{


	Tp tp;

	/*
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
		*/
		 glutInit(&argc, argv);




		 tp.run();


}