/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"

void test1() {
	int ret;
	int values[] = {1,3,5,7,9,23};
	struct node* llist = CreateList(values,6);
	PrintList(llist);

	llist = InsertInFront(llist, 53);
    //PrintList(llist);
	llist = InsertAtEnd(llist, 78);
    //PrintList(llist);
	llist = InsertAtN(llist, 44, 3);
    //PrintList(llist);
	llist = DeleteNode(llist, 5);
	PrintList(llist); // 53 1 3 44 7 9 23 78

	ret = LinkedListLength(llist);
	assert(ret == 8);
}


/* Test for length function */
void test2() {
	int values[] = {1,3,5,7,9,23};
	struct node* llist = CreateList(values,6);

	int ret = LinkedListLength(llist);
	assert(ret == 6);

	ret = LinkedListLength(NULL);
	assert(ret == 0);

	printf("Test 3 passed\n");
}

/* Test for insert functions */
void test3() {
	struct node* head = NULL;
	head = InsertInFront(head, 2);
	head = InsertInFront(head, 4);
	head = InsertInFront(head, 6);
	PrintList(head); // 6 4 2

	head = NULL;
	head = InsertAtEnd(head, 2);
	head = InsertAtEnd(head, 4);
	head = InsertAtEnd(head, 6);
	PrintList(head); // 2 4 6

	head = NULL;
	head = InsertAtN(head, 2, 5); //should print error
	head = InsertAtN(head, 3, 0);
	head = InsertAtN(head, 4, 2); //should print error
	head = InsertAtN(head, 5, 1);
	head = InsertAtN(head, 6, 1);
	head = InsertAtN(head, 7, 3);
	head = InsertAtN(head, 8, 0);
	PrintList(head); // 8 3 6 5 7
}

/* Test for delete function */
void test4() {
	int values[] = {1,3,5,7,9,23};
	struct node* llist = CreateList(values,6);

	llist = DeleteNode(llist, -1); //should print error
	llist = DeleteNode(llist, 0); //should print error
	llist = DeleteNode(llist, 9); //should print error
	llist = DeleteNode(llist, 1);
	llist = DeleteNode(llist, 5);
	llist = DeleteNode(llist, 3);
	PrintList(llist); // 3 5 9

	DeleteNode(NULL,0); //should print error
}

int main(int argc, char **argv) {
	assert(argc==2);
	char *ch = argv[1];
	int choice = atoi(ch);

	printf("Executing test case %d\n", choice);
	switch(choice) {
	case 1: test1();
		break;
	case 2: test2();
		break;
	case 3: test3();
		break;
	case 4: test4();
		break;
	default: printf("Testcase not defined\n");
	}

    return 0;
}


