#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "sorts.h"
#include "scan.h"
#include "dict.h"

int menu(int*);
int from(int*);
int where(int*);
int which(int*);
int bywhat(int*);
int direction(int*);

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);


	int ch = 1, stat=0, n=0;
	Dict *arr=NULL;
	while(ch != EOF){
		switch (ch){
			case 1:
				if (arr != NULL){
					free_array_dict(arr,n);
					free(arr);
					arr = NULL;
				}
				stat = from(&ch);	
				if (stat == EOF) break;	
				switch (ch){
				case 1:
					stat = input(&n, &arr);
					break;
				case 2:
					stat = inputf(&n, &arr);
					break;
				default:
					printf("and nothing happend...\n");
				}	
				break;
			case 2:
				stat = which(&ch);
				if (stat==EOF) break;
				int dir, sor;
				stat = bywhat(&sor); 
				if (stat==EOF) break;
				stat = direction(&dir);
				switch (ch){
					case 1:
						if (sor == 1){
							if (dir == 1){
								dss(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_word);
							} else if(dir==2){
								dss(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_aword);								
							} else{ 
								printf("and nothing happend...\n");
							}
						} else if (sor == 2){
							if (dir == 1){
								dss(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_defi);
							} else if(dir==2){
								dss(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_adefi);								
							} else{ 
								printf("and nothing happend...\n");
							}
						} else if (sor == 3){
							if (dir == 1){
								dss(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_emp);
							} else if(dir==2){
								dss(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_aemp);								
							} else{ 
								printf("and nothing happend...\n");
							}
						} else {
							printf("and nothing happend...\n");
						}
						break;
					case 2:
						if (sor == 1){
							if (dir == 1){
								qsort(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_word);
							} else if(dir==2){
								qsort(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_aword);								
							} else{ 
								printf("and nothing happend...\n");
							}
						} else if (sor == 2){
							if (dir == 1){
								qsort(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_defi);
							} else if(dir==2){
								qsort(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_adefi);								
							} else{ 
								printf("and nothing happend...\n");
							}
						} else if (sor == 3){
							if (dir == 1){
								qsort(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_emp);
							} else if(dir==2){
								qsort(arr, n, sizeof(Dict), (int (*)(const void *, const void *))dict_cmp_aemp);								
							} else{ 
								printf("and nothing happend...\n");
							}
						} else {
							printf("and nothing happend...\n");
						}
						break;
				}
				break;
			case 3:
				stat = where(&ch);
				if (stat == EOF) break;
				switch (ch){
				case 1:
					print_array_dict(arr, n);
					break;
				case 2:
					print_dict_file(arr, n);
					break;
				default:
					printf("and nothing happend...\n");	
				}
				break;
				
			default:
				printf("and nothing happend...\n");	
		}
		if (stat == EOF) break;
		if (arr == NULL){
			ch = 1;
			continue;
		}
		if (stat != EOF || arr != NULL)
			stat = menu(&ch);	
	}
	if (arr != NULL){
		free_array_dict(arr, n);
		free(arr);
	}
	return 0;
}

int menu(int *a){
	int stat;
	printf("-------MENU-------\n");
	printf("|(1) input array |\n");
	printf("|(2) sort array  |\n");
	printf("|(3) output array|\n");
	printf("------------------\n");
	stat = scan(a);
	return stat;
}

int where(int *a){
	int stat;
	printf("------where?------\n");
	printf("|(1) input stream|\n");
	printf("|(2) text file   |\n");
	printf("------------------\n");
	stat = scan(a);
	return stat;
}
int from(int *a){
	int stat;
	printf("-------from?------\n");
	printf("|(1) input stream|\n");
	printf("|(2) text file   |\n");
	printf("------------------\n");
	stat = scan(a);
	return stat;
}

int which(int *a){
	int stat;
	printf("----which sort?----\n");
	printf("|(1) dss          |\n");
	printf("|(2) qsort        |\n");
	printf("-------------------\n");
	do{
		stat = scan(a);
	}while(*a>=3 || *a<=0);
	return stat;
}

int bywhat(int *a){
	int stat;
	printf("---sort by what?---\n");
	printf("|(1) words        |\n");
	printf("|(2) definitions  |\n");
	printf("-------------------\n");
	//will sort alphabeticly words and definitions
	stat = scanf("%d", a);
	return stat;
}

int direction(int *a){
	int stat;
	printf("---direcly or reverse?---\n");
	printf("|(1) direcly            |\n");
	printf("|(2) reverse            |\n");
	printf("-------------------------\n");
	stat = scan(a);
	return stat;
}
