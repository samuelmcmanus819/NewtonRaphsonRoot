#include <string.h>
#include <ctype.h>
void NewLineStripper(char *string)
{
	if((strlen(string) > 0) && (string[strlen(string) - 1] == '\n'))
		string[strlen(string) - 1] = '\0';
}
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
