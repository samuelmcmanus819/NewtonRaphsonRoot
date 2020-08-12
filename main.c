#include <stddef.h>
#include "strfmt.h"
#include <ctype.h>
#include "list_vm.h"
#include <math.h>
#include "Newton.h"
#define LIMIT 20

Node *head = NULL;
Node *pt = NULL;
/*
 * Name: main
 * Purpose: To find roots of functions using the bisectional method
 * Author: Samuel McManus
 * Date: August 12, 2019
 */
int main()
{
	int count = 0;
	char *input_holder, *x_guess_string; 
	int coefficient, x_guess, has_errors;

	//Welcome the user
	printf("Welcome to my root finding program. ");
	printf("Please enter the coefficients of your  function and I'll find its root using the bisectional method.\n");
	printf("Please note that this method will only find one root.");
	printf("You can press enter with no input when finished.\n");
	//Loop through each coefficient declaration
	while(count < LIMIT){
		input_holder = malloc(sizeof(char) * 8);
		//Get user input
		printf("Enter a coefficient for x^%d\n", count);
		fgets(input_holder, 8, stdin);
		//Strip off the new line character if applicable
		NewLineStripper(input_holder);
		//If the user enters y, exit the loop
		if(!strcmp(input_holder, "y")){
			break;
		}
	       	//Else check if the entered value is an integer
		else{
			has_errors = NumberChecker(input_holder);
			//If so, then add the input to the list
			if(has_errors == 0){
				coefficient = atoi(input_holder);
				if(head == NULL){
					InsertHead(&head, count, coefficient);
					pt = head;
				}
				else
					InsertTail(pt, count, coefficient);
			}
			//Else make them redo that coefficient
			else{
				printf("You have entered an invalid value\n");
				count--;
			}
		}
		free(input_holder);
		count ++;
	}
	//Print the user's function
	printf("Your function is: \n");
	PrintList(head);
	has_errors = 0;
	//Obtain the lower bound.
	while(1){
		has_errors = 0;
		//Has the user enter the lower bound of their string
		printf("Please enter the expected zero point for your function\n");
		x_guess_string = malloc(sizeof(char) * 8);
		fgets(x_guess_string, 8, stdin);
		//Strips the new line character and checks errors
		NewLineStripper(x_guess_string);
		has_errors = NumberChecker(x_guess_string);
		//If there are no errors, set lower bound to the input
		if(has_errors == 0){
			x_guess = atoi(x_guess_string);
			break;
		}
		//Else, make the user try again
		else{
			printf("You have entered an invalid value\n");
			free(x_guess_string);
		}
	}
	newton((double)x_guess, &head);
}
