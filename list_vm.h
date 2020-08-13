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
/*
 * Name: insert_first_node
 * Purpose: Inserts the first node into a new list
 * Author: Samuel McManus
 * @param head: A null pointer used to mark the head node
 * @param key: The exponent of the node
 * @param data: The coefficient of the data
 * Used By: Main, Newton
 * Date: August 13, 2020
 */ 
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
/*
 * Name: delete_list
 * Purpose: Deletes a list after we're done using it
 * Author: Samuel McManus
 * @param node: the head node of our list
 * Used By: Newton, main
 * Date: August 13, 2020
 */ 
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
