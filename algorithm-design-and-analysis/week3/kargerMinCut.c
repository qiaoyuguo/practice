/*
 * =====================================================================================
 *
 *       Filename:  kargeMinCut.c
 *
 *    Description:  implementation of karge min cut
 *
 * =====================================================================================
 */
/* http://upload.wikimedia.org/wikipedia/commons/thumb/e/e7/Single_run_of_Karger%E2%80%99s_Mincut_algorithm.svg/2000px-Single_run_of_Karger%E2%80%99s_Mincut_algorithm.svg.png */
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
    int line_no; //line count between two vex
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
int get_vex_pair(adj_lst *lst, int *out_fst_num, int *out_sec_num);
int one_round_min_cut(adj_lst *lst, int pair_one, int pair_two);

int main(void)
{
    adj_lst input_lst, output_lst;    
    memset(&input_lst, 0, sizeof(adj_lst));
    print_adj_lst(&input_lst);
    read_file_and_create_graph(INPUT_FILE, &input_lst);
    print_adj_lst(&input_lst);

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
#if 0
#endif
    //rounds = lst->vex_num * lst->vex_num;
    rounds = 1;
    for(i = 0; i < rounds; i++)
    {
        ret_val = copy_adj_lst(lst, &cur_lst);
        if(ret_val != OK)
            return ERROR;
        int cur_cut_num = min_cut(&cur_lst);
        printf("current cut num is %d\n", cur_cut_num);
        if(cur_cut_num < min)
            min = cur_cut_num;
        free_adj_lst(&cur_lst);
    }
    
    printf("min cut num is %d\n", min);
    return OK;
}

int min_cut(adj_lst *lst)
{
    int i;
    int ret;
    int pair_one, pair_two;
    int vex_num;
    int count;
    node *cur_node;

    if(lst == NULL || lst->lst == NULL || lst->vex_num == 0)
        return 0;

    srandom(time(NULL));
    vex_num = lst->vex_num;

    for(i = 0; i < 1; i++)
    //for(i = 0; i < vex_num -1; i++)
    {
#if 0
        ret = get_vex_pair(lst, &pair_one, &pair_two);
        if(ret != OK)
            return ERROR;
#endif
#if 1
        pair_one = 1;
        pair_two = 3;
#endif
        one_round_min_cut(lst, pair_one, pair_two);
        printf("pair:%d %d\n", pair_one, pair_two);
#if 1 
        print_adj_lst(lst);
#endif
    }
    // also need to free  space allocated for pair two, now not implemented
    cur_node = lst->lst[pair_one].next->next;
    count = 0;
    while(cur_node != NULL)
    {
        ++count;
        cur_node = cur_node->next;
    }

    return count;
}

int one_round_min_cut(adj_lst *lst, int pair_one, int pair_two)
{
    int vex_num = lst->vex_num;
    int i;
    lst->lst[pair_two].vex = 0;

    for(i = 0; i < vex_num; i++)
    {
        if(lst->lst[i].vex != 0)
        {
            int has_pair_two = 0;
            int has_pair_one = 0;
            node *cur_node = lst->lst[i].next;
            node *prev_node;
            cur_node = cur_node->next;
            // search list to find if has pair_one or pair_two;
            while(cur_node != NULL)
            {
                if(cur_node->vex == pair_two + 1)
                    has_pair_two = 1;
                if(cur_node->vex == pair_one + 1)
                    has_pair_one = 1;
                cur_node = cur_node->next;
            }
            //only when has pair_two we need modify the list
            if(has_pair_two)
            {
                prev_node = lst->lst[i].next;
                cur_node = prev_node->next;
                while(cur_node != NULL)
                {
                    if(cur_node->vex == pair_two + 1)
                    {
                        if(has_pair_one || i == pair_one) // if has pair_oneor it is the list corresponding to pair one  then delete node whose value is  pair_two  
                        {
                            prev_node->next = cur_node->next;
                            free(cur_node);
                            cur_node = NULL;
                            --lst->lst[i].vex;
                        }
                        else // if has no pair_one then modify corresponding vex to pair_one
                            cur_node->vex = pair_one + 1;
                        break;
                    }
                    prev_node = cur_node;
                    cur_node = cur_node->next;
                }
            }


        }
    }
    return OK; 
}

//return two pair vertex num 
int get_vex_pair(adj_lst *lst, int *out_fst_num, int *out_sec_num)
{
    int i;
    int rand;
    int count;
    int vex_num;
    int *cur_buf = NULL;
    int fst_vex;
    int sec_vex;
    int out_degree;
    node *node;
    if(lst == NULL || lst->lst == NULL || out_fst_num == NULL
      || out_sec_num == NULL)
        return -1;

    vex_num = lst->vex_num;
    for(count = 0,i = 0; i < vex_num; i++)
    {
        if(lst->lst[i].vex != 0)
            ++count;
    }
    cur_buf = malloc(count * sizeof(int));
    if(cur_buf == NULL)
        return ERROR;

    for(count = 0,i = 0; i < vex_num; i++)
    {
        if(lst->lst[i].vex != 0)
            cur_buf[count++] = i;
    }
    do{
        fst_vex = random() % count;
        *out_fst_num = cur_buf[fst_vex];
    }while(lst->lst[*out_fst_num].vex == 0);
    //printf("fst_vex:%d, fst_num:%d\n",fst_vex ,*out_fst_num);
    out_degree = lst->lst[*out_fst_num].vex - 1;
    sec_vex = random() % out_degree;
    node = lst->lst[*out_fst_num].next->next;
    printf("\n for vex %d , seach %d index, node->vex=%d:", *out_fst_num, sec_vex, node->vex);
    for(count = 0; count < sec_vex-1 && node != NULL; count++)
    {
        printf(" %d", node->vex);
        node = node->next;
    }
    printf("\n");
    *out_sec_num = node->vex - 1;

    if(lst->lst[*out_fst_num].vex == 0 )//|| lst->lst[*out_sec_num].vex == 0)
    {
        printf("get_vex_pair return error pair\n");
        return ERROR;
    }
    
    return OK; 
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
    out->lst = (node *)malloc(vex_num * sizeof(node ));
    if(out->lst == NULL)
    {
        fclose(fp);
        return ERROR;
    }
    memset(out->lst, 0, vex_num * sizeof(node));

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
            ++cur_node->line_no;
            cur_node->next = NULL;
            prev_node->next = cur_node;
            prev_node = prev_node->next;
            ++count;
            tmp_str = strtok(NULL, delim_str);
        }
        out->lst[i].vex = count;
        out->lst[i].line_no = count;
    }
    fclose(fp);

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
        printf("vex num: %d,line_no:%d ", cur_node->vex,cur_node->line_no);
        while(cur_node->next != NULL)
        {
            cur_node = cur_node->next;
            if(first)
            {
                printf("vex %d, line_no:%d \n", cur_node->vex, cur_node->line_no);
                first = 0;
            }
            printf(" %d,%d", cur_node->vex, cur_node->line_no);
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
            tmp_node ->line_no = input_node->line_no;
            tmp_node -> next = NULL;

            output_node->next = tmp_node;
            output_node = output_node->next;
        }
    }

    return OK;
}
