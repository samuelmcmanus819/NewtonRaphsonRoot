#include "list_model.h"
#include <stdio.h>
/*
 * Name: PrintList
 * Purpose: Takes in a pointer to a list's head node and
 *          prints the contents of the list
 * Author: Samuel McManus
 * @param head: The head node of the list being passed in
 * Used By: main
 * Date: August 12, 2020
 */
void PrintList(struct Node** head)
{
	//Set pt to the head node
	Node *pt = *head;
	pt = pt->previous;
	while(pt->key != 0){
		if(pt->data != 0)
			printf(" %dx^%d + ", pt->data, pt->key);
		pt = pt->previous;
	}
	printf("%d\n", pt->data);
}
void PrintListForward(struct Node** head)
{
	Node *pt = *head;
	printf("%d", pt->data);
	pt = pt->next;
	while(pt != NULL){
		printf(" + %dx^%d ", pt->data, pt->key);
		pt = pt->next;
	}
	printf("\n");
}
void insert_first_node(struct Node** head, int key, int data)
{
	Node *node = (struct Node*)malloc(sizeof(struct Node));
	node->key = key;
	node->data = data;
	node->next = node;
	node->previous = node;
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
void InsertTail(Node** pt, int key, int data)
{
	struct Node *node = (struct Node*)malloc(sizeof(struct Node));
	node->key = key;
	node->data = data;
	node->previous = (*pt)->previous;
	(*pt)->previous->next = node;
	node->next = *pt;
	(*pt)->previous = node;
}
void delete_list(Node *node)
{
	node->previous->next = NULL;
	Node *pt;
	while(node != NULL){
		pt = node;
		node = node->next;
		free(pt);
	}

}
