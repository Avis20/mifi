//#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct itm{
	int key;
	//int release;
	int size;
	int offset;
	struct itm *next;
}itm;

typedef struct tbl{
	int size;
	itm **list; 
	FILE *file;
	char *filename;
}tbl;

//void pause();
char *check_data(char *);
char *add_extension(char *, char *);
int check_number(int *);
int hash(int, int);
int freemem(itm **);

int add_tbl(tbl *, int, char *);
int del_tbl(tbl *);
int show_tbl(tbl *);
int search_tbl(tbl *, itm *, int);


itm *find(itm *, int);


int dialog(char *[], int, tbl *);
int dialog_add(tbl *);
int dialog_del(tbl *);
int dialog_show(tbl *);
int dialog_search(tbl *);

int (*f[])(tbl *) = {
	NULL,
	dialog_add,
	dialog_search,
	dialog_del,
	dialog_show
};

char *menu[] = {
	"0. Quit",
	"1. Add",
	"2. Find",
	"3. Delete",
	"4. Show"
};

void open(tbl *);
void load(tbl *);
void close(tbl *);

char *read_data(FILE *, itm *, char *);
int write_data(FILE *, char *, int);



int main(){
	int i = 0;
	tbl t = {0, NULL, NULL, NULL};
	//setlocale(LC_ALL,"RUS");
	open(&t);
	while(i = dialog(menu, sizeof(menu)/sizeof(menu[0]), &t))
		if(f[i](&t)) break;
	
	close(&t);
	return 0;
}

int dialog(char *m[], int n, tbl *t){
	int i, choice;
	char *msg = "";

	//system("cls");
	
	printf("\nMenu program: \n");
	for(i = 0; i < n; i++)
		printf("%s\n",m[i]);

	printf("\nSelect the menu item: ");
	do{
		printf("%s",msg);
		msg = "No such item! Enter again: ";
		while(check_number(&choice));

	}while(choice < 0 || choice >= n);
	return choice;
}

char *read_data(FILE *file, itm  *node, char *data){
	fseek(file, node->offset, SEEK_SET);
	fread(data, sizeof(char), node->size, file);
	return data;
}

int show_tbl(tbl *t){
	int i = 0, f = -1;
	char *data = NULL;
	itm *p = NULL;
	
	for(i = 0; i < t->size; i++)
		if((p = t->list[i]) != NULL){
			f = 0;
			printf("t key: %i --------------------------\n", i);
			while(p){
				data = (char *)calloc(p->size, sizeof(char));
				data = read_data(t->file, p, data);
				printf("%d\t%s\n", p->key, data);
				free(data);
				p = p->next;		
			}
		}
	return f;
}

int dialog_show(tbl *t){
	//system("cls");
	printf("Displays the contents of the table: \n");
	printf("Key\tRelease\tInfo\n");

	if(show_tbl(t))
		printf("The table contains no elements!\n");

	return 0;
}
int search_tbl(tbl *t, itm *p, int k){
	itm *tmp = NULL;
	while(p){
		if(k == p->key){
			tmp = (itm *)calloc(1, sizeof(itm));
			tmp->key = p->key;
			tmp->size = p->size;
			tmp->offset = p->offset;
			tmp->next = t->list[0];
			t->list[0] = tmp;
		}
		p = p->next;
	}
					
	return 0;
}

int dialog_search(tbl *t){
	int key = 0;
	tbl newt = {1, (itm **)calloc(1,sizeof(itm *)), t->file, NULL};
	//system("cls");
	printf("Enter new element: \n");
	printf("Enter key:\n");
	if(check_number(&key))
		return 0;
	printf("Enter release:\n");
	search_tbl(&newt, t->list[hash(key, t->size)], key);
	dialog_show(&newt);
	freemem(newt.list);
	return 0;
}
int freemem(itm **p){
	itm *del, **tmp;
	tmp = p;
	while(*tmp){
		del = *tmp;
		*tmp = del->next;
		free(del);
	}
	return 0;
}

itm *find(itm *p, int k){
	while(p && p->key != k)
		p = p->next;
	return p;
}

int write_data(FILE *file, char *data, int size){
	int offset = 0;
	fseek(file, 0, SEEK_END);
	offset = ftell(file);
	fwrite(data, sizeof(char), size, file);
	return offset;
}

int add_tbl(tbl *t, int key, char *data){
	int i = hash(key, t->size);
	itm *newitm = NULL, *tmp = NULL;

	newitm = (itm *)calloc(1, sizeof(itm));
	newitm->key = key;
	newitm->size = strlen(data) + 1 ;
	newitm->offset = write_data(t->file, data, newitm->size);
	newitm->next = t->list[i];
	t->list[i] = newitm;
	
	return 0;	
}

int dialog_add(tbl *t){
	int key = 0;
	char *data = NULL;

	//system("cls");
	printf("Enter new element: \n");
	printf("Enter key:\n");
	if(check_number(&key))
		return 0;
	printf("Enter info:\n");
	data = check_data(data);
	if(add_tbl(t, key, data) < 0)
		printf("\nDuplicate key!\n\n");
	else
		printf("\nDone!\n");
	free(data);
	return 0;
}


int del_tbl(tbl *t){
	int i = 0, key = 0;
	itm **list = NULL, **tmp = NULL, *del = NULL;
	for(i = 0; i < t->size; i++){
		list = &t->list[i];
		while(*list){
			key = (*list)->key;
			tmp = &(*list)->next;
			while(*tmp){
				if((*tmp)->key == key){
					del = *tmp;
					*tmp = del->next;
					free(del);
				}
				else
					tmp = &(*tmp)->next;
			}
			list = &(*list)->next;
		}
	}
	return 0;
}

int dialog_del(tbl *t){
	int key = 0;
	//system("cls");
	printf("Reorganizing a table\n");
	del_tbl(t);
	printf("\nReorganization completed\n");
	return 0;
}

void open(tbl *t){
	char  *filename_data = NULL;
	//system("cls");
	printf("Enter file name: ");

	t->filename = check_data(t->filename);

	filename_data = add_extension(t->filename,".data");
	if(t->file = fopen(t->filename, "r+b")){
		printf("File is loaded!\n");
		load(t);
		fclose(t->file);
		t->file = fopen(filename_data,"r+b");
	}
	else{ 
		printf("Enter size of table: ");
		check_number(&t->size);
		t->list = (itm **)calloc(t->size, sizeof(itm *));
		
		printf("File is created!\n");
		t->file = fopen(filename_data,"w+b");
	}

	free(filename_data);
}



void load(tbl *t){
	int i = 0, count = 0;
	itm *current = NULL, *last = NULL;	
	
	fread(&t->size, sizeof(int), 1, t->file);
	
	t->list = (itm **)calloc(t->size, sizeof(itm *));	

	for(i = 0; i < t->size; count = 0,  i++){
	fread(&count, sizeof(int), 1, t->file);
		while(--count >= 0){
			current = (itm *)calloc(1, sizeof(itm));

			fread(&current->key, sizeof(int), 1, t->file);
			fread(&current->size, sizeof(int), 1, t->file);
			fread(&current->offset, sizeof(int), 1, t->file);
	
			if(t->list[i] == NULL)
				t->list[i] = current;
			else
				last->next = current;
	
			last = current;
		}
	}
}

void close(tbl *t){
	int i = 0, count = 0, offset = 0;
	itm *del = NULL, *p = NULL;
	fclose(t->file);
	t->file = fopen(t->filename,"w+b");
	fwrite(&t->size, sizeof(int), 1, t->file);

	for(i = 0; i < t->size; count = 0, i++){

		p = t->list[i];
	
		fseek(t->file, 0, SEEK_END);
		offset = ftell(t->file);
		fwrite(&count, sizeof(int), 1, t->file);

		while(p){
			count = count + 1;
			fwrite(&p->key, sizeof(int), 1, t->file);
			fwrite(&p->size, sizeof(int), 1, t->file);
			fwrite(&p->offset, sizeof(int), 1, t->file);

			del = p;
			p = del->next;
			free(del);
		}

		fseek(t->file, offset, SEEK_SET);
		fwrite(&count, sizeof(int), 1, t->file);
	}
	fclose(t->file);

	free(t->filename);
	free(t->list);
}	

int hash(int key, int size){
	return key % size;
}

int check_number(int *n){
	int ErrorCode;
	char tmp = ' ';
	while(!(1 == (ErrorCode = scanf("%d", n)))){
		if(ErrorCode == EOF){
			printf("Cancel enter!\n");
			return EOF;
		}
		else{
			scanf("%*[^\n]",tmp);
			printf("Input error! Input again: ");
		}
	}
	scanf("%1[\n]",&ErrorCode);
	return 0;
}

char *check_data(char *s){
	char buf[25] = "";
	int i = 0;
	do{
		while(EOF == scanf("%24[^\n]",buf)) 
			printf("Input error! Input again: ");
		if(!i++) 
			s = (char *)calloc(sizeof(buf),sizeof(char));
		else
			s = (char *)realloc(s, i * sizeof(buf));
		strcat(s, buf);
	}while(!scanf("%1[\n]",buf));
	return s;
}

char *add_extension(char *filename, char *extension){
	char *tmp = (char *)calloc(strlen(filename) + strlen(extension) + 1, sizeof(char));
	strcpy(tmp, filename);
	strcat(tmp, extension);
	return tmp;
}
/*void pause(){
	char tmp = ' ';
	printf("\nPress ENTER to continue... ");
	while(1 && scanf("%*c",tmp));
}*/
