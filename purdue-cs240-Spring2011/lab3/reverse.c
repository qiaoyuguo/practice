#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *string);

/******************************************************************************
 * main() function
 ******************************************************************************/

int main(int argc, char **argv){

    int i;
    int len;
    char *buf = NULL;
    //check for arguments
    if(argc < 2)
    {
        printf("usage: reverse <string>");
        return -1;
    }
    
    //concatenate the strings
    for(i = 1; i < argc; i++)
        len = strlen(argv[i]);
    len += argc-1;
   
    buf = malloc(sizeof(char) * (len + 1));
    if(NULL == buf)
    {
        perror("allocate memory error");
        return -1;
    }

    memset(buf, 0, sizeof(char)* (len+1));
    for(i = 1; i <= argc-1; i++)
    {
        strcat(buf, argv[i]);
        if(i != argc -1)
            strcat(buf, " ");
    }
    //printf("buf = %s\n", buf);
    //reverse the string
    printf("Reverse of String = ");
    reverse(buf);
    printf("\n");
    free(buf);

    return 0;
}

/******************************************************************************
 * reverse() function using recursion
 ******************************************************************************/

void reverse(char *string){
    if( string[0] == '\0')
        return;
    else
    {
        reverse(&string[1]);
        putchar(string[0]);
    }
}
