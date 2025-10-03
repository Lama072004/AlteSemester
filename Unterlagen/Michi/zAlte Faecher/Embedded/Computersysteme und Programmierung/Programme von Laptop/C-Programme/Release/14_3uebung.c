#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

char* strRevers(const char* str) {
	int count = 0;
	char* pReturn;
	
	while (str[count] != '\0') count++; //länge lesen
	pReturn = malloc(count);
	if (pReturn == NULL) return pReturn; //kein Speicher verfügbar, Abbruch
	
	int temp = count;
	for (int i = 0; i < temp ; i++, count --) {
		pReturn[i] = str[count - 1];
	}
	pReturn[temp] = '\0';
	return pReturn;
}

//bool checkPalindrome(const char* str1, const char* str2) {
//	bool ret = 1;
//	while()
//}

int main(void) {

	char input[100];
	while (1) {
		scanf_s("%s", input, _countof(input));

		char* reversedString = strRevers(input);
		if (reversedString == NULL) return EXIT_FAILURE;
		printf("%s", reversedString);
		free(reversedString);
	}

}