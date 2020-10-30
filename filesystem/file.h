#ifndef __FILE_H__
#define __FILE_H__

typedef struct List {

	// fisier/director (lista generica)
	void *data;

	// lista dubla inlantuita
	struct List *prev;
	struct List *next;
} List;

typedef struct Directory {
    char *name;

    struct List *file_list;

    struct List *dir_list;

    struct Directory *parentDir;
} Directory;


typedef struct File {
    char *name;

    int size;

    char *data;

    Directory *dir;
} File;

#endif 
