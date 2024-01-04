#include "str.h"
#include <assert.h>
#include "string.h"

void test_strcpy()
{
    char str1[20] = "C programming";
    char str2[20];
    char* result = my_strcpy(str2, str1);
    char str3[20] = "C programming";
    char str4[20];
    strcpy(str4, str3);
    assert(strcmp(result, str4) == 0);
}

void test_strcat()
{
    char str1[20] = "C programming";
    char str2[11] = " is good:)";
    char* result = my_strcat(str1, str2);
   
    char str3[20] = "C programming";
    char str4[11] = " is good:)";
    strcat(str3, str4);
    assert(strcmp(result, str3) == 0);

}

void test_strcmp()
{
    char str1[] = "abcd", str3[] = "abcd";
    int result = my_strcmp(str1, str3);
    assert(result == 0);	

}

void test_strlen()
{
    char str1[] = "abcd";
    int result = my_strlen(str1);
    assert(result == 4);
}
