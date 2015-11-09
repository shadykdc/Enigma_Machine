#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <fstream>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ENIGMAPART CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class EnigmaPart
{
public:
	int position;
	
	EnigmaPart();
	
	/* function to get position */
	int get_position();
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~PLUGBOARD CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Plugboard : public EnigmaPart
{
private:
	int plug_cables;
	int pairs[26];
	EnigmaPart *ptr_to_next_part;
public:
	Plugboard();

	/* function to assign pairs to the array and the number of cables */
	void assign_values(std::ifstream& in_stream, EnigmaPart *next_part);
	
	/* function to swap an input with an output */
	int swap(int input);
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ROTOR CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

class Rotor : public EnigmaPart
{
private:
	int notch;
	int pairs[26];
	EnigmaPart *ptr_to_fwd_part;
	EnigmaPart *ptr_to_rev_part;
public:
	Rotor();
	
	/* function to assign pairs to the array and a value for the notch */
	void assign_values(std::ifstream& in_stream, EnigmaPart *fwd_part, EnigmaPart *rev_part);
	
	/* assign the position from the other stream */
	void assign_position(std::ifstream& in_stream);
	
	/* function to rotate the rotor */
	void rotate();
	
	/* function to trace an input to the corresponding output backwards */
	int swap_rev(int input);
	int swap_fwd(int input);
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~REFLECTOR CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class Reflector : public EnigmaPart
{
private:
	int pairs[26];
	EnigmaPart *ptr_to_next_part;
public:
	Reflector();
	
	/* function to assign pairs to the array */
	void assign_values(std::ifstream& in_stream, EnigmaPart *next_part);
	
	/* function to swap an input with an output */
	int swap(int input);
};

#endif