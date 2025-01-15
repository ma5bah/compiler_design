#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main( )
{
    char word[1000];
    char code[100000];
    int lc=0;
    int end_of_file=false;
    int count_bracket=0;
    bool first_bracket=false;
    while(fgets(word,sizeof(word),stdin)!=NULL)
    {
        // printf("%s",word);
        int size_of_line=0;
        while(word[size_of_line]!= '\0' && word[size_of_line]!= '\n')
        {
            size_of_line++;
        }
        int i=0;
        while(i<size_of_line)
        {
            if(word[i]=='{')
            {
                count_bracket++;
                first_bracket=true;
            }
            if(word[i]=='}')count_bracket--;
            if(isspace(word[i])){
                code[lc++]='\n';
            }
            while (isspace(word[i++]));
            code[lc++]=word[i];
            i++;
        }
        if(count_bracket==0&&first_bracket)
        {
            end_of_file=true;
            code[i]='\0';
            break;
        }
    }
    printf("%s",code);

    return (0);
}