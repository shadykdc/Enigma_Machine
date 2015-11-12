// enigma: classes.h
#ifndef CHECKS_H
#define CHECKS_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "classes.h"
#include "errors.h"
#include "helpers.h"
#include "checks.h"

bool check_plugboard(char *file, std::ifstream& ins);
	/* returns true if a configuration file for the plugboard has no errors */

bool check_reflector(char *file, std::ifstream& ins);
	/* returns true if a configuration file for the reflector has no errors */

bool check_rotor(char *file, std::ifstream& ins);
	/* returns true if a configuration file for the rotors has no errors */

bool check_position(char *file, std::ifstream& ins, int rotor_count);
	/* returns true if a configuration file for the position has no errors */

#endif
