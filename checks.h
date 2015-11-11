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

/* checks a configuration file for the plugboard for any errors */
bool check_plugboard(char *file, std::ifstream& ins);

/* checks a configuration file for the reflector for any errors */
bool check_reflector(char *file, std::ifstream& ins);

/* checks a configuration file for the rotor for any errors */
bool check_rotor(char *file, std::ifstream& ins);

/* checks a configuration file for the rotor positions for any errors */
bool check_position(char *file, std::ifstream& ins, int rotor_count);

#endif
