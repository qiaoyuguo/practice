/*
 * node.c
 */

/* node is the element of linked list */
struct node {
	int data; //data contained in each node
	struct node* next; //pointer to next node in the list
};


/* This function allocates space for a new node and
 * returns the pointer to this new node.
 * This function should be called while creating a new node
 * */
struct node* CreateNode();


/* Function: Compute the length of linked list
 * Input:
 *    head: pointer to the start of linked list
 * Return: length of the linked list
 */
int LinkedListLength(struct node* head);


/* Function: Insert a new node in front of linked list
 * Input:
 *    head: pointer to the start of linked list
 *    value: data field for new node
 * Return: new linked list after inserting the node
 * */
struct node* InsertInFront(struct node* head, int value);


/* Function: Insert a new node at the end of linked list
 * Input:
 *    head: pointer to the start of linked list
 *    value: data field for new node
 * Return: new linked list after inserting the node
 * */
struct node* InsertAtEnd(struct node* head, int value);


/* Function: Insert a new node with given data
 * Input:
 *    head: pointer to the start of linked list
 *    value: value to be stored in data field of new node
 *    N: position of node AFTER which new node should be inserted
 *       If N=0, then new node should be inserted in front (Special case) 
 */
struct node* InsertAtN(struct node* head, int value, int N);


/* Function: to create a new linked list
 * Input:
 *    values[]: array of integers containing values for data fields
 *    len: length of values[] array
 * Return: New linked list where each node data contains
 *         a value from values[] array
 * */
struct node* CreateList(int values[], int len);


/* Function: Deletes a node at a given position from linked list
 * Input:
 *    head: pointer to the start of linked list
 *    pos: position of node to delete from linked list (pos is in [1,length])
 * Return: new linked list after deleting the node
 * Error: If node to be deleted does not exist, output:
 *    ERROR: Node does not exist
 */
struct node* DeleteNode(struct node* head, int pos);


/* Print the linked list with head pointing to the first node
 * For an empty linked list, print NULL
 * */
void PrintList(struct node* head);

