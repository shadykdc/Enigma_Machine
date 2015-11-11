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

/* checks if input is not between 0 and 25 */
bool out_of_range(int input);

/* sets input to be within range of 0 and 25 using %26 */
int set_in_range(int input);

/* fixes an output that is out of range using out_of_range and set_in_range */
int fix_input(int input);

/* counts how many parts are in the enigma machine based on the rotor count */
int count_parts(int rotor_count);

#endif
