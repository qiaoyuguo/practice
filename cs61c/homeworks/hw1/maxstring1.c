/* 
 * CS61C Summer 2013
 * Name:
 * Login:
 */
/* for problem 4 part 1 */
/* compile: gcc -o maxstring1 -std=c99 maxstring1.c */

#include <stdio.h>

int charcount(char* str, char c);
char* maxstring(char* str_arr[], int num, char c);

/*
 * Modify this in part B to accept command-line arguments.
 */
int main(int argc, char* argv[]) {
    char* strings[] = {"hello world!", "", "welcome to cs61c", "good day"};
    printf("If the char is 'd', maxstring() should return 'good day'. Result:\n%s\n", maxstring(strings, 4, 'd'));
    printf("If the char is ' ', maxstring() should return 'welcome to cs61c'. Result:\n%s\n", maxstring(strings, 4, ' '));
    printf("If the char is 'b', maxstring() should return ''. Result:\n%s\n", maxstring(strings, 4, 'b'));
    printf("If the char is 'o', maxstring() should return 'hello world!'. Result:\n%s\n", maxstring(strings, 4, 'o'));
    return 0;
}

/*
 * Counts the number of times a given character is present in a string.
 */
int charcount(char* str, char c) {
    int count = 0;
    while(*str != '\0')
    {
        if(*str == c)
            ++count;
        str++;
    }

    return count;
}

/*
 * Takes an array of strings and returns the string with the maximum number of occurences 
 * of a given character. In case of a tie, the first string is returned. If the array is 
 * empty or if the character does not exist in any of the strings, an empty string is returned.
 */
char* maxstring(char* str_arr[], int num, char c) { 
    int i;

    int max = 0;
    int index = -1;

    if(str_arr == NULL)
        return "";
    for(i = 0; i < num; i++)
    {
        int cur_count = charcount(str_arr[i], c);
        if(cur_count > max)
        {
            max = cur_count;
            index = i;
        }
    }

    if(index == -1)
        return "";
    return str_arr[index];
}

