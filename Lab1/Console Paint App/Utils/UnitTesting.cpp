#if WITH_UNIT_TESTING == 1
#include <iostream>
#include <cassert>
#include "ParamsValidator.h"


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


}


#endif // WITH_UNIT_TESTING == 1

