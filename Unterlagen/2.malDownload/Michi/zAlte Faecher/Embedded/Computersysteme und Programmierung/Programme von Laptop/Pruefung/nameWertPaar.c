#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char input[159] = { '\0' };

	rewind(stdin);
	gets_s(input, _countof(input));
	if(input[0] == '\0') { printf("No input!"); return EXIT_FAILURE; }
	//search first '-'
	char* ptr = strpbrk(input, "-");
	//check for NULLptr, no '>' after '-' and length
	if(ptr == NULL || *(ptr + 1) != '>' || (ptr - input) > 31) { printf("Wrong input!"); return EXIT_FAILURE; }
	*ptr = '\0';
	printf("Name: %s\nWert: %s", input, ptr+2);

	return EXIT_SUCCESS;
}

