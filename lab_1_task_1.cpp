#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main( )
{
    int c;
    char word[1000];
    int word_size=0;
    FILE *input_file;
    input_file = fopen("./1904001_input.txt", "r");
    if (input_file == 0)
    {
        perror("Can't open input file\n");
        exit(-1);
    }

    FILE *output_file;
    output_file = fopen("./1904001_output.txt", "w");
    if (output_file == 0)
    {
        perror("Can't open output file\n");
        exit(-1);
    }
    int flag=true;
    while ((c = fgetc(input_file)) != EOF )
    {
        if (isspace(c) && flag)
        {
            flag=false;
            printf("\n");
            int d='\n';
            fprintf(output_file,"\n");
            continue;
        }

        if (!isspace(c) )
        {
            //fprintf(output_file,c);
            flag=true;
            printf("%c",c);
            putc(c,output_file);
        }
    }
    fclose(output_file);
    fclose(input_file);

    printf("\n");

    return (0);
}