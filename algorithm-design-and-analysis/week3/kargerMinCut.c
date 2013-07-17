/*
 * =====================================================================================
 *
 *       Filename:  kargeMinCut.c
 *
 *    Description:  implementation of karge min cut
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define OK 1
#define ERROR -1
#define MAX 3048
#define ARR_SIZE(a) (sizeof(a)/sizeof(a[0]))
//#define INPUT_FILE  "8-loop.txt"
#define INPUT_FILE  "test-8v.txt"

char buf[MAX + 1] = {0};

typedef struct node_s {
    int vex;
    struct node_s *next;
}node;

typedef struct adj_lst_s {
    int vex_num; //vertext number
    node *lst; // adjacent lst
}adj_lst;

int  read_file_and_create_graph(char *file_name, adj_lst *out);
void print_adj_lst(adj_lst *input);
void free_adj_lst(adj_lst *input);
int copy_adj_lst(adj_lst *input, adj_lst *output);
int core_handle(adj_lst *lst);
int min_cut(adj_lst *lst);

int main(void)
{
    adj_lst input_lst, output_lst;    
    memset(&input_lst, 0, sizeof(adj_lst));
    print_adj_lst(&input_lst);
    read_file_and_create_graph(INPUT_FILE, &input_lst);
    //print_adj_lst(&input_lst);
    //copy_adj_lst(&input_lst, &output_lst);
    //print_adj_lst(&output_lst);
    core_handle(&input_lst);
    free_adj_lst(&input_lst);

    return 0;
}

int core_handle(adj_lst *lst)
{
    int i;
    int ret_val = OK;
    int rounds = 0;
    int min = INT_MAX;

    adj_lst cur_lst;
    if(lst == NULL || lst->lst == NULL || lst->vex_num == 0)
        return ERROR;
    srandom(time(NULL));
    ret_val = copy_adj_lst(lst, &cur_lst);
    if(ret_val != OK)
        return ERROR;

    rounds = cur_lst.vex_num * cur_lst.vex_num;
    for(i = 0; i < rounds; i++)
    {
        int cur_cut_num = min_cut(&cur_lst);
        if(cur_cut_num < min)
            min = cur_cut_num;
    }

    free_adj_lst(&cur_lst);
    
    return OK;
}

int min_cut(adj_lst *lst)
{
    int pair_one, pair_two;
    int vex_num;

    if(lst == NULL || lst->lst == NULL || lst->vex_num == 0)
        return 0;

    vex_num = lst->vex_num;
    pair_one = random() % vex_num;
    pair_two = random() % vex_num;
    while(pair_two == pair_one)
        pair_two = random() % vex_num;

    printf("%d %d\n", pair_one, pair_two);
    print_adj_lst(lst);

    return 0;
}

int  read_file_and_create_graph(char *file_name, adj_lst *out)
{
    FILE *fp = NULL;
    int vex_num = 0;
    int buf_size = ARR_SIZE(buf);
    int i;

    if(out == NULL)
        return ERROR;

    fp = fopen(file_name, "r");
    if(fp == NULL)
        return ERROR;

    while(fgets(buf, MAX, fp) != NULL)
    {
        if(strcmp("\n", buf) == 0)
            continue;
        ++vex_num;
        memset(buf, 0, buf_size);
    }

    out->vex_num = vex_num;

    rewind(fp);
    out->lst = (node *)malloc(vex_num * sizeof(node));
    if(out->lst == NULL)
    {
        fclose(fp);
        return ERROR;
    }

    for(i = 0; i < vex_num; i++)
    {
        int vex_index;
        char *tmp_str = NULL;;
        char *delim_str = " \t\n";
        int count = 0;
        node *prev_node = &(out->lst[i]);

        memset(buf, 0, buf_size);
        fgets(buf, MAX, fp);
        
        tmp_str = strtok(buf, delim_str);
        while(tmp_str != NULL)
        //while(fgets(fp, "%d", &vex_index) == 1)
        {
            vex_index = atoi(tmp_str);
            node *cur_node = malloc(sizeof(node));
            if(cur_node == NULL)
            {
                fclose(fp);
                free(out->lst);
                return ERROR;
            }
            cur_node->vex = vex_index;
            cur_node->next = NULL;
            prev_node->next = cur_node;
            prev_node = prev_node->next;
            ++count;
            tmp_str = strtok(NULL, delim_str);
        }
        out->lst[i].vex = count;
    }
    return OK;
}

void print_adj_lst(adj_lst *input)
{
    int i,j;
    if(input == NULL || input->lst == NULL)
        return;
    printf("printing adj list:\n");
    for(i = 0; i < input->vex_num; i++)
    {
        int first = 1;
        node *cur_node = &(input->lst[i]);
        if(cur_node->vex == 0)
            continue;
        while(cur_node->next != NULL)
        {
            cur_node = cur_node->next;
            if(first)
            {
                printf("vex %d: \n", cur_node->vex);
                first = 0;
            }
            printf(" %d", cur_node->vex);
        }
        printf("\n");
    }
    printf("\n");
}

void free_adj_lst(adj_lst *input)
{
    int i,j;
    if(input == NULL || input->lst == NULL)
        return;
    for(i = 0; i < input->vex_num; i++)
    {
        node *cur_node = &(input->lst[i]);
        cur_node = cur_node->next;
        while(cur_node != NULL)
        {
            node *tmp_node = cur_node;
            cur_node = cur_node->next;
            free(tmp_node);
            tmp_node = NULL;
        }
    }
    free(input->lst);
    input->lst = NULL;
}

int copy_adj_lst(adj_lst *input, adj_lst *output)
{
    int i,j;
    if(input == NULL || output == NULL || input->lst == NULL
      || input->vex_num== 0)
        return ERROR;

    output->vex_num = input->vex_num;
    output->lst  = malloc(input->vex_num * sizeof(node));
    if(output->lst == NULL)
        return ERROR;
    for(i = 0; i < input->vex_num; i++)
    {
        node *input_node = &(input->lst[i]);
        node *output_node = &(output->lst[i]);
        output_node->vex = input_node->vex;
        output_node->next = NULL;
        
        while(input_node->next != NULL)
        {
            input_node = input_node->next;
            node *tmp_node = malloc(sizeof(node));
            if(tmp_node == NULL)
                return ERROR;
            tmp_node -> vex = input_node->vex;
            tmp_node -> next = NULL;

            output_node->next = tmp_node;
            output_node = output_node->next;
        }
    }

    return OK;
}
