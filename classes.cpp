#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "classes.h"
#include "errors.h"

using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~PLUGBOARD CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Plugboard::Plugboard()
{
	for(int i = 0; i < 26; i++){
		pairs[i] = 0;}
	plug_cables = 0;
}

void Plugboard::assign_values(ifstream& ins)
{
	int num;
	int count = 0;
	while(ins >> ws >> num)
	{
		pairs[count] = num;
		count++;
	}
	plug_cables = count/2;
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
	notch = 0;
	position = 0;
	for(int i = 0; i < 26; i++){
		pairs[i] = 0;}
}

void Rotor::assign_values(std::ifstream& ins)
{
	int num;
	int count = 0;
	int list_in[27];
	while(ins >> ws >> num)
	{
		list_in[count] = num;
		count++;
	}
	for(int i = 0; i < 26; i++)
		pairs[i] = list_in[i];
	notch = list_in[26];
}

void Rotor::assign_position(int input)
{
	position = input;
}

int Rotor::get_position()
{
	return(position);
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
	cerr << "Invalid input." << endl;
	exit(2);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~REFLECTOR CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Reflector::Reflector()
{
	for(int i = 0; i < 26; i++){
		pairs[i] = 0;}
}

void Reflector::assign_values(ifstream& ins)
{
	int num;
	int count = 0;
	while(ins >> ws >> num)
	{
		pairs[count] = num;
		count++;
	}
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
	cerr << "Invalid input." << endl;
	exit(2);
}