/*
 * =====================================================================================
 *
 *       Filename:  ex1.c
 *
 *    Description:  sort cards using queue
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 

typedef struct Card_s
{
    char c; /* 'A','B','C','D'  */
    int n;  /* digit from 1 to 9 */
}Card;

typedef struct Queue_s
{
    Card card[MAX + 10];
    int count;
}Queue;

void print_card(Card *c)
{
    printf("%c%d", c->c, c->n);
}
void print_cards(Card *c, int n)
{
    int i;
    int is_first = 1;
    for(i = 0; i < n; i++)
    {
        if(is_first)
            is_first = 0;
        else
            printf(" ");
        print_card(&c[i]);
    }
    printf("\n");
}

void sort_cards_byType(Card *c, int n)
{
    int i,j;
    for(i = 0; i < n; i++) 
        for(j = n-1; j >= 1; j--)
        {
            if(c[j].c > c[j-1].c)
            {
                Card temp = c[j];
                c[j] = c[j-1];
                c[j-1] = temp;
            }
        }
}

void sort_cards_byNum(Card *c, int n)
{
    int i,j;
    for(i = 0; i < n; i++) 
        for(j = n-1; j >= 1; j--)
        {
            if(c[j].n < c[j-1].n)
            {
                Card temp = c[j];
                c[j] = c[j-1];
                c[j-1] = temp;
            }
        }
}
    
int print_queue_without_newline(Queue *q)
{
    int i;
    int is_first = 1;
    if(q->count == 0)
        return 0;
    for(i = 0; i < q->count; i++)
    {
        if(is_first)
            is_first = 0;
        else
            printf(" ");
        print_card(&q->card[i]);
    }
 
    return 1;
}
void print_queue(Queue *q)
{
    print_queue_without_newline(q);
    printf("\n");
}
void print_queues(Queue *q, int start, int n)
{
    int  i;
    for(i = start; i < n+start; i++)
    {
        if(i< 10)
            printf("Queue%d:", i);
        else
            printf("Queue%c:", i-10+'A');
        print_queue(&q[i]);
    }
}

Queue q[15] = {0};
int main(void)
{
    int i,j,k,n;
    Card *card;

    scanf("%d", &n);
    card = (Card *)malloc(sizeof(Card) * (n+20));
    if(card == NULL)
        return -1;
    for(i = 0; i < n; i++)
    {
        do
        {
            scanf("%c", &card[i].c);
        }while(card[i].c > 'D' || card[i].c < 'A');
        scanf("%d", &card[i].n);
    }
    
    for(i = 0; i < n; i++)
    {
        int curNum= card[i].n;
        int curIndex = q[curNum].count;
        q[curNum].card[curIndex] = card[i];
        q[curNum].count+= 1;
    }
    print_queues(q, 1, 9);
    k = 0;
    for(i = 1; i <= 9; i++)
    {
        for(j = 0; j < q[i].count; j++)
            card[k++] = q[i].card[j];
    }
    for(i = 0; i < n; i++)
    {
        int curNum= card[i].c - 'A' +10; 
        int curIndex = q[curNum].count;
        q[curNum].card[curIndex] = card[i];
        q[curNum].count+= 1;
    }
    print_queues(q, 10, 4);
    k = 0;
    for(i = 10; i <= 13; i++)
    {
        for(j = 0; j < q[i].count; j++)
            card[k++] = q[i].card[j];
    }
    print_cards(card, n);
    for(i = 0; i < n-1; i++)
    {
        if(card[i].c < card[i+1].c)
            continue;
        if(card[i].c == card[i+1].c && card[i].n <= card[i+1].n)
            continue;
        else
            return 1;
    }

    free(card);
    return 0;
}
