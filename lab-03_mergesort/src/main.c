#include "mergesort.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int Int_Comparator(const void *p1, const void *p2)
{	
    return (*(int*)p1 - *(int*)p2);
}

int Char_Comparator(const void *p1, const void *p2)
{	
    return (*(char*)p1 - *(char*)p2);
}

int String_Comparator(const void *p1, const void *p2)
{
    int k = 0;
    while (*(*(char**)p1 + k) == *(*(char**)p2 + k) && *(*(char**)p1 + k)){
	k++;
    }
    return (*(*(char**)p1 + k) - *(*(char**)p2 + k));
}

int main(int argc, char **argv)
{
    size_t element_size;	
    if(argv[1][0] == 'i'){
        element_size = sizeof(int);
        int *array = malloc((argc - 2) * sizeof(int));
	argv += 2;
        for(int i = 2; i < argc; i++){
            *array = atoi(*argv); 
	    array++;
	    argv++;
	}
	array -= argc - 2;
	mergesort(array, argc - 2, element_size, *Int_Comparator);
	for(int i = 2; i < argc; i++) {
	    if(i != 2) printf(" ");
	    printf("%d", array[i - 2]);                
	}
	printf("\n");
	free(array);
    }
    else if(argv[1][0] == 'c'){
        element_size = sizeof(char);
        char *array = malloc((argc - 2) * sizeof(char));
        argv += 2;
        for(int i = 2; i < argc; i++){
            *array = **argv;
	    argv++;
	    array++;
	}
	array -= argc - 2;	
	mergesort(array, argc - 2, element_size, *Char_Comparator);
	for(int i = 2; i < argc; i++) {
	    if(i != 2) printf(" ");
	    printf("%c", array[i - 2]);                
	}
	printf("\n");
	free(array);
    }
    else if(argv[1][0] == 's'){
        element_size = sizeof(char*);
        char **array = malloc((argc - 2) * sizeof(char*));
        argv += 2;
        for(int i = 2; i < argc; i++){
            *array = *argv;
	    argv++;
	    array++;
	}
	array -= argc - 2;
	mergesort(array, argc - 2, element_size, *String_Comparator);
	for(int i = 2; i < argc; i++) {
	    if(i != 2) printf(" ");
	    char *start = array[i - 2];
	    while(*start != '\0'){
		printf("%c", *start);
		start++;
	    }               
	}
	printf("\n");
	free(array);
    }
}
