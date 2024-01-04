#include <stddef.h>
#include "str.h"

char* my_strcpy(char* restrict destination, const char* restrict source)
{
    char* temporary = destination;
    while(*destination++ = *source++);
    return temporary;
}

char* my_strcat(char* restrict destination, const char* restrict source)
{
    char* temporary = destination;
    while(*destination != '\0')
	destination++;
    while(*destination++ = *source++);
    return temporary;
}

int my_strcmp(const char* destination, const char* source)
{
    while(*source == *destination && *destination && *source) {
	source++;
	destination++;
   }
   return *destination - *source;
}

size_t my_strlen(const char* source)
{
    const char* pointer = source;
    while((*source++));
    return (source - 1) - pointer;
}
