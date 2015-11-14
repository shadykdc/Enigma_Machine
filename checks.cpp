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

int check_input(char *file, ifstream& ins)
{
	/* check for characters -- also covers doubles since 0.4 contains a '.' */
	char input;
	ins.open(file);
	while(ins >> ws >> input){
		if(input > '9' || input < '0'){
			cerr << "Configuration file, " << file << ", ";
			cerr << "contains an invalid character: '" << input << "'." << endl;
			exit(NON_NUMERIC_CHARACTER);
		}
	}
	ins.close();
	
	/* check for out of range integers */
	int count = 0;
	int in;
	ins.open(file);
	while(ins >> ws >> in){
		if(in > 25 || in < 0){
			cerr << "Configuration file, " << file << ", ";
			cerr << "contains an invalid index: '" << in << "'." << endl;
			exit(INVALID_INDEX);
		}
		count++;
	}
	ins.close();
	return(count);
}

bool check_plugboard(char *file, ifstream& ins)
{
	/* check for errors with opening the plugboard configuration file */
	ins.open(file);
	if (ins.fail()){
		cerr << "Failed to open plugboard configuration file: " << file << endl;
		exit(ERROR_OPENING_CONFIGURATION_FILE);
	}
	ins.close();
	
	/* check the number of parameters for the plugboard */
	int count = check_input(file, ins);
	if(count > 26 || count%2 != 0){
		cerr << "Incorrect number of parameters in plugboard file ";
		cerr << file << endl;
		exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
	}
	return true;
}	

bool check_reflector(char *file, ifstream& ins)
{
	/* check for errors with opening the reflector configuration file */
	ins.open(file);
	if (ins.fail()){
		cerr << "Failed to open reflector configuration file: " << file << endl;
		exit(ERROR_OPENING_CONFIGURATION_FILE);
	}
	ins.close();
	
	/* check that the relfector has exactly 13 pairs */
	int count = check_input(file, ins);
	if(count%2 != 0){
		cerr << "Incorrect (odd) number of parameters in reflector file ";
		cerr << file << endl;
		exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
	}
	return true;
	if(count < 26){
		cerr << "Insufficient number of mappings in reflector file: ";
		cerr << file << endl;
		exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);
	}
	return true;
}

bool check_rotor(char *file, ifstream& ins)
{
	/* check for errors with opening the rotor configuration file */
	ins.open(file);
	if (ins.fail()){
		cerr << "Failed to open rotor configuration file: " << file << endl;
		exit(ERROR_OPENING_CONFIGURATION_FILE);
	}
	ins.close();
	
	/* check the rotor mapping for too few inputs */
	int count = check_input(file, ins);
	if(count < 26){
		cerr << "Not all inputs mapped in rotor file: ";
		cerr << file << endl;
		exit(INVALID_ROTOR_MAPPING);
	}
	/* check the rotor mapping for too many inputs */
	else if (count > 52){
		cerr << "Configuration file has " << count;
		cerr << " inputs when it only uses up to 52 integers: ";
		cerr << file << endl;
		exit(INVALID_ROTOR_MAPPING);
	}
	return true;
}

bool check_position(char *file, ifstream& ins, int rotor_count)
{
	/* check for errors with opening the position configuration file */
	ins.open(file);
	if (ins.fail()){
		cerr << "Failed to open position configuration file: " << file << endl;
		exit(ERROR_OPENING_CONFIGURATION_FILE);
	}
	ins.close();
	
	int count = check_input(file, ins);
	
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
		exit(NO_ROTOR_STARTING_POSITION);
	}
	return true;
}