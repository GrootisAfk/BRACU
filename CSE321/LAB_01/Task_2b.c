#include<stdio.h>
#include <string.h>

int main()
{
    char str[20][200],buffer[200];
    int i=0;

    FILE *file_in, *file_out;
    file_in=fopen("file1.txt", "r");
    file_out=fopen("output.txt","w");
    while(fgets(buffer,200,file_in)){
        strcpy(str[i],buffer);
        i++;
    }
    // printf("%s",str);
    char *lst = strtok(str, " ");
    while( lst != NULL ) 
    {
    //    printf( "%s ", lst );
       fprintf(file_out, "%s ",lst);
       lst = strtok(NULL, " ");
    }
    fclose(file_in);
    fclose(file_out);
    return 0;
}