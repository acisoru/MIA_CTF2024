#ifndef DICT_H
#define DICT_H

typedef struct{
	char *word, *defi;
	int emp;
} Dict;

Dict dict_new(char *, char*, int);
void dict_print(const Dict *d);
int  dict_cmp_emp(const Dict *d1, const Dict *d2);
int  dict_cmp_aemp(const Dict *d1, const Dict *d2);
int  dict_cmp_word(const Dict *d1, const Dict *d2);
int  dict_cmp_aword(const Dict *d1, const Dict *d2);
int  dict_cmp_defi(const Dict *d1, const Dict *d2);
int  dict_cmp_adefi(const Dict *d1, const Dict *d2);

void print_dict(const Dict*);
void print_array_dict(const Dict *arr, int n);
void free_dict(const Dict*);
void free_array_dict(const Dict*, int);
int  print_dict_file(const Dict*, int);

int  scan(int*);
int  input(int  *, Dict **);
int  inputf(int *, Dict **);

int  inputff(int *, Dict **, char *);
#endif
