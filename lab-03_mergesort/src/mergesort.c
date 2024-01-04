#include "mergesort.h"
#include <stdlib.h>
#include <stdio.h>


void mergesort( void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *))
{
    sort(array, 0, elements - 1, elements, element_size, comparator);
}

void sort( void *array, int left, int right, size_t elements, size_t element_size, int (*comparator)(const void *, const void *))
{
    char *p = array;
    if(left >= right)
	return;
    int middle = (right + left) / 2;
    sort(array, left, middle, elements, element_size, comparator);
    sort(array, middle + 1, right, elements, element_size, comparator);
    int i = left, j = middle + 1, k = left;
    char *t = malloc(elements * element_size);
    while (i <= middle && j <= right){
        if(comparator(p + i * element_size, p + j * element_size) <= 0){
            replace(t + (k++) * element_size, p + (i++) * element_size, element_size);
        }
        else{
            replace(t + (k++) * element_size, p + (j++) * element_size, element_size);
        }
    }
    while(i <= middle){
        replace(t + (k++) * element_size, p + (i++) * element_size, element_size);
    }
    while(j <= right){
        replace(t + (k++) * element_size, p + (j++) * element_size, element_size);
    }

    for(int pos = left; pos < k; pos++){
        replace(p + pos * element_size, t + pos * element_size, element_size);
    }
    free(t);
}

void replace(void *to, void *from, size_t element_size)
{
    
    char *a = to, *b = from;
    int m = 0;
    while(m < element_size){
        *(a + m) = *(b + m);
        m++;
    }
}
