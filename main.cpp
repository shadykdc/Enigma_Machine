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

int main(int argc, char **argv)
{	
	/* count how many parts and rotors there are */
	int rotor_count = argc-4; // = -1 if there are no rotors
	int part_count = count_parts(rotor_count);
	
	/* run error checks on configuration files */
	if(argc < 3 || argc == 4){
		cerr << "Insufficient number of configuration parameters: ";
		cerr << argc-1 << ".  (Please enter 2 or 4 or more)." << endl;
		exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
	}
	ifstream ins;
	check_plugboard(argv[1], ins);
	check_reflector(argv[2], ins);
	if(rotor_count > 0){
		for(int i = 3; i < argc-1; i++){
			check_rotor(argv[i], ins);
		}
		check_position(argv[argc-1], ins, rotor_count);
	}
	
	/* create and check plugboard and reflector mappings */
	Plugboard pb;
	ins.open(argv[1]);
	pb.assign_values(ins);
	ins.close();
	
	Reflector ref;
	ins.open(argv[2]);
	ref.assign_values(ins);
	ins.close();
	
	Rotor *rotors[rotor_count];
	if(rotor_count > 0){
		/* create an array of pointers to rotors */
		for (int i = 0; i < rotor_count; i++){
			rotors[i] = new Rotor();
		}	
		/* create rotors */
		for (int i = 0; i < rotor_count; i++){
			ins.open(argv[part_count-i]);
			(rotors[i])->assign_values(ins);
			ins.close();
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
	}

	/* get input from user */
	char input;
	while(cin >> ws >> input)
	{
	int enigma_in = input - 65;
	if(enigma_in > 25 || enigma_in < 0){
		cerr << "Invalid Character - please use capital letters, A-Z." << endl;
		exit(INVALID_INPUT_CHARACTER);
	}
	
	if (rotor_count > 0){
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
	}

	/* run the plugboard */
	int letter = pb.swap(enigma_in);
	if(rotor_count < 0){
		letter = ref.swap(letter);
		letter = pb.swap(letter);
		char output = letter+65;
		cout << output;
	}
	else {
		/* run the rotors */
		letter = letter + rotors[0]->get_position();
		letter = fix_input(letter);
		letter = rotors[0]->swap_fwd(letter);
		for(int i = 1; i < rotor_count; i++){
			letter = letter +
					 rotors[i]->get_position() -
					 rotors[i-1]->get_position();
			letter = fix_input(letter);
			letter = rotors[i]->swap_fwd(letter);
		}
		/* run the reflector */
		letter = letter - rotors[rotor_count-1]->get_position();
		letter = fix_input(letter);
		letter = ref.swap(letter) + rotors[rotor_count-1]->get_position();
		letter = fix_input(letter);
	
		/* run the rotors in reverse */
		for(int i = rotor_count-1; i > 0; i--){
			letter = rotors[i]->swap_rev(letter) -
					 rotors[i]->get_position() +
					 rotors[i-1]->get_position();
			letter = fix_input(letter);
		}
		letter = rotors[0]->swap_rev(letter) - rotors[0]->get_position();
		letter = fix_input(letter);
	
		/* run the plugboard */
		letter = pb.swap(letter);
		letter = fix_input(letter);
	
		/* print the output */
		char output = letter+65;
		cout << output;
	} // if / else bracket
	} // while loop bracket -- didn't want my code to be really narrow
	exit(NO_ERROR);
}
