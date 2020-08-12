#include <stdio.h>
#include <stdlib.h>
#include "list_model.h"

/*
 * Name: PrintList
 * Purpose: Takes in a pointer to a list's head node and
 *          prints the contents of the list
 * Author: Samuel McManus
 * @param head: The head node of the list being passed in
 * Used By: main
 * Date: August 12, 2020
 */
void PrintList(struct Node *head)
{
	//Set pt to the head node
	Node *pt = head;
	//Read through every node in the list
	if(pt != NULL){
		printf("%d", pt->data);
		pt = pt->next;
	}
	while(pt != NULL){
		printf(" + %dx^%d", pt->data, pt->key);
		pt = pt->next;
	}
	printf("\n");
}
/*
 * Name: InsertHead
 * Purpose: To insert an item at the head of a list
 * Author: Samuel McManus
 * @param head: The head node of the list being passed in
 * @param key: A unique identifier for each member of the list used
 * 	       to hold the exponent of x
 * @param data: The non-unique value in the list used to hold the 
 * 		coefficient of x
 * Used By: main
 * Date: August 12, 2020
 */
//Takes in the value of head and 2 integers to insert into the head node
void InsertHead(struct Node** head, int key, int data)
{
	//Create a new node and set its values
	struct Node *node = (struct Node*)malloc(sizeof(struct Node));
	node->key = key;
	node->data = data;
	//Sets the next node in the list to a pointer to head
	node->next = *head;
	//Sets head to the inserted node
	*head = node;
}
/*
 * Name: InsertTail
 * Purpose: To insert an item at the tail of a list
 * Author: Samuel McManus
 * @param pt: A pointer to an arbitrary location in the list
 * @param key: Exponent of x
 * @param data: Coefficient of x
 * Used By: main
 * Date: August 12, 2020
 */ 
void InsertTail(Node *pt, int key, int data)
{
	struct Node *node = (struct Node*)malloc(sizeof(struct Node));
	node->key = key;
	node->data = data;
	while(pt->next != NULL)
		pt = pt->next;
	pt->next = node;
}
