#include <stdlib.h>
#include "list_vm.h"
#include "function_model.h"
#include <math.h>
#include <stdio.h>
#define ACCEPTABLE_RANGE .0001
/* 
 * Name: evaluate_functioin
 * Purpose: Solves a function f(x)
 * Author: Samuel McManus
 * @param x: The value of x in f(x)
 * @param head: The head node of a list of coefficients 
 * 		and exponents in the function
 * Used By: newton
 * Date: August 13, 2020
 */ 
double evaluate_function(long double x, Node *head)
{
	double solution = 0;
	double temp = 0;
	//Go through the list setting x to x^key * data
	//and adding it to solution
	while(head != NULL){
		temp = 0;
		temp = pow(x, (double)head->key);
		temp = temp * (double)head->data;
		solution = solution + temp;
		head = head->next;
	}
	return solution;
}
/*
 * Name: get_derivative
 * Purpose: Gets the derivative of a function
 * Author: Samuel McManus
 * @param f_head: The head node of a list of coefficients
 * 		  and exponents in the user-entered function
 * @param fp_head: The head node of a list of coefficients
 * 		  and exponents for f' of the user-entered function
 * Uses: InsertTail, PrintList
 * Used By: newton
 * Date: August 13, 2020
 */
void get_derivative(Node** f_head, Node** fp_head)
{
	//Allocates space for the function list's head node
	//and the f'() list's head node
	Node *f_pt = *f_head;
	Node *f_prime_pt = *fp_head;
	//The function pointer is set to the node prior to the head node
	//To mimic x^0 being discarded
	f_pt = *f_head;
	f_pt = f_pt->next;
	f_prime_pt = *fp_head;
	//The f'() pointer is set to the f'() head node
	//Take the derivative of every other item in the f() list
	if(f_pt != NULL){
		InsertTail(fp_head, (f_pt->key - 1), (f_pt->key * f_pt->data));
		f_pt = f_pt->next;
	}
	else{
		InsertTail(fp_head, 0, 0);
	}
	while(f_pt != NULL){
		InsertTail(fp_head, (f_pt->key - 1), (f_pt->key * f_pt->data));
		f_pt = f_pt->next;
	}
	PrintList(fp_head);
}
/*
 * Name: get_next_guess
 * Purpose: To move the value of x closer to the root of the function
 * Author: Samuel McManus
 * @param func: Holds x, f(x), and f'(x)
 * @param multiplicity: The multiplicity of the function
 * @return (func->x - adjustment_amount): The previous x approximation  minus 
 * 					  the calculated amount to move
 * 					  x
 * Used By: newton
 * Date: August 13, 2020
 */ 
double get_next_guess(Function *func, long double multiplicity)
{
	long double adjustment_amount;
	adjustment_amount = func->fx / func->fpx;
	adjustment_amount = adjustment_amount * multiplicity;
	return (func->x - adjustment_amount);
}
/*
 * Name: newton
 * Purpose: To find a local root in a function entered by the user
 * Author: Samuel McManus
 * @param x_guess: The user's initial guess for the value of x
 * @param f_head: The head node of the user-entered function
 * Uses: get_next_guess, get_derivative, evaluate_function,
 * 	 InsertHead
 */ 
void newton(long double x_guess, Node** f_head)
{
	int cycle_count = 0;
	long double first_guess;
	long double next_guess;
	//A list of f'() derivatives and coefficients
	Node *fp_head = (Node*)malloc(sizeof(Node));
	get_derivative(f_head, &fp_head);
	PrintList(&fp_head);
	long double multiplicity = 1;
	//A function variable holding values related to the user's current
	//x-guess
	Function *func = (Function*)malloc(sizeof(Function));
	func->x = x_guess;
	//A function variable holding values related to the user's previous
	//x-guess
	Function *old_func = (Function*)malloc(sizeof(Function));
	first_guess = x_guess;
	//Loops through 35 times trying to get closer values such that
	//f(x) = 0
	for(int i = 0; i < 35; i++){
		//Sets the previous value of x
		old_func->x = func->x;
		//Sets the value of f(x) for the current function
		func->fx = evaluate_function(func->x, *f_head);
		//If f(x) is within an acceptable range of zero, exit
		if(fabs(func->fx) < ACCEPTABLE_RANGE)
			break;
		//Checks the slope of the function with input values to see
		//if the next guess will be moving away from the local root
		func->fpx = evaluate_function(func->x, fp_head);
		if((fabs(evaluate_function((func->x - .5), *f_head) > fabs(func->fx))) && (fabs(evaluate_function((func->x + .5), *f_head) > fabs(func->fx)))){
			//If we're moving away from the local root in the positive
			//direction, then try to move back and readjust
			if((0 > func->fpx) && (func->fpx > -.1) && (fabs(func->fx) > .1)){
				func->x = func->x - .5;
				func->fx = evaluate_function(func->x, *f_head);
				if(fabs(func->fx) < ACCEPTABLE_RANGE) 
					break; 
				func->fpx = evaluate_function(func->x, fp_head);
				multiplicity = 2.0;
			}
			//If we're moving away from the local root in the negative
			//direction, then try to move forward and readjust
			else if((0.1 > func->fpx) && (func->fpx >= 0) && (fabs(func->fx) > 0.1))
			{
				func->x = func->x + .5;
				func->fx = evaluate_function(func->x, *f_head);
				if(fabs(func->fx) < ACCEPTABLE_RANGE)
					break;
				func->fpx = evaluate_function(func->x, fp_head);
				multiplicity = 2.0;
			}
		}
	       	//If the slope of the function is plateuing and we're higher on
		//the y-axis than .1, we might be stuck in a loop and should try to
		//move the guess to the other side of the root 	
		else{
		       	if((0 > func->fpx) && (func->fpx > -.1) && (fabs(func->fx) > .1))
			{
				func->x = first_guess;
				while(func->fpx <= 0){
					func->x = func->x - .5;
					func->fx = evaluate_function(func->x, *f_head);
					if(fabs(func->fx < ACCEPTABLE_RANGE))
						break;
					func->fpx = evaluate_function(func->x, fp_head);
				}
			}
			else if((0.1 > func->fpx) && (func->fpx >= 0) && (fabs(func->fx) > .1)){
				func->x = first_guess;
				while(func->fpx >= 0){
					func->x = func->x + .5;
					func->fx = evaluate_function(func->x, *f_head);
					if(fabs(func->fx < ACCEPTABLE_RANGE))
						break;
					func->fpx = evaluate_function(func->x, fp_head);
				}
			}
		}
		
		//Finds next guess incorporating multiplicity.
		next_guess = get_next_guess(func, multiplicity);
		if(next_guess == old_func->x)
			cycle_count++;
		//If the program is in a cycle repeating the same guesses in a 
		//mirrored fashion, tell them to try the bisectional method
		//instead
		if(cycle_count > 3){
			if(evaluate_function(first_guess, fp_head) > 0){
				printf("%d is the lower bound of your function\n", first_guess);
			}
			else{
				printf("%d is the upper bound of your function\n", first_guess);
			}
			printf("Try the bisectional method\n");
			exit(0);
		}
		func->x = next_guess;
		if(i == 34){
			printf("Too many guesses. Your answer will likely have an intolerable error");
			exit(0);
		}	
	}

	printf("Your root is at: %Lf\n", func->x);
	free(fp_head);
	free(func);
	free(old_func);
}
