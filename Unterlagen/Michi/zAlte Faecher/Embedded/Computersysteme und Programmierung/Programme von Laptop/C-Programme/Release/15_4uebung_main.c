#include "15_4uebungHead.h"


int main(void) {
	Point3D_t point1 = { 1.0f, 2.5f,-3.3f }, point2 = { -3.3f, 4.0f, 2.0f };
	Point3D_t point3 = sumP3D(&point1, &point2);

	printf("x: %lf\ny: %lf\nz: %lf\n\n", sumP3D(&point1, &point2).x, 
		sumP3D(&point1, &point2).y, sumP3D(&point1, &point2).z);
	
	printf("Skaliert mit 5:\nx: %lf\ny: %lf\nz: %lf\n\n", sProductP3D(&point1, 5.0f).x,
		sProductP3D(&point1, 3.0f).y, sProductP3D(&point1, 3.0f).z);
	
	printf("Inneres Produkt:\n%lf\n\n", iProductP3D(&point1, &point2));
	
	char* string = toStringP3D(&point3);
	
	printf("%s", string);

	return 0;
}