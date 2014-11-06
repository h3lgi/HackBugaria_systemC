#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char* argument;
    int len=0;
    FILE* f;

    if(argc != 2)
        {
            printf("%s(%d)\n", "you need to put one argument more");
            exit(1);
        }
    else
        {
            f=fopen(argv[1], "r");
            if(f==NULL)
            {
                puts ("Canot open file for reading");
            }

        }
    fseek(f, 0L, SEEK_END);
    len = ftell(f);
    argument = (char *)malloc(sizeof(char) * len );
    fseek(f, 0L, SEEK_SET);

    //while(ftell(f) != sz)
    //{
    //    fscanf(f, "%s", argument);
    //}
    fread(argument, len, 1, f);
    
    write(1, argument, len);

    fclose(f);
    return 0;
}
