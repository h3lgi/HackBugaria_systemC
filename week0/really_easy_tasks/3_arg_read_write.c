
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char* argument;
    char* file_name;
    int len=0;
    FILE* f;
    if(argc != 3)
        {
            printf("%s(%d)\n", "you need to put one argument more");
            exit(1);
        }
    else
        {
            len=strlen(argv[1])+1;
            argument = (char*)malloc(sizeof(char) * len);
            strncpy(argument, argv[1], len);

            len=strlen(argv[2])+1;
            file_name = (char*)malloc(sizeof(char) * len);
            strncpy(file_name, argv[2], len);
        }
    f = fopen(file_name, "w");
    if(f==NULL)
    {
        puts ("Cannot open file for writing");
        exit (1);
    }


    fprintf(f, "this is a argument:-> %s\n", argument);

    fclose(f);
    return 0;
}
