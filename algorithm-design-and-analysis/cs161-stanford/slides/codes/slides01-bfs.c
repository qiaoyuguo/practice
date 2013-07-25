/*
 * =====================================================================================
 *
 *       Filename:  slides01-bfs.c
 *
 *    Description:  breadth first search to find distance between a vertex and all other vertex
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define INPUT "undirect-graph.txt"

typedef struct graph_s {
    int v; // number of vertexs
    int e; // number of edges
    int **adj; // adjlist
}graph, *Graph;

int ** matrix_init(int r, int c, int val)
{
    int i,j;

    int **t = malloc((r+1) * sizeof(int *));
    for(i = 1; i <= r; i++)
        t[i] = malloc((c+1) * sizeof(int));
    for(i = 1; i <= r; i++)
        for(j = 1; j <= c; j++)
            t[i][j] = val;

    return t;
}
Graph graph_init(int v)
{
    Graph G = malloc(sizeof(*G));
    G->v = v;
    G->e = 0;
    G-> adj = matrix_init(v,v,0);

    return G;
}

void graph_show(Graph G)
{
    int i,j;

    printf("%d vertices, %d edges\n", G->v, G->e);
    for(i = 1; i <= G->v; i++)
    {
        printf("%2d:", i);
        for(j = 1; j <= G->v; j++)
            if(G->adj[i][j] == 1)
                printf(" %2d",j);
        printf("\n");
    }
}

int graph_add_edge(Graph G, int v1, int v2)
{
    G->e += 1;
    G->adj[v1][v2] = 1;
    G->adj[v2][v1] = 1;

    return 0;
}

Graph read_file_create_graph(char *file)
{
    int i;
    int count = 0;
    FILE *fp;
    char buf[MAX+1];
    Graph G;

    if(file == NULL)
        return NULL;
    fp = fopen(file, "r");
    if(fp == NULL)
        return NULL;
    while(fgets(buf, MAX, fp))    
    {
        ++count;
    }
    if(count == 0)
        return NULL;
    G = graph_init(count);
    rewind(fp);

    for(i = 0; i < count; i++)
    {
        char *tmp_str = NULL;;
        char *delim_str = " \t\n";
        int cur_v;

        memset(buf, 0, MAX);
        fgets(buf, MAX , fp);
        
        tmp_str = strtok(buf, delim_str);
        if(tmp_str == NULL)
            continue;
        cur_v = atoi(tmp_str);
         
        tmp_str = strtok(NULL, delim_str);
        while(tmp_str != NULL)
        {
            int adj_v = atoi(tmp_str);
            graph_add_edge(G, cur_v, adj_v);
            tmp_str = strtok(NULL, delim_str);
        }
    }
    fclose(fp);
    
    return 0;
}

int core_handle(char *file_name)
{
    Graph G = read_file_create_graph(file_name);
    if(G != NULL)
        graph_show(G);
    else
        fprintf(stderr, "can't create graph");

    return 0;
}

int main(void)
{
    core_handle(INPUT);

    return 0;
}


