/*
 * =====================================================================================
 *
 *       Filename:  ex4.c
 *
 *    Description:  mid-order expression computation
 *    Thinking:     use algorithm in http://en.wikipedia.org/wiki/Shunting-yard_algorithm
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_higher(char a, char b)
{
    if(a == '*' && b == '-')
        return 1;
    if(a == '/' && b == '-')
        return 1;
    if(a == '*' && b == '+')
        return 1;
    if(a == '/' && b == '+')
        return 1;
    return 0;
}
int infix_to_postfix(char *infix, char *postfix, int n)
{
   int i = 0,j=0, top = 0; 
   char *a;

   a = (char*)malloc(n * sizeof(char));
   if(a == NULL)
       return -1;

   while(i < n)
   {
        if(isdigit(infix[i])) 
            printf("%c", infix[i]);
        else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*'|| infix[i] == '/')
        {
            while(top > 0 && !is_higher(infix[i], a[top-1]))
            {
                printf("%c", a[--top]);
            }
            a[top++] = infix[i];
        }
        else if(infix[i] == '(')
            a[top++] = infix[i];
        else if(infix[i] == ')')
        {
            while(top > 0 && a[top-1] != '(')
            {
                printf("%c", a[--top]);
            }
            if(top > 0 && a[top-1] == '(')
                --top;
        }
        ++i;
   }

   free(a);
}

int main(void)
{
    char buf[50]  = "3+4*2/(1-5)";
    char out[50] = {0};
    infix_to_postfix(buf, out, strlen(buf));

    return 0;
}
