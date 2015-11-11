//	Integrated Programming Laboratory
//	Exercise 2, The Enigma Machine
//	Kathryn Shea, November 23, 2015

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "classes.h"
#include "errors.h"
#include "helpers.h"
#include "checks.h"

using namespace std;

/*
TO DO:
- Zero Rotor Case
- Need to make sure there is definitely a zero in the notch list
*/

int main(int argc, char **argv)
{	
	cerr << "The Enigma Machine is running." << endl;
	
	/* count how many parts and rotors there are */
	int rotor_count = argc-4;
	int part_count = count_parts(rotor_count);
	
	/* run error checks on files */
	if(argc < 3){
		cerr << "This program requires at least 3 files to run." << endl;
		exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
	}
	ifstream ins;
	check_plugboard(argv[1], ins);
	check_reflector(argv[2], ins);
	if(rotor_count > 0){
		for(int i = 3; i < argc-1; i++){
			check_rotor(argv[i], ins);
		}
	}
	check_position(argv[argc-1], ins, rotor_count);
	
	/* create plugboard and reflector */
	Plugboard pb;
	ins.open(argv[1]);
	pb.assign_values(ins);
	ins.close();
	
	Reflector ref;
	ins.open(argv[2]);
	ref.assign_values(ins);
	ins.close();
	
	/* create an array of pointers to enigma machine parts */
	Rotor *rotors[rotor_count];
	if(rotor_count > 0){
		for (int i = 0; i < rotor_count; i++){
			rotors[i] = new Rotor();
		}
	}
	
	/* create Rotors */
	if (rotor_count > 0){
		for (int i = 0; i < rotor_count; i++){
			ins.open(argv[part_count-i]);
			(rotors[i])->assign_values(ins);
			ins.close();
		}
	}

	/* import rotor positions */
	ins.open(argv[part_count+1]);
	int num;
	int i = 0;
	while (i < rotor_count && ins >> ws >> num){
		rotors[rotor_count-i-1]->assign_position(num);
		i++;
	}
	ins.close();

	/* get input from user */
	char input;
	while(cin >> ws >> input)
	{
	int enigma_in = input - 65;
	if(enigma_in > 25 || enigma_in < 0){
		cerr << "Invalid Character - please use capital letters, A-Z." << endl;
		exit(INVALID_INPUT_CHARACTER);
	}
	
	/* rotate the rotors */
	rotors[0]->rotate();
	int i = 0;
	bool keep_going = true;
	
	while(keep_going && i < rotor_count-1){
		if(rotors[i]->is_a_notch(rotors[i]->get_position())){
			rotors[i+1]->rotate();
		}
		else {
			keep_going = false;
		}
		if (!(rotors[i+1]->is_a_notch(rotors[i+1]->get_position()))){
			keep_going = false;
		}
		i++;
	}

	/* run the plugboard */
	int rotor_in = pb.swap(enigma_in);
	
	/* run the rotors */
	rotor_in = rotor_in + rotors[0]->get_position();
	rotor_in = fix_input(rotor_in);
	rotor_in = rotors[0]->swap_fwd(rotor_in);
	for(int i = 1; i < rotor_count; i++){
		rotor_in =	rotor_in +
					rotors[i]->get_position() -
					rotors[i-1]->get_position();
		rotor_in = fix_input(rotor_in);
		rotor_in = rotors[i]->swap_fwd(rotor_in);
	}
	
	/* run the reflector */
	rotor_in = rotor_in - rotors[rotor_count-1]->get_position();
	rotor_in = fix_input(rotor_in);
	int rotor_out = ref.swap(rotor_in) + rotors[rotor_count-1]->get_position();
	rotor_out = fix_input(rotor_out);
	
	/* run the rotors in reverse */
	for(int i = rotor_count-1; i > 0; i--){
		rotor_out = rotors[i]->swap_rev(rotor_out) -
					rotors[i]->get_position() +
					rotors[i-1]->get_position();
		rotor_out = fix_input(rotor_out);
	}
	rotor_out = rotors[0]->swap_rev(rotor_out) - rotors[0]->get_position();
	rotor_out = fix_input(rotor_out);
	
	/* run the plugboard */
	rotor_out = pb.swap(rotor_out);
	rotor_out = fix_input(rotor_out);
	char output = rotor_out+65;
	cout << output;
	}
	/* print decrypted/encrypted output */
	cerr << endl << "The Enigma Machine is finished running." << endl;
	exit(NO_ERROR);
}
