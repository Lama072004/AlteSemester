#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	double x, y, z;
} Point3D_t;

Point3D_t sumP3D(const Point3D_t* p1, const Point3D_t* p2) {
	return (Point3D_t){ p1->x + p2->x , p1->y + p2->y, p1->z + p2->z };
}

Point3D_t sProductP3D(const Point3D_t* p1, double factor) {
	return (Point3D_t) { p1->x* factor, p1->y* factor, p1->z* factor };
}

double iProductP3D(const Point3D_t* p1, const Point3D_t* p2) {
	return p1->x * p2->x + p1->y * p2->y + p1->z + p2->z;
}

char *toStringP3D(const Point3D_t* p) {
	static char stringOfPoint[50];
	sprintf(stringOfPoint, "x:%8lf\ny:%8lf\nz:%8lf", p->x, p->y, p->z);
	return stringOfPoint;
}