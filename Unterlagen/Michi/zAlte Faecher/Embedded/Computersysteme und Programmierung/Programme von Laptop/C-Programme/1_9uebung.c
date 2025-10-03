#include <stdio.h>
void stars2(void), stars6(void), stars10(void);

/*
int main()
{
	stars2();
	stars6();
	stars10();
	stars2();
	stars2();
	return 0;
}


*/

int main() {
	stars10();
	stars6();
	stars2();
	stars6();
	stars10();
	return 0;
}


void stars2() { printf("    **\n"); }
void stars6() { printf("  ******\n"); }
void stars10() { printf("**********\n"); }