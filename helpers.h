// enigma: helper.h

#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "classes.h"
#include "errors.h"
#include "helpers.h"
#include "checks.h"

bool out_of_range(int input);
	/* returns true if input is not between 0 and 25 */

int set_in_range(int input);
	/* sets input to be within range of 0 and 25 using %26 */

int fix_input(int input);
	/* fixes input if it is out of range using out_of_range and set_in_range */

int count_parts(int rotor_count);
	/* counts how many parts are in the machine based on the rotor count */

#endif
