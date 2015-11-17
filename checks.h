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

int check_input(char *file, std::ifstream& ins, int& count);
	/* returns the error code if there is one after checking the input file */

int check_plugboard(char *file, std::ifstream& ins);
	/* returns the error code if a configuration file for the plugboard has
	an error, otherwise return NO_ERROR (0) */

int check_reflector(char *file, std::ifstream& ins);
	/* returns the error code if a configuration file for the reflector has
	an error, otherwise return NO_ERROR (0) */

int check_rotor(char *file, std::ifstream& ins);
	/* returns the error code if a configuration file for the rotors has 
	an error, otherwise return NO_ERROR (0) */

int check_position(char *file, std::ifstream& ins, int rotor_count);
	/* returns the error code if a configuration file for the position has
	an error, otherwise return NO_ERROR (0) */

#endif