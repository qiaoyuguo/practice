#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 300

int isPresent (char *mainString, char *subString);

/******************************************************************************
 * main() function
 ******************************************************************************/

int main(int argc, char **argv){

    char buf[MAX_SIZE] = {0};
    //check for arguments
    if(argc != 2)
    {
        printf("Usage: mygrep {String to Search} < {File Name}\n");
        return -1;
    }
    

    // iterate through all the lines in the input file and display those
    // which contain the string passed as command line argument
    while(fgets(buf, MAX_SIZE, stdin ) != NULL)
    {
        if(isPresent(buf, argv[1]))
            printf("%s", buf);
    }
	
    return 0;
}

/******************************************************************************
 * isPresent() function
 ******************************************************************************/

int isPresent (char *mainString, char *subString){
    
    // if subString is present in mainString then return 1 else 0
    if(strstr(mainString, subString) == NULL) 
        return 0;
    else
        return 1;
}
