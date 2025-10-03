#include <stdio.h>
#include <stdlib.h>

double fahr2celsius(double fahr) {
	return 5.0f / 9.0f * (fahr - 32.0f);
}

double celsius2kelvin(double celsius) {
	return celsius + 273.15f;
}

int main(void) {
	printf("Please enter temperature in fahrenheit:\n");
	double input;
	rewind(stdin);
	while (scanf_s("%lf", &input) != 1) { printf("Input incorrect! Enter valid number. Decimal as '.' !\n"); rewind(stdin); }

	{
		double celsius = fahr2celsius(input);
		double kelvin = celsius2kelvin(celsius);
		if (kelvin < 0.0f) { printf("Temperature below absolute zero!"); return EXIT_FAILURE; }
		else {
			printf("Temperature in:\n"
				"Celsius: %12.2lf\nKelvin: %13.2lf", celsius, kelvin);
		}
	}
	return EXIT_SUCCESS;
}