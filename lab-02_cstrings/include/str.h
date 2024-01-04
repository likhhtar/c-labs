#ifndef STR_H
#define STR_H

#include <stddef.h>

char* my_strcpy(char* restrict destination, const char* restrict source);
char* my_strcat(char* restrict destination, const char* restrict source);
int my_strcmp(const char* destination, const char* source);
size_t my_strlen(const char* source);

#endif
