/*
 * =====================================================================================
 *
 *       Filename:  Median.c
 *
 *    Description:  Median maintainence implementation
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>

#define MAX 1000000

int buf[MAX];

// return total numbers in the file
int read_file_to_buf(char *file_name)
{
    FILE *fp;
    char tmp_buf[20] = {0};
    if(file_name == NULL)
        return 0;
    fp = fopen(file_name, "r") ;
    if(fp == NULL)
        return 0;

    int count = 0;
    while(fgets(tmp_buf, 20-1, fp))
    {
        if(tmp_buf[strlen(tmp_buf) - 1] == '\n')
            tmp_buf[strlen(tmp_buf) - 1] = '\0';
        if(tmp_buf[strlen(tmp_buf) - 1] == '\r')
            tmp_buf[strlen(tmp_buf) - 1] = '\0';
        buf[count++] = atoi(tmp_buf);
        memset(tmp_buf, 0, sizeof(tmp_buf));
    }

    fclose(fp);

    return count;
}

int median_maintenence(int *arr, int n)
{
    int i;
    int sum = 0;
    for(i = 0; i < n; i++)
    {
        int j;
        int cur_elem = arr[i];
        for(j = i-1; j >= 0 && arr[j] > cur_elem; j--)
            arr[j+1] = arr[j];
        arr[j+1] = cur_elem;

        sum += arr[i/2];
        printf("%d ", arr[i/2]);

        sum %= 10000;
        
    }

    return sum;
}
void print_arr(int *a, int len)
{
    int i;
    for(i = 0; i < len; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    int n = read_file_to_buf("Median.txt");
    //print_arr(buf, 10);

    int sum = median_maintenence(buf, n);
    printf("sum = %d\n", sum);

    return 0;
}
