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
	int plug_cables;
	int pairs[26];
public:
	Plugboard();

	/* function to assign pairs to the array and the number of cables */
	void assign_values(std::ifstream& ins);
	
	/* function to swap an input with an output */
	int swap(int input);
};

class Rotor
{
private:
	int notches[26];
	int pairs[26];
	int position;
public:
	Rotor();
	
	/* function to assign pairs to the array and a value for the notch */
	void assign_values(std::ifstream& ins);
	
	/* assign the position from the other stream */
	void assign_position(int input);
	
	/* get position of rotor */
	int get_position();
	
	/* function to rotate the rotor */
	void rotate();
	
	/* function to check if a number is a notch */
	bool is_a_notch(int input);
	
	/* function to trace an input to the corresponding output backwards */
	int swap_fwd(int input);
	int swap_rev(int input);
};

class Reflector
{
private:
	int pairs[26];
public:
	Reflector();
	
	/* function to assign pairs to the array */
	void assign_values(std::ifstream& ins);
	
	/* function to swap an input with an output */
	int swap(int input);
};

#endif