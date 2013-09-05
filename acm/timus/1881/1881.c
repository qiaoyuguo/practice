/*
 * =====================================================================================
 *
 *       Filename:  1881.c
 *
 *    Description:  Long problem statement
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

int ceil_quot(int dividend, int divider)
{
    int result = dividend/divider;
    if(dividend % divider != 0)
        ++result;

    return result;
}

int main(void)
{
    int h, w ,n,i;
    int line_count = 0;
    char *buf;
    int cur_line_len = 0;
    int word_len;

    scanf("%d %d %d", &h, &w, &n);
    buf = malloc((MAX_LEN+3) * sizeof(char));
    if(buf == NULL)
        return -1;
    fgets(buf, MAX_LEN+3, stdin);
    for(i = 0; i < n; i++)
    {
        memset(buf, 0, MAX_LEN+3);
        fgets(buf, MAX_LEN+3, stdin);
        word_len = strlen(buf) - 1;
        if(word_len + cur_line_len + 1 < w)
        {
            if(cur_line_len > 0)
                ++cur_line_len;
            cur_line_len += word_len;
        }
        else if(word_len + cur_line_len + 1 == w)
        {
            cur_line_len = 0;
            ++line_count;
        }
        else if(word_len < w)
        {
            cur_line_len = word_len;
            ++line_count;
        }
        else if(word_len == w)
        {
            if(cur_line_len == 0)
                line_count += 1;
            else
            {
                cur_line_len = 0;
                line_count += 2;
            }
        }
        else
        {
            cur_line_len = word_len/w;
            line_count += ceil_quot(word_len, w);
        }
        printf("%s line_count=%d\n", buf,  line_count);
    }
    if(cur_line_len== 0)
    {
        //--line_count;
    }
    if(line_count == 0)
        ++line_count;
    printf("%d\n", ceil_quot(line_count, h));

    free(buf);

    return 0;
}
