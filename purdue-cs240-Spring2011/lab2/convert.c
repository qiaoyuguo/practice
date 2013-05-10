/*
 * =====================================================================================
 *
 *       Filename:  convert.c
 *
 *    Description:  convert number from one base system to another
 *
 *        Version:  1.0
 *        Created:  2013年05月10日 10时45分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qiao Yuguo (), qiaoyuguo2012@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEX_NUM 16
#define IS_BETWEEN(x, low, high) ((x) >= low && (x) <= high)

void usage(void)
{
    printf("Usage convert <number> <from_base> <to_base>\n");
}
/* convert char in base to number */
int char_to_int(const char *tbl, char c, int base)
{
    int cur_digit;
    if(c >= '0' && c <= '9')
        cur_digit = c-'0';
    else if(c >= 'a' && c <= '9')
        cur_digit = c-'a' + 10;
    else
    {
        return -1;
    }

    if(cur_digit < base)
        return cur_digit;
    else
        return -1;
}
int main(int argc, char **argv)
{
    char *num;
    int from_base;
    int to_base;
    int i;
    int len;
    unsigned long long  cur_num = 0; /* base num in decimal */
    char tbl[HEX_NUM] = {'0', '1', '2', '3', '4', '5', '6', '7',
                         '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    char to_num[100] = {0};
    int to_len = 0; /* length of the converted string */
    if(4  != argc)
    {
        usage();
        return -1;
    }

    num = argv[1];
    from_base = atoi(argv[2]);
    to_base = atoi(argv[3]);
    if(!IS_BETWEEN(from_base, 2, 35) || !IS_BETWEEN(to_base, 2, 35))
    {
        printf("The bases should lie between 2 and 35\n");
        return -1;
    }
    //if(from_base != 10)
    {
        len = strlen(num);
        if(len > 32)
        {
            printf("The entered number is longer than 32 digits, please enter a small number\n");
            return -1;
        }


        for(i = 0; i < len; i++)
        {
            int cur_digit = char_to_int(tbl, num[i], from_base);
            if(cur_digit < 0)
            {
                printf("quitting for %c with base %d\n", num[i], from_base);
                printf("the entered number is invalid for the given base\n");
                return -1;
            }
            cur_num = cur_num * from_base + cur_digit;
        }
    }

    while(cur_num != 0)
    {
       to_num[to_len++] = tbl[cur_num%to_base];
       cur_num /= to_base;
    }

    
    for(i = to_len-1; i>=0; --i)
        printf("%c", to_num[i]);
    printf("\n");

    return 0;
}
