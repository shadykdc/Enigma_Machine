#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "classes.h"
#include "errors.h"

using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ENIGMAPART CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
EnigmaPart::EnigmaPart()
{
	position = 0;
}

int EnigmaPart::get_position()
{
	return(position);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~PLUGBOARD CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Plugboard::Plugboard()
{
	for(int i = 0; i < 26; i++){
		pairs[i] = 0;}
	ptr_to_next_part = NULL;
	plug_cables = 0;
}

void Plugboard::assign_values(ifstream& in_stream, EnigmaPart *next_part)
{
	int num;
	int count = 0;
	while(in_stream >> ws >> num)
	{
		pairs[count] = num;
		count++;
	}
	plug_cables = count/2;
	ptr_to_next_part = next_part;
}

int Plugboard::swap(int input)
{
	for (int i = 0; i < (plug_cables*2); i++)
	{
		if(pairs[i] == input)
		{
			if (i%2 == 0){
				return (pairs[i+1]);}
			else {
				return (pairs[i-1]);}
		}
	}
	return(input);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ROTOR CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Rotor::Rotor()
{
	position = 0;
	for(int i = 0; i < 26; i++){
		pairs[i] = 0;}
	ptr_to_fwd_part = NULL;
	ptr_to_rev_part = NULL;
	notch = 0;
}

void Rotor::assign_values(std::ifstream& in_stream, EnigmaPart *fwd_part, EnigmaPart *rev_part)
{
	int num;
	int count = 0;
	int list_in[27];
	while(in_stream >> ws >> num)
	{
		list_in[count] = num;
		count++;
	}
	for(int i = 0; i < 26; i++)
		pairs[i] = list_in[i];
	notch = list_in[26];
	ptr_to_fwd_part = fwd_part;
	ptr_to_rev_part = rev_part;
}

void Rotor::assign_position(std::ifstream& in_stream)
{
	// do nothing
}

void Rotor::rotate()
{
	position = position + 1;
}

int Rotor::swap_fwd(int input)
{
	for (int i = 0; i < 26; i++)
	{
		return(pairs[input]);
	}
	exit(1);
}

int Rotor::swap_rev(int input)
{
	for (int i = 0; i < 26; i++)
	{
		if(pairs[i] == input)
		{
			return(i);
		}
	}
	exit(1);
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~REFLECTOR CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Reflector::Reflector()
{
	position = 0;
	for(int i = 0; i < 26; i++){
		pairs[i] = 0;}
	ptr_to_next_part = NULL;
}

void Reflector::assign_values(ifstream& in_stream, EnigmaPart *next_part)
{
	int num;
	int count = 0;
	while(in_stream >> ws >> num)
	{
		pairs[count] = num;
		count++;
	}
	ptr_to_next_part = next_part;
}

int Reflector::swap(int input)
{
	for (int i = 0; i < 26; i++)
	{
		if(pairs[i] == input)
		{
			if (i%2 == 0){
				return (pairs[i+1]);}
			else {
				return (pairs[i-1]);}
		}
	}
	exit(1);
}