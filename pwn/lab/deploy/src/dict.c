#include "dict.h"
#include "scan.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>

Dict dict_new(char *word, char *defi, int emp){
	Dict d = {word, defi, emp};
	return d;
}

int dict_cmp_emp(const Dict *d1, const Dict *d2){
	return d1->emp - d2->emp;
}

int dict_cmp_aemp(const Dict *d1, const Dict *d2){
	return d2->emp - d1->emp;
}

int dict_cmp_word(const Dict *d1, const Dict *d2){
	char *s1 = d1->word;
	char *s2 = d2->word;
	while(*s1 || *s2){
		if((int)*s1-(int)*s2 != 0){
			return (int)(*s1)-(int)(*s2);
		}
		s1++;
		s2++;
	}
	return 0;
}

int dict_cmp_aword(const Dict *d1, const Dict *d2){
	char *s2 = d1->word;
	char *s1 = d2->word;
	while(*s1 || *s2){
		if((int)*s1-(int)*s2 != 0){
			return (int)(*s1)-(int)(*s2);
		}
		s1++;
		s2++;
	}
	return 0;
}

int dict_cmp_defi(const Dict *d1, const Dict *d2){
	return strcmp(d1->defi,d2->defi);
}

int dict_cmp_adefi(const Dict *d1, const Dict *d2){
	return strcmp(d2->defi,d1->defi);
}

void free_dict(const Dict*d){
	free(d->word);
	free(d->defi);
}

void free_array_dict(const Dict*arr, int n){
	for (int i=0;i<n;i++){
		free_dict(arr+i);
	}
}

void print_dict(const Dict *d){
	printf("Word: %s\n", d->word);
	printf("Definition: %s\n", d->defi);
	printf("Emphasis: %d\n", d->emp);
}

void print_array_dict(const Dict *arr, int n){
	for (int i=0;i<n;++i){
		printf("Note %d\n",i+1);
		print_dict(arr+i);
	}
}

int print_dict_file(const Dict *arr, int n){
	FILE *f = NULL;
	do{
	char *filename = readline("Input name of file\n");	
	char *tmp=strstr(filename, ".txt");	
	if (!tmp || *(tmp+4) != '\0'){
		printf("should be *.txt file.\n");
		free(filename);
		continue;
	}
	if (filename == NULL){
		printf("ERROR: EOF\n");
		return EOF;
		}					
	f = fopen(filename, "wb");
	free(filename);
	} while (f==NULL);
	
	fprintf(f, "%d\n", n);
	for (int i=0;i<n;++i){
		fprintf(f, "%s\n%s\n%d\n", (arr+i)->word, (arr+i)->defi, (arr+i)->emp);
	}
	fclose(f);
	return 0;
}

int scan(int *a){
	int stat;
	do{
		stat = scani(a);
		if (stat == EOF){printf("nothing happend...\n"); *a = EOF; break;}
	} while (*a < 1);
	return stat;
}

 #define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

int input(int *n, Dict **arr){
	printf("Input number of objects\n");
	int stat = scani(n);
	if (stat == EOF) return EOF;	
	for (int i=0;i<*n;++i){
		printf("Input word (length <= 50)\n");
		char word[50];
		memset(word,0,50);
		read(0, word, 51);
		
		printf("%d\n", word[strlen(word)-1]);
		word[min(strlen(word)-1, 50)] = 0;
		printf("Input definition (length <= 100)\n");
		char defi[100];

		memset(defi,0,100);
		read(0, defi, 1010);

		defi[min(strlen(defi)-1, 100)] = 0;
		int emp;
		printf("Input emphasis\n");
		int stat = scani(&emp);
		if (stat == EOF){
			*n=i;
			return EOF;
		}
		if (!*arr){
			*arr = malloc(sizeof(Dict));
			if (*arr == NULL) return -2;
		} else {
			*arr = realloc(*arr, sizeof(Dict)*(i+1));
			if (*arr == NULL) return -2;
		}
		char *tmp_word = calloc(1,strlen(word)+1);
		char *tmp_defi = calloc(1,strlen(defi)+1);
		strcpy(tmp_word, word);
		strcpy(tmp_defi, defi);
		
		(*arr)[i] = dict_new(tmp_word,tmp_defi,emp);
		
	}
	return 0;
}

int inputf(int *n, Dict**arr){
	int emp;
	char * word, *defi;
	FILE *text=NULL;
	do{
		char *filename = readline("Input name of file\n");	
		if (filename == NULL){
			printf("ERROR: EOF\n");
			return EOF;
			}	
		char *tmp=strstr(filename, ".txt");	
		if (!tmp || *(tmp+4) != '\0'){
			printf("should be *.txt file.\n");
			free(filename);
			continue;
		}				
		text = fopen(filename, "r");
		free(filename);
		if (text == NULL){printf("No such file.\n");}
	}while(text==NULL);
	fscanf(text, "%d%*c", n);
	for (int i=0;i<*n;i++){
		word = freadline(text);
		defi = freadline(text);
//		printf("%s\n %s\n", word, defi);
		if (defi == NULL || word == NULL){
			printf("It is too bad, exiting");
			fclose(text);
			return -2;
		}
		char *tmp = freadline(text);
		emp = atoi(tmp);
		free(tmp);
		if (strlen(word) > 20){
			printf("Something went wrong. Skip object number: %d\n", i+1);
			(*n)--;
			(i)--;
			free(word);
			free(defi);
			continue;
		}
		if (!*arr){
			*arr = malloc(sizeof(Dict));
			if (*arr == NULL) return -2;
		} else {
			*arr = realloc(*arr, sizeof(Dict)*(i+1));
			if (*arr == NULL) return -2;
		}
		(*arr)[i] = dict_new(word,defi,emp);
	}
	fclose(text);
	return 0;
}

int inputff(int *n, Dict**arr, char *name){
	FILE *f = fopen(name, "r");

	fread(n, sizeof(int), 1, f);
	
		char *word = NULL;
		char *defi = NULL;
		
		int * wordlist = malloc(*n*sizeof(int));
		int * lenwlist = malloc(*n*sizeof(int));
		
		int * defilist = malloc(*n*sizeof(int));
		int * lendlist = malloc(*n*sizeof(int));
		if (wordlist == NULL || defilist == NULL || lenwlist == NULL || lendlist == NULL){
			return EOF;
		}
		int*emplist = malloc(*n*sizeof(int));
		for (int i=0;i<*n;i++){
			fread((lenwlist+i), sizeof(int), 1, f);
			fread((lendlist+i), sizeof(int), 1, f);
			fread((emplist+i), sizeof(int), 1, f);
		}
		int skipped = 0;
		for (int i=0;i<*n;i++){
			word = calloc(lenwlist[i]+1,sizeof(char));
			defi = calloc(lendlist[i]+1,sizeof(char));		
			if (word == NULL || defi == NULL){
				return EOF;
			}
			fread(word, sizeof(char), lenwlist[i], f);
			fread(defi, sizeof(char), lendlist[i], f);		
			if (lenwlist[i]>20){
				printf("Word is too long, skip...");
				free(word);
				free(defi);
				skipped++;
			} else {
				if (!*arr){
					*arr = malloc(sizeof(Dict));
					if (*arr == NULL) return -2;
				} else {
				*arr = realloc(*arr, sizeof(Dict)*(i+1));
					if (*arr == NULL) return -2;
				}
				(*arr)[i] = dict_new(word, defi, emplist[i]);
			}
			
		}
		*n = (*n)-skipped;
		free(wordlist);
		free(defilist);
		free(lenwlist);
		free(lendlist);
		free(emplist);
		fclose(f);
		return 0;
}

void win(){
	//fscanf(myfile, "%s%d", str, &a);
	FILE *file = fopen("flag", "r");
	char flag[64];
	fgets(flag, 64, file);
	printf("%s", flag);
}
