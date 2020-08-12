#include "function_model.h"
#include <math.h>

double evaluate_function(double x, Node** head);
double evaluate_function(double x, Node** head)
{
	double solution = 0;
	double temp = 0;
	//Allocate space for a list node
	Node *pt = (Node*)malloc(sizeof(Node));
	pt = *head;
	//Go through the list setting x to x^key * data
	//and adding it to solution
	while(pt != NULL){
		temp = 0;
		temp = pow(x, (double)pt->key);
		temp = temp * (double)pt->data;
		solution = solution + temp;
		pt = pt->next;
	}
	return solution;
}
void get_derivative(Node** f_head, Node** fp_head)
{
	Node *f_pt = (Node*)malloc(sizeof(Node));
	Node *f_prime_pt = (Node *)malloc(sizeof(Node));
	f_pt = *f_head;
	f_pt = f_pt->next;
	f_prime_pt = *fp_head;
	if(f_pt != NULL){
		InsertHead(fp_head, (f_pt->key - 1), (f_pt->key * f_pt->data));
		f_pt = f_pt->next;
	}
	else{
		InsertHead(fp_head, 0, 0);
	}
	while(f_pt != NULL){
		InsertTail(f_prime_pt, (f_pt->key - 1), (f_pt->key * f_pt->data));
		f_pt = f_pt->next;
	}
	free(f_pt);
	free(f_prime_pt);
}
double get_next_guess(Function *func, double multiplicity)
{
	double x;
	x = func->fx / func->fpx;
	x = x * multiplicity;
	return x;
}

void newton(double x_guess, Node** f_head)
{
	printf("a");
	int cycle_count;
	double first_guess;
	double next_guess;
	//A list of f'() derivatives and coefficients
	Node *fp_head = (Node*)malloc(sizeof(Node));
	get_derivative(f_head, &fp_head);
	double multiplicity;
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
		func->fx = evaluate_function(func->x, f_head);
		//If f(x) is within an acceptable range of zero, exit
		if(fabs(func->fx) < 0.0000000000001){
			break;
		}
		//Checks the slope of the function with input values to see
		//if the next guess will be moving away from the local root
		func->fpx = evaluate_function(func->x, &fp_head);
		if((fabs(evaluate_function((func->x - .5), f_head) > fabs(func->fx))) && (fabs(evaluate_function((func->x + .5), f_head) > fabs(func->fx)))){
			//If we're moving away from the local root in the positive
			//direction, then try to move back and readjust
			if((0 > func->fpx) && (func->fpx > -.1) && (fabs(func->fx) > .1)){
				func->x = func->x - .5;
				func->fx = evaluate_function(func->x, f_head);
				if(fabs(func->fx) < 0.0000000000001)
					break;
				func->fpx = evaluate_function(func->x, &fp_head);
				multiplicity = 2.0;
			}
			//If we're moving away from the local root in the negative
			//direction, then try to move forward and readjust
			else if((0.1 > func->fpx) && (func->fpx >= 0) && (fabs(func->fx) > 0.1))
			{
				func->x = func->x + .5;
				func->fx = evaluate_function(func->x, f_head);
				if(fabs(func->fx) < 0.0000000000001)
					break;
				func->fpx = evaluate_function(func->x, &fp_head);
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
					func->fx = evaluate_function(func->x, f_head);
					if(fabs(func->fx <  0.0000000000001))
						break;
					func->fpx = evaluate_function(func->x, &fp_head);
				}
			}
			else if((0.1 > func->fpx) && (func->fpx >= 0) && (fabs(func->fx) > .1)){
				func->x = first_guess;
				while(func->fpx >= 0){
					func->x = func->x + .5;
					func->fx = evaluate_function(func->x, f_head);
					if(fabs(func->fx < 0.0000000000001))
						break;
					func->fpx = evaluate_function(func->x, &fp_head);
				}
			}
		}
		//Finds next guess incorporating multiplicity.
		next_guess = get_next_guess(func, multiplicity);
		if(next_guess == old_func->x)
			cycle_count++;
		if(cycle_count > 3){
			if(evaluate_function(first_guess, &fp_head) > 0){
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
	free(fp_head);
	free(func);
	free(old_func);
	printf("Your root is at: %d\n", func->x);
}
