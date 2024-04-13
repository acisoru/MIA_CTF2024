#include "scan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scani(int *x){
	int a;
	int check;
	char c = '\n';
	do{
	   check = scanf("%d", &a); // enter format is x,y
	   scanf("%c", &c);
		if (check == EOF) return EOF;
		if (check != 1|| c != '\n' || a < 0) printf("Incorrect input.\nTry again.\n");
		if (c != '\n'){
			scanf("%*[^\n]%*c");
		}
	}while(check != 1 || c != '\n' || a < 0);
	*x = a;
	return check;
}

int scanF(float *x){
	float a;
	int check;
	char c = '\n';
	do{
	   check = scanf("%f", &a); 
	   scanf("%c", &c);
		if (check == EOF) return EOF;
		if (check != 1|| c != '\n' || a < 0.0) printf("Incorrect input.\nTry again.\n");
		if (c != '\n'){
			scanf("%*[^\n]%*c");
		}
	}while(check != 1 || c != '\n' || a < 0.0);
	*x = a;
	return check;
}

int fscani(int *x, FILE *text){
	int a, stat;
	stat = fscanf(text, "%d", &a);
	if (stat != 1) return stat;
	*x = a;
	return stat;
}

char *freadline(FILE *text){	
	size_t len = 0, tmplen = 0;
	char *res = calloc(1, sizeof(char));
	char *tmp = calloc(17,sizeof(char));
	int stat = fscanf(text, "%16[^\n]", tmp);
	if (stat == EOF){
		free(res);
		free(tmp);
		return NULL;
	}
	
	while(stat != 0){
		tmplen = strlen(tmp);
		len += tmplen;
		char* tres = realloc(res,(len+1)*sizeof(char));
		if (tres == NULL){
			free(tmp);
			free(res);
			return NULL;
		}
		res = tres;
		strcat(res,tmp);
		res[len]='\0';
		stat = fscanf(text, "%16[^\n]",tmp);
	}
	//scanf("%*1[\n]");
	fscanf(text, "%*c"); 
	free(tmp);
	
	return res;
}
