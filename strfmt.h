#include <string.h>
#include <ctype.h>
/*
 * Name: NewLineStripper
 * Purpose: Takes off the new line character from strings entered
 * 	    through fgets
 * Author: Samuel McManus
 * @param string: The string having its new line character stripped
 * Used By: Main
 * Date: August 13, 2020
 */
void NewLineStripper(char *string)
{
	if((strlen(string) > 0) && (string[strlen(string) - 1] == '\n'))
		string[strlen(string) - 1] = '\0';
}
/*
 * Name: NumberChecker
 * Purpose: Determines whether a string can be transformed
 * 	    into an integer or not
 * Author: Samuel McManus
 * @param string: The string which will be transformed into an integer
 * @return has_errors: A boolean value defining whether there were any alphabetic
 * 		       characters in the string
 * Used By: Main
 * Date: August 13, 2020	
 */
int NumberChecker(char *string)
{
	int count;
	int has_errors = 0;
	for(count = 0; count < strlen(string); count++){
		if(isalpha(string[count]))
			has_errors = 1;
	}
	return has_errors;
}
