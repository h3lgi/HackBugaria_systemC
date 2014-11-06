
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    char out;
    FILE *f_out, *f_in;

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
                puts ("Canot open file for reading");
                exit(1);
            }

            f_in=fopen(argv[2], "w");
            if(f_in==NULL)
            {
                puts("Cannot open file for writing");
                exit(1);
            }

        }
    do 
    {
        out = fgetc(f_out);
        fputc(out, f_in);
    }while(out != EOF);


    fclose(f_out);
    fclose(f_in);
    return 0;
}
