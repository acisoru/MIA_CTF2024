#include <stdlib.h>
#include <string.h>
#include "sorts.h"

void swap(void *a, void *b, size_t size){
	// printf("%d %d\n", sizeof(a), sizeof(b));
	void *tmp=malloc(size);
	memcpy(tmp, a, size);
	memcpy(a, b, size);
	memcpy(b, tmp, size);
	free(tmp);
	return;
	// char *x = (char*) (a), *y = (char*) (b);
	// while(size>0) {
	// 	char tmp = *x;
	// 	*x++ = *y;
	// 	*y++ = tmp;
	// 	--size;
	// };
	// return;
}

void dss(void *arr, size_t n, size_t size, int (*cmp)(const void*, const void*)){
	// char *arr = (char *) tmp;
	void *max=calloc(size, 1);
	void *min=calloc(size, 1);
	for (size_t i = 0, j=n-1;i<j;++i,--j){
		size_t min_i = i, max_i = i;
		memcpy(min, (arr+i*size), size);
		memcpy(max, (arr+i*size), size);
		for (size_t k = i; k<=j;k++){
			if (cmp(arr+k*size, max)>0){
				max_i = k;
				memcpy(max, (arr+k*size), size);
			} else if (cmp(arr+k*size, min)<0){
				min_i = k;
				memcpy(min, (arr+k*size), size);
			}
		}
		swap((arr+j*size), (arr+min_i*size), size);

		if (cmp(arr+min_i*size, max) == 0){
			swap(arr+j*size, arr+min_i*size, size);
		} else{
			swap(arr+j*size, arr+max_i*size, size);			
		}
	}
	free(max);
	free(min);
	return;
}
