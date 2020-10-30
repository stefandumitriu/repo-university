#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include <string.h>

void update_list(Directory *curr_dir, List **list, void *new_data, size_t data_size) {
	
	List *new_entry = (List *) malloc(sizeof(List));
	new_entry->data = malloc(data_size);
    for (int i = 0; i < data_size; i++) 
        *(char *)(new_entry->data + i) = *(char *)(new_data + i); 

	List *p = curr_dir->file_list;
	while(p->next != NULL) {
		p = p->next;
	}
	p->next = new_entry;
	new_entry->next = NULL;
	new_entry->prev = p;
	
}

void get_input(char *cmd, char args[][256], int *nr_arg) {

	(*nr_arg) = 0;
	fgets(cmd, 256, stdin);
	cmd[strlen(cmd) - 1] = '\0';
	
	char *aux;
	aux = strdup(cmd);
	
	char *p;
	p = strtok(cmd, " ");
	
	while(p) {
		strcpy(args[(*nr_arg)++], p);
		p = strtok(NULL, " ");
	}
	(*nr_arg)--;
}

void create_fs(Directory *root) {
	root->name = strdup("/");
	root->parentDir = NULL;
	root->file_list = NULL;
	root->dir_list = NULL;
}

void touch(File *new_file, char *name, char *content, Directory *curr_dir) {
	new_file->name = strdup(name);
	new_file->size = strlen(content);
	new_file->data = strdup(content);
	new_file->dir = curr_dir;
	update_list(curr_dir, &curr_dir->file_list, new_file, sizeof(File));
}

int main() {
	char cmd[256];
	char args[10][256];
	int nr_arg = 0;
	Directory root;
	Directory new_dir;
	Directory curr_dir;
	File new_file;
	get_input(cmd, args, &nr_arg);
	while(strcmp(args[0], "create") || strcmp(args[1], "fs")) {
		printf("No file system, use <create fs>\n");
		get_input(cmd, args, &nr_arg);
	}
	create_fs(&root);
	curr_dir = root;
	printf("%s\n", root.name);
	while(strcmp(args[0], "delete")) {
		get_input(cmd, args, &nr_arg);
		printf("%s\n", args[0]);
		if(!strcmp(args[0], "touch")) {
			touch(&new_file, args[1], args[2], &curr_dir);
			printf("%s %s %s", args[0], args[1], args[2]);
		}
	}
	return 0;
}
