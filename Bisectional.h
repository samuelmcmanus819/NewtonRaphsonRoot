#include <stdio.h>
#include <math.h>
#define ACCEPTABLE_RANGE 0.0000000001 
/*
 * Name: function_solver
 * Purpose: To solve functions with a given x value
 * Author: Samuel McManus
 * @param bound: The value being plugged in for x
 * @param head: The head node of the list from which all of
 * 		the different coefficients and exponents of x
 * 		are found
 * @return solution: The result of x with all of the coefficients and exponents
 * 		     plugged in
 * Used By: bisectional
 * Date: August 12, 2020
 */ 
double function_solver(double bound, Node** head){ 
	double solution = 0; 
	double temp = 0; 
	//Allocate space for a list node
	Node *pt = (Node*)malloc(sizeof(Node)); 
	pt = *head;
	//Go through the list setting x to x^key * data
	//and adding it to solution
	while(pt != NULL){ 
		temp = 0;
		temp = pow(bound, (double)pt->key); 
		temp = temp * (double)pt->data; 
		solution = solution + temp; 
		pt = pt->next;
	}
	return solution;
}
/*
 * Name: bisectional
 * Purpose: To use the bisectional method to find a root of the function given
 * Author: Samuel McManus
 * @param a: The lower bound of the expected location of the root
 * @param b: The upper bound of the expected location of the root
 * @param head: The head node of the list with all of the 
 * 		coefficients and exponents stored
 * Uses: function_solver
 * Used By: main
 * Date: August 12, 2020
 */ 
void bisectional(int a, int b, Node** head)
{
	double LB, fLB, UB, fUB, midpoint, fMid;
	LB = (double) a;
	UB = (double) b;
	fLB = function_solver(LB, head);
	fUB = function_solver(UB, head);
	//If f(LowerBound) * f(UpperBound) > 0, then
	//there is no root between the two bounds and the bisectional
	//method will not work
	if((fLB * fUB) > 0){
		printf("You have entered invalid boundary points\n");
		exit(1);
	}
	//Checks if f(LB) == 0. If so then that's your root.
	if(fLB == 0){
		UB = LB;
	}
	//Checks if f(UB) == 0. If so then that's your root.
	if(fUB == 0){
		LB = UB;
	}
	//Passes through 52 times adjusting the midpoint closer to the true
	//root until it hits a point of acceptable closeness
	for(int i = 0; i < 53; i++){
		//Midpoint is set to the  mid point between the upper
		//and lower bound
		midpoint = (UB + LB) / 2;
		fMid = function_solver(midpoint, head);
		//If the result for midpoint was within the range
		//of acceptability, exit the loop.
		if(fabs(fMid) <= ACCEPTABLE_RANGE)
			break;
		//If the lower bound and the mid point have a root between them, 
		//set the upper bound to mid point
		if(fMid * fLB < 0)
			UB = midpoint;
		else
			LB = midpoint;
	}
	printf("The root is at %f\n", midpoint);
}

