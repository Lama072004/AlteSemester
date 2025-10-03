#include <stdio.h>
#include <stdlib.h>

#define WORDSIZE 32

typedef struct  {
	char word[WORDSIZE];
	int count;
} wordCount_t;

void abortWithMessage(const char* c) {
	printf("%s", c);
	exit(EXIT_FAILURE);
}

int main(void) {
	FILE* fPtr;
	errno_t check = fopen_s(&fPtr, "Input04.txt", "r");

	if (fPtr == NULL) abortWithMessage("File could not be opened");

	int n = 0;
	if (fscanf_s(fPtr, "%d", &n) != 1) abortWithMessage("Word count could not be read");
	int k = 0; 
	if (fscanf_s(fPtr, "%d", &k) != 1) abortWithMessage("Output number could not be read");
	
	int uniqueWords = 0;
	wordCount_t words[3];
	for (int i = 0; i < n; i++) {
		char newWord[WORDSIZE];
		if(fscanf_s(fPtr, "%s", &newWord) != 1) abortWithMessage("New word could not be read");


	}




	return EXIT_SUCCESS;
}