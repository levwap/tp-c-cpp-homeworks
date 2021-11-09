#include "static.h"




int ranking(char directory[], char search_request[])
{
    DIR *d;
    struct dirent *dir;
    printf("%s\n", directory);
    d = opendir(directory);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return(0);
}

int number_substrings(char string[], char substring[])
{
    int result = 0;
    for (int i = 0; string)
}