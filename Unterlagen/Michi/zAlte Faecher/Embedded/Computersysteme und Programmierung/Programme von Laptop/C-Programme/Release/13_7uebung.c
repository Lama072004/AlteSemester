#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int strIcmp(const char *firstStr, const char *secondStr) {
	int tmp = 0;
	while (*firstStr && *secondStr) {
		if (*firstStr != *secondStr) { 
			if (toupper(*firstStr) != *secondStr) {
				if (tolower(*firstStr) != *secondStr) { //Strings haben unterschiedliche Inhalte, abbruch und rückgabe 
					tmp = *firstStr - *secondStr;
					break;
				}
			}

		}
		firstStr++;
		secondStr++;
	}    
	return (0 < tmp) - (tmp < 0);
}

int main(void) {
	char inputOne[100], inputTwo[100];

	printf("Geben Sie die erste Zeichenkette ein:\n");
	rewind(stdin);
	fgets(inputOne, _countof(inputOne), stdin);

	printf("Geben Sie die zweite Zeichenkette ein:\n");
	rewind(stdin);
	fgets(inputTwo, _countof(inputTwo), stdin);

	printf("%d", strIcmp(inputOne, inputTwo));



	return 0;
}