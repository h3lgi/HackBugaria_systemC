#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char* argument;
    int len=0;
    
    if(argc != 2)
        {
            printf("%s(%d)\n", "you need to put one argument more");
            exit(1);
        }
    else
        {   

            len = strlen(argv[1])+1;
            strncpy(argument, argv[1], len);
            printf("argument = %s\n", argument);
        }
    
    return 0;

}
