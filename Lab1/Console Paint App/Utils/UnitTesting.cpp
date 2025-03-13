#if WITH_UNIT_TESTING == 1
#include <iostream>
#include <cassert>
#include "ParamsValidator.h"
#include "../Figures/Ellipse.h"
#include "../Figures/Rect.h"


int main() {
	assert(ValidateHorizPosition(-10) == false);
	assert(ValidateHorizPosition(0) == true);
	assert(ValidateHorizPosition(10) == true);
	assert(ValidateHorizPosition(250) == false);

	assert(ValidateVerticalPosition(-10) == false);
	assert(ValidateVerticalPosition(0) == true);
	assert(ValidateVerticalPosition(10) == true);
	assert(ValidateVerticalPosition(50) == false);

	assert(ValidateellipseParams(0, 0, 30, 30) == true);
	assert(ValidateellipseParams(-1, 0, 30, 30) == false);
	assert(ValidateellipseParams(0, -1, 30, 30) == false);
	assert(ValidateellipseParams(0, 0, 0, 30) == false);
	assert(ValidateellipseParams(0, 0, 30, 0) == false);

	assert(Elipse(4, 4, 1, 1, 'a').GetSquare() == 5);
	assert(Elipse(10, 10, 5, 5, 'a').GetSquare() == 81);
	assert(Elipse(10, 10, 10, 5, 'a').GetSquare() == 159);

	assert(ValidateRectParams(0, 0, 30, 30) == true);
	assert(ValidateRectParams(-1, 0, 30, 30) == false);
	assert(ValidateRectParams(0, -1, 30, 30) == false);
	assert(ValidateRectParams(0, 0, 0, 30) == false);
	assert(ValidateRectParams(0, 0, 30, 0) == false);
	assert(ValidateRectParams(0, 0, 0, 0) == false);

	assert(Rect(0, 0, 10, 10, 'a').GetSquare() == 100);
	assert(Rect(0, 0, 1, 1, 'a').GetSquare() == 1);
	assert(Rect(0, 0, 10, 5, 'a').GetSquare() == 50);

	assert(ValidateTriangleParams(0, 0, 30, 30) == true);
	assert(ValidateTriangleParams(-1, 0, 30, 30) == false);
	assert(ValidateTriangleParams(0, -1, 30, 30) == false);
	assert(ValidateTriangleParams(0, 0, 0, 30) == false);
	assert(ValidateTriangleParams(0, 0, 30, 0) == false);
	assert(ValidateTriangleParams(0, 0, 0, 0) == false);
}


#endif // WITH_UNIT_TESTING == 1

