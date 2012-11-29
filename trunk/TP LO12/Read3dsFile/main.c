#include <stdio.h>
#include <stdlib.h>
#include "lib3ds.h"

static int  log_level = LIB3DS_LOG_ERROR;
/* ========================================================================= */
static long
fileio_seek_func(void *self, long offset, Lib3dsIoSeek origin) {
	FILE *f = (FILE*)self;
	int o;
	switch (origin) {
		case LIB3DS_SEEK_SET:
			o = SEEK_SET;
			break;

		case LIB3DS_SEEK_CUR:
			o = SEEK_CUR;
			break;

		case LIB3DS_SEEK_END:
			o = SEEK_END;
			break;
	}
	return (fseek(f, offset, o));
}


static long
fileio_tell_func(void *self) {
	FILE *f = (FILE*)self;
	return(ftell(f));
}


static size_t
fileio_read_func(void *self, void *buffer, size_t size) {
	FILE *f = (FILE*)self;
	return (fread(buffer, 1, size, f));
}


static size_t
fileio_write_func(void *self, const void *buffer, size_t size) {
	FILE *f = (FILE*)self;
	return (fwrite(buffer, 1, size, f));
}


static void 
fileio_log_func(void *self, Lib3dsLogLevel level, int indent, const char *msg)
{
	static const char * level_str[] = {
		"ERROR", "WARN", "INFO", "DEBUG"
	};
	if (log_level >=  level) {
		int i;
		printf("%5s : ", level_str[level]);
		for (i = 1; i < indent; ++i) printf("\t");
		printf("%s\n", msg);
	}
}
/* ========================================================================= */

void main(void)
{
	FILE *fileSce;
	Lib3dsFile* file3ds;
	Lib3dsIo io;
	int result;

	fileSce = fopen("models\\jeep.3ds","rb");
	if(!fileSce){
		printf("Erreur : fichier introuvable\n");
		system("PAUSE");
		exit(1);
	}
	file3ds = lib3ds_file_new();
	io.self = fileSce;
	io.seek_func = fileio_seek_func;
	io.tell_func = fileio_tell_func;
	io.read_func = fileio_read_func;
	io.write_func = fileio_write_func;
	io.log_func = fileio_log_func;

	result =  lib3ds_file_read(file3ds, &io);

	printf("Le fichier jeep.3ds contient :\n");
	printf("\t%d maillage(s)\n",file3ds->nmeshes);
	printf("\t%d camera(s)\n",file3ds->ncameras);
	printf("\t%d lumiere(s)\n",file3ds->nlights);
	printf("\t%d materiau(x)\n",file3ds->nmaterials);
	system("PAUSE");
	
	fclose(fileSce);

	lib3ds_file_free(file3ds);
}