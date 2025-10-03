#include <math.h>

static const double cSquareRootOfTwo = 1.41421356237309;
static const double cPi = 3.14159265359;

//data ptr of field, size(must be a square)
double getAngle(double* data, int fieldSize) {
	double maxAngle = 0.0f;
	for (int i = 1; i < fieldSize - 1; i++) {
		for (int j = 1; j < fieldSize - 1; j++) {
			// i, j, lines and columns of array --> search entry
			double* pSearchEntry = data + j + i * fieldSize;

			double distanceStraight = 0.0f;
			//same line, entry left and right of search entry
			if (distanceStraight < fabs(*pSearchEntry - *(pSearchEntry - 1)))
				distanceStraight = fabs(*pSearchEntry - *(pSearchEntry - 1));
			if (distanceStraight < fabs(*pSearchEntry - *(pSearchEntry + 1)))
				distanceStraight = fabs(*pSearchEntry - *(pSearchEntry + 1));

			//line above and below search entry
			if (distanceStraight < fabs(*pSearchEntry - *(pSearchEntry - (fieldSize))))
				distanceStraight = fabs(*pSearchEntry - *(pSearchEntry - (fieldSize)));
			if (distanceStraight < fabs(*pSearchEntry - *(pSearchEntry + (fieldSize))))
				distanceStraight = fabs(*pSearchEntry - *(pSearchEntry + (fieldSize)));

			double tanOfDistance = (atan(distanceStraight));
			//compare max angle, set new angle if bigger
			if (maxAngle < tanOfDistance) {
				maxAngle = tanOfDistance;
			}

			//search entries diagonal to search entry
			double distanceDiagonal = 0.0f;
			//search above entry
			if (distanceDiagonal < fabs(*pSearchEntry - *(pSearchEntry - fieldSize - 1)))
				distanceDiagonal = fabs(*pSearchEntry - *(pSearchEntry - fieldSize - 1));
			if (distanceDiagonal < fabs(*pSearchEntry - *(pSearchEntry - fieldSize + 1)))
				distanceDiagonal = fabs(*pSearchEntry - *(pSearchEntry - fieldSize + 1));
			//search below entry
			if (distanceDiagonal < fabs(*pSearchEntry - *(pSearchEntry + fieldSize - 1)))
				distanceDiagonal = fabs(*pSearchEntry - *(pSearchEntry + fieldSize - 1));
			if (distanceDiagonal < fabs(*pSearchEntry - *(pSearchEntry + fieldSize + 1)))
				distanceDiagonal = fabs(*pSearchEntry - *(pSearchEntry + fieldSize + 1));

			//compare max angle, set new angle if bigger
			tanOfDistance = (atan(distanceDiagonal / cSquareRootOfTwo));
			if (maxAngle < tanOfDistance) {
				maxAngle = tanOfDistance;
			}
		}
	}
	return (maxAngle/cPi)*180;
}
