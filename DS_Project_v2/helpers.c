#include <stdio.h>
#include <stdlib.h>
#include<gmp.h>
#include"_Headers/ntheory.h"
#include<time.h>
#include<string.h>
#include<assert.h>
#include"_Headers/helpers.h"
#define bufSize 3072
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}
int *decimal_to_binary(int n,int* l)
{
	int *a=(int*)malloc(sizeof(int)*bufSize),i;
	for(i=0;n>0;i++)
	{
	a[i]=n%2;
	n=n/2;
	}
  *l=i;
	return a;
}
