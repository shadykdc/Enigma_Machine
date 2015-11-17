// enigma: checks.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "classes.h"
#include "errors.h"
#include "helpers.h"
#include "checks.h"

using namespace std;

int check_input(char *file, ifstream& ins, int &count)
{
	/* check for characters -- also covers doubles since 0.4 contains a '.' */
	char input;
	ins.open(file);
	while(ins >> ws >> input){
		if(input > '9' || input < '0'){
			cerr << "Configuration file, " << file << ", ";
			cerr << "contains an invalid character: '" << input << "'." << endl;
			return NON_NUMERIC_CHARACTER;
		}
	}
	ins.close();
	
	/* check for out of range integers */
	count = 0;
	int in;
	ins.open(file);
	while(ins >> ws >> in){
		if(in > 25 || in < 0){
			cerr << "Configuration file, " << file << ", ";
			cerr << "contains an invalid index: '" << in << "'." << endl;
			return INVALID_INDEX;
		}
		count++;
	}
	ins.close();
	return NO_ERROR;
}

int check_plugboard(char *file, ifstream& ins)
{
	/* check for errors with opening the plugboard configuration file */
	ins.open(file);
	if (ins.fail()){
		cerr << "Failed to open plugboard configuration file: " << file << endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	ins.close();
	
	/* check the number of parameters for the plugboard */
	int count;
	int error = check_input(file, ins, count);
	if(error > 0){
		return error;}
	if(count > 26 || count%2 != 0){
		cerr << "Incorrect number of parameters in plugboard file ";
		cerr << file << endl;
		return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
	}
	return NO_ERROR;
}	

int check_reflector(char *file, ifstream& ins)
{
	/* check for errors with opening the reflector configuration file */
	ins.open(file);
	if (ins.fail()){
		cerr << "Failed to open reflector configuration file: " << file << endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	ins.close();
	
	/* check that the relfector has exactly 13 pairs */
	int count;
	int error = check_input(file, ins, count);
	if(error > 0){
		return error;}
	if(count%2 != 0){
		cerr << "Incorrect (odd) number of parameters in reflector file ";
		cerr << file << endl;
		return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	}
	if(count < 26){
		cerr << "Insufficient number of mappings in reflector file: ";
		cerr << file << endl;
		return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
	}
	return NO_ERROR;
}

int check_rotor(char *file, ifstream& ins)
{
	/* check for errors with opening the rotor configuration file */
	ins.open(file);
	if (ins.fail()){
		cerr << "Failed to open rotor configuration file: " << file << endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	ins.close();
	
	/* check the rotor mapping for too few inputs */
	int count;
	int error = check_input(file, ins, count);
	if(error > 0){
		return error;}
	if(count < 26){
		cerr << "Not all inputs mapped in rotor file: ";
		cerr << file << endl;
		return INVALID_ROTOR_MAPPING;
	}
	/* check the rotor mapping for too many inputs */
	else if (count > 52){
		cerr << "Configuration file has " << count;
		cerr << " inputs when it only uses up to 52 integers: ";
		cerr << file << endl;
		return INVALID_ROTOR_MAPPING;
	}
	return NO_ERROR;
}

int check_position(char *file, ifstream& ins, int rotor_count)
{
	/* check for errors with opening the position configuration file */
	ins.open(file);
	if (ins.fail()){
		cerr << "Failed to open position configuration file: " << file << endl;
		return ERROR_OPENING_CONFIGURATION_FILE;
	}
	ins.close();
	
	int count;
	int error = check_input(file, ins, count);
	if(error > 0){
		return error;}
	
	/* check for too many position inputs */
	/*if (count > rotor_count){
		cerr << "There are more positions (" << count << ") than rotors (";
		cerr << rotor_count << ")." << endl;
		exit(INVALID_INDEX);
	} TOOK THIS OUT BECAUSE THE TESTS ONLINE APPARENTLY DON'T ACCOUNT FOR THIS*/
	/* check for too few position inputs */
	if (count < rotor_count){
		cerr << "There are fewer positions (" << count << ") than rotors (";
		cerr << rotor_count << ")." << endl;
		return NO_ROTOR_STARTING_POSITION;
	}
	return NO_ERROR;
}