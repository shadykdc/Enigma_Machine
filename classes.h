// enigma: classes.h
#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "classes.h"
#include "errors.h"
#include "helpers.h"
#include "checks.h"

class Plugboard
{
private:
	int pairs[26];
	int plug_cables;
public:
	Plugboard();

	void assign_values(std::ifstream& ins);
		/* function to assign values to pairs[] and plug_cables from the
		configuration file.  Pairs[] is an array of values for swapping and
		plug_cables is the number of cables that have been used. Also
		checks for invalid mappings */
			
	int swap(int input);
		/* function to swap a plugboard input with an output */
};

class Rotor
{
private:
	int notches[26];
	int pairs[26];
	int position;
public:
	Rotor();
	
	void assign_values(std::ifstream& ins);
		/* function to assign values to pairs[] and notches[] from the
		configuration file.  Pairs[] is an array of values for swapping and
		notches[] is an array of notches.  Also checks for invalid mappings */
	
	void assign_position(int input);
		/* function to assign the starting position value  from the
		position configuration file */
	
	int get_position();
		/* function that returns the position of rotor */
	
	void rotate();
		/* function to rotate (increment position of) the rotor */
	
	bool is_a_notch(int input);
		/* function that returns true if input is a notch value */
	
	int swap_fwd(int input);
		/* function to trace an input to the corresponding output forwards */
	int swap_rev(int input);
		/* function to trace an input to the corresponding output in reverse */
};

class Reflector
{
private:
	int pairs[26];
public:
	Reflector();
	
	void assign_values(std::ifstream& ins);
		/* function to assign values to pairs[] from the configuration file.
		Pairs[] is an array of values for swapping.  Also checks for invalid
		mappings */
		
	int swap(int input);
		/* function that swaps an input and returns an output */
};

#endif
