/*
 * =====================================================================================
 *
 *       Filename:  ex1.c
 *
 *    Description:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct Node{
	int coefficient;
	int exponent;
	struct Node *next;
};

struct Node *create_node(int coff, int exp)
{
	struct  Node *cur_node = NULL;
	cur_node = (struct Node*)malloc(sizeof(struct Node));
	if(cur_node == NULL)
		return NULL;
	cur_node->coefficient = coff;
	cur_node->exponent = exp;
	cur_node->next = NULL;

	return cur_node;
}

int insert_node(struct Node **head, int coff, int exp)
{
	struct Node *cur_node;
	struct Node *prev_node;
	struct Node *trav_node;

	if(head == NULL)
		return 0;
	cur_node = create_node(coff, exp);
	if(cur_node == NULL)
		return 0;

	if(*head == NULL)
		*head =cur_node;
	else
	{
		prev_node = NULL;
		trav_node = *head;
		while(trav_node != NULL &&  trav_node->exponent > exp)
		{
			prev_node = trav_node;
			trav_node = trav_node->next;
		}
		if(trav_node != NULL && trav_node->exponent == exp)
		{
			trav_node->coefficient += coff;
			/*  
			if(trav_node->coefficient == 0)
                        {
                            if(prev_node != NULL)
                                prev_node->next = trav_node->next;
                            free(trav_node);
                        }*/
			free(cur_node);
			return 1;
		}
		if(prev_node == NULL)
		{
			cur_node->next = *head;
			*head = cur_node;
		}
		else
		{
			cur_node->next = prev_node->next;
			prev_node->next = cur_node;
		}
	}

	return 1;
}
int add_poly(struct Node **p1, struct Node *p2)
{
	struct Node *head;
	struct Node *prev_node;
	if(p2 == NULL)
		return 1;
	if(*p1 == NULL)
	{
		*p1 = p2;
		return 1;
	}

	prev_node = NULL;
	head = *p1;
	while(head != NULL && p2 != NULL)
	{

		if(head->exponent > p2->exponent)
		{
			prev_node = head;
			head = head->next;
		}
		else if(head->exponent == p2->exponent)
		{
			struct Node *tmpNode = p2;
			head->coefficient += p2->coefficient;
			prev_node = head;
			head = head->next;
			p2 = p2->next;
			free(tmpNode);
		}
		else
		{
			struct Node *tmpNode = p2;
			p2 = p2->next;
			if(prev_node == NULL)
			{
				tmpNode->next = head;
				//prev_node = head;
				prev_node = tmpNode;;
				*p1 = tmpNode;;
			}
			else
			{
				tmpNode->next = prev_node->next;
				prev_node->next = tmpNode;
				prev_node = tmpNode;
			}
		}
	}
	while(head != NULL)
        {
            prev_node->next = head;
            prev_node = head;
            head = head->next;
        }

        while(p2 != NULL)
        {
            prev_node->next = p2;
            prev_node = p2;
            p2 = p2->next;
        }

	return 1;
}
/*  remove useless node */
int remove_useless(struct  Node **head)
{
    struct Node *prev_node = NULL;
    struct Node *trav_node;
    if(head == NULL || *head == NULL) 
       return 1;
    trav_node = *head;
    while(trav_node != NULL)
    {
        if(trav_node->coefficient == 0)
        {
            struct Node *tmp_node = trav_node;
            trav_node = trav_node->next;
            if(prev_node != NULL)
                prev_node->next = trav_node;
            else
                *head = trav_node;
            free(tmp_node);
        }
        else
        {
            prev_node = trav_node;
            trav_node = trav_node->next;
        }
    }

}
int print_poly(struct Node *head)
{
	int first = 1;
	if(head == NULL)
		return 1;
	while(head != NULL)
	{
		
		if(first)
		{
			first = 0;
		}
		else
		{
			printf(" ");
		}
		printf("[ %d %d ]", head->coefficient, head->exponent);
		head = head->next;
	}
	printf("\n");

	return 1;
}

int delete_poly(struct Node **head)
{
	struct Node *trav_node;
	if(head == NULL || *head == NULL)
		return 1;
	trav_node = *head;

	while(trav_node != NULL)
	{
		struct Node *tmpNode = trav_node;
		trav_node = trav_node->next;
		free(tmpNode);
	}
	*head = NULL;
	return 1;
}
int main(void)
{
#if 0
	struct Node *head1 = NULL, *head2 = NULL;

	insert_node(&head1, 2, 3);
	insert_node(&head1, 4,5);
	insert_node(&head1, 6,8);
	print_poly(head1);

	insert_node(&head2, 1,5);
	insert_node(&head2, 2,7);
	insert_node(&head2, 5,8);
	print_poly(head2);

	add_poly(&head1, head2);
	print_poly(head1);
#endif
	int n;
	int cur_coff, cur_exp;
	scanf("%d", &n);
	while(n-- > 0)
	{
		struct Node *head1 = NULL, *head2 = NULL;
		while(1)
		{
			scanf("%d %d", &cur_coff, &cur_exp);
			if(cur_exp < 0)
				break;
			insert_node(&head1, cur_coff, cur_exp);
		}

		while(1)
		{
			scanf("%d %d", &cur_coff, &cur_exp);
			if(cur_exp < 0)
				break;
			insert_node(&head2, cur_coff, cur_exp);
		}

                //print_poly(head1);print_poly(head2);
		add_poly(&head1, head2);
                //print_poly(head1);print_poly(head2);
		remove_useless(&head1);
		print_poly(head1);
		delete_poly(&head1);
	}

	return 0;
}
