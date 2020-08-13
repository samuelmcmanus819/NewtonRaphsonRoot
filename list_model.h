/*
 * Name: list_model
 * Purpose: To create a model of the node being used in 
 * 	    the linked list class
 * Author: Samuel McManus
 * Date: August 12, 2020
 */
struct Node;
typedef struct Node Node;
struct Node
{
	int key;
	int data;
	Node *next;
	Node *previous;
};
