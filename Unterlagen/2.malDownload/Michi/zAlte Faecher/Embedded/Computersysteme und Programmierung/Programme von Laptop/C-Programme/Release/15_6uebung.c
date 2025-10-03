#include <limits.h>
#include <stdio.h>

typedef struct {
	long z, n;
}bruch;

long ggT(long a, long b) {
	long tmp;
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (a == 0 || b == 0) return 1;

	while (b != 0) {
		tmp = a % b; a = b; b = tmp;
	}
	return a;
};

void kuerzeBruch(bruch* b) {
	if ((b->n < 0 && b->z < 0) || (b->n < 0 && b->z >0)) {
		b->n = -b->n;
		b->z = -b->z;
	};
	long g = ggT(b->z, b->n);
	b->n /= g;
	b->z /= g;
};

bruch addB(bruch* b1, bruch* b2) {
	bruch val;
	val.z = b1->n * b2->z + b1->z * b2->n;
	val.n = b1->n * b2->n;
	kuerzeBruch(&val);
	return val;
};

bruch subB(bruch* b1, bruch* b2) {
	bruch val;
	val.z = b1->z * b2->n - b1->n * b2->z;
	val.n = b1->n * b2->n;
	kuerzeBruch(&val);
	return val;
};

bruch mulB(bruch* b1, bruch* b2) {
	bruch val;
	val.z = b1->z * b2->z;
	val.n = b1->n * b2->n;
	kuerzeBruch(&val);
	return val;
};

bruch divB(bruch* b1, bruch* b2) {
	bruch val;
	val.z = b1->z * b2->n;
	val.n = b1->n * b2->z;
	kuerzeBruch(&val);
	return val;
};

void printB(const bruch* b) {
	printf("Bruch: %d/%d\n", b->z, b->n);
}

double bruchToDouble(bruch* b) {
	return (double)b->z / b->n;
}

int main(void) {
	bruch b1 = { 99,-7 }, b2 = { -5,19 }, b3;

	printf("Bruch 1 : %d/%d\nBruch 2 : %d/%d\n\n", b1.z, b1.n, b2.z, b2.n);

	b3 = addB(&b1, &b2);
	printf("Summe:\n%d/%d\n", b3.z, b3.n);
	printf("Als Float: %lf\n", bruchToDouble(&b3));
	b3 = subB(&b1, &b2);
	printf("Subtraktion:\n%d/%d\n", b3.z, b3.n);
	printf("Als Float: %lf\n", bruchToDouble(&b3));
	b3 = mulB(&b1, &b2);
	printf("Multiplikation:\n%d/%d\n", b3.z, b3.n);
	printf("Als Float: %lf\n", bruchToDouble(&b3));
	b3 = divB(&b1, &b2);
	printf("Division:\n%d/%d\n", b3.z, b3.n);
	printf("Als Float: %lf\n", bruchToDouble(&b3));
}