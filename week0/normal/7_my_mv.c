#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv)
{

    char out;
    char* new_path;
    int len=0;
    FILE* f_out, *f_in;

    if(argc != 3)
    {
        printf("%s(%d)\n", "you need to put one argument more");
        exit(1);
    }
    else
    {
        f_out=fopen(argv[1], "r");
        if(f_out==NULL)
        {
            puts ("canot open file for reading");
            exit(1);
        }

        len=strlen(argv[1]) + strlen(argv[2]) + 2;
        new_path=(char*)malloc(sizeof(char)*len);
        //for(i=1, i<=argc)
        //{
          //  strncpy()
       // }
        new_path=strcat(argv[2], argv[1]);
        f_in=fopen(new_path, "w");
        if(f_in==NULL)
        {
            puts ("cannot open file for writing");
            exit(1);
        }
    }

    do
    {
        out = fgetc(f_out);
        fputc(out, f_in);

    }while(out != EOF);

    unlink(argv[1]);
}
