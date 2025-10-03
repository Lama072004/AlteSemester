
#include <stdbool.h>
#include <stdio.h>

bool palindrome(unsigned int num) {
	unsigned int n = num;
	unsigned int reverseNum = 0;
	while (n != 0) {
		reverseNum *= 10;
		reverseNum += (n % 10);
		n /= 10;
	}
	return (num == reverseNum);
}

int main(int argc, char* argv[]) {
	printf("Plaindromzahlen\n");
	unsigned int lowerBound = 100;
	unsigned int upperBound = 200;

	//soll ausgeben 101, 111, 121, 131, ...
	while (lowerBound <= upperBound) {
		if (palindrome(lowerBound)) printf("%d, ", lowerBound);
		lowerBound += 1;
	}

	return 0;
}