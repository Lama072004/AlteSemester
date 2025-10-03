#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141593

void cone(double radius, double hoehe, double* volumen, double* mantel, double* oberflaeche) {
	double mantellinie = sqrt((radius * radius + hoehe * hoehe));
	*volumen = (PI * radius * radius * hoehe) / 3;
	*mantel = PI * mantellinie * radius;
	*oberflaeche = PI * radius * (radius + mantellinie);
}

int main(void) {
	double radius, hoehe, volumen, mantelflaeche, oberflaeche;
	while (1) {
		printf("Geben Sie den Radius ein:\n");
		if (scanf("%lf", &radius) != 1) break;
		printf("Geben Sie die Hoehe ein:\n");
		if (scanf("%lf", &hoehe) != 1) break;

		if (hoehe <= 0 || radius <= 0) return EXIT_FAILURE;

		cone(radius, hoehe, &volumen, &mantelflaeche, &oberflaeche);
		printf("Volumen: %lf\nMantelflaeche: %lf\nOberflache: %lf\n", volumen, mantelflaeche, oberflaeche);
	}
	return EXIT_SUCCESS;
}