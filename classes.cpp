// enigma: classes.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "classes.h"
#include "errors.h"
#include "helpers.h"
#include "checks.h"

using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~PLUGBOARD CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Plugboard::Plugboard()
{
	for(int i = 0; i < 26; i++){
		pairs[i] = 0;
	}
	plug_cables = 0;
}

bool Plugboard::assign_values(ifstream& ins)
{
	int num;
	int count = 0;
	while(ins >> ws >> num){
		pairs[count] = num;
		count++;
	}
	plug_cables = count/2;
	
	/* check plugboard for repeats */
	for (int i = 0; i < count-1; i++){
		for (int j = i+1; j < count; j++){
			if(pairs[i] == pairs[j]){
				cerr << "The plugboard configuration file has an ";
				cerr << "invalid mapping.  " << pairs[i] << " appears";
				cerr << " twice." << endl;
				return false;
			}
		}
	}
	return true;
}

int Plugboard::swap(int input)
{
	for (int i = 0; i < (plug_cables*2); i++){
		if(pairs[i] == input){
			if (i%2 == 0){
				return (pairs[i+1]);
			}
			else {
				return (pairs[i-1]);
			}
		}
	}
	return(input);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ROTOR CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Rotor::Rotor()
{
	position = 0;
	for(int i = 0; i < 26; i++){
		pairs[i] = -1;
		notches[i] = -1;
	}
}

bool Rotor::assign_values(char *file)
{
    ifstream ins;
    ins.open(file);
	int num;
	int count = 0;
	int list_in[52];
	for(int i = 0; i < 52; i++){
		list_in[i] = -1;}
	while(ins >> ws >> num){
		list_in[count] = num;
		count++;
	}
	ins.close();
	for(int i = 0; i < 26; i++){
		pairs[i] = list_in[i];
	}
	for(int i = 26; i < 52; i++){
		notches[i-26] = list_in[i];
	}
	
	/* check rotor for repeats */
	for (int i=0; i<25; i++){
		for(int j=i+1; j<26; j++){
			if(pairs[i] == pairs[j]){
				cerr << "Invald mapping of input " << pairs[j] << " to output ";
				if (j%2 == 0){
				    cerr << pairs[j+1] << " (output " << pairs[j+1];
				}
				else {
				    cerr << pairs[j-1] << " (output " << pairs[j-1];
				}
				cerr << " is already mapped to from input ";
				if (i%2 == 0){
				    cerr << pairs[i+1];
				}
				else {
				    cerr << pairs[i-1];
				}
				cerr << ") in rotor file: " << file << endl;
				return false;
			}
		}
	}
	for (int i = 0; i < 25; i++){
		for(int j = i+1; j < 26; j++){
			if(notches[i] == notches[j] && notches[i] != -1){
				cerr << "Rotor configuration file contians repeat";
				cerr << " notches (" << notches[i] << ")." << endl;
				return false;
			}
		}
	}
	return true;
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
	if(position > 25){
		position = position%26;
	}
}

bool Rotor::is_a_notch(int input)
{
	for (int i = 0; i < 26; i++){
		if (notches[i] == input){
			return true;
		}
	}
	return false;
}

int Rotor::swap_fwd(int input)
{
	return(pairs[input]);
}

int Rotor::swap_rev(int input)
{
	for (int i = 0; i < 26; i++){
		if(pairs[i] == input){
			return(i);
		}
	}
	cerr << "Rotor::swap_rev received invalid input: " << input << "." << endl;
	exit(2);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~REFLECTOR CLASS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Reflector::Reflector()
{
	for(int i = 0; i < 26; i++){
		pairs[i] = 0;}
}

bool Reflector::assign_values(ifstream& ins)
{
	int num;
	int count = 0;
	while(ins >> ws >> num)
	{
		pairs[count] = num;
		count++;
	}
	
	/* check reflector for repeats */
	for (int i=0; i<25; i++){
		for(int j=i+1; j<26; j++){
			if(pairs[i] == pairs[j]){
				cerr << "The reflector configuration file has an invalid ";
				cerr << "mapping.  " << pairs[i] << " appears twice." << endl;
				return false;
			}
		}
	}
	return true;
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
	cerr << "Reflector::swap has received invalid input: " << input << ".";
	cerr << endl;
	exit(2);
}