#ifndef MERGESORT_H
#define MERGESORT_H

#include <stddef.h>

void mergesort(
    void *array,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *)
);
void sort( void *array, int left, int right, size_t elements, size_t element_size, int (*comparator)(const void *, const void *));
void replace(void *a, void *b, size_t element_size);
#endif
