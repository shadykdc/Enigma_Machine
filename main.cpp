//	Integrated Programming Laboratory
//	Exercise 2, The Enigma Machine
//	Kathryn Shea, November 23, 2015

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "classes.h"
#include "errors.h"

using namespace std;

bool out_of_range(int input)
{
	if(input < 0){
		return true;}
	else if(input > 25){
		return true;}
	else
		return false;
}

int set_in_range(int input)

{
	if(input < 0){
		return(input+26);}
	if(input > 25){
		return(input%26);}
	else
		return input;
}		

int fix_input(int input)
{
	while (out_of_range(input))
	{
		input = set_in_range(input);
	}
	return(input);
}

int count_parts(int rotor_count)
{
	cout << "There are " << rotor_count << " rotors." << endl;
	int part_count = 0;
	if(rotor_count > 0){
		return(rotor_count+2);}
	else {
		return(rotor_count+3);}
	cout << "There are " << part_count << " enigma machine parts." << endl;
}

int main(int argc, char **argv)
{
	/* count how many parts and rotors there are */
	int rotor_count = argc-4;
	int part_count = count_parts(rotor_count);
	
	
	/* create an array of pointers to enigma machine parts */
	EnigmaPart *enigma_machine[part_count];
	enigma_machine[part_count-1] = new Reflector();
	if(rotor_count > 0)
	{
		for (int i = 1; i <= part_count-2; i++)
		{
			enigma_machine[i] = new Rotor();
		}
	}
	enigma_machine[0] = new Plugboard();
	
	/* Create Plugboard */
	ifstream in_stream;
	in_stream.open(argv[1]);
	((Plugboard *)enigma_machine[0])->assign_values(in_stream, enigma_machine[1]);
	in_stream.close();
	
	/* Create Reflector */
	in_stream.open(argv[2]);
	((Reflector *)enigma_machine[part_count-1])->assign_values(in_stream, enigma_machine[part_count-2]);
	in_stream.close();
	
	/* Create Rotors */
	if (rotor_count > 0)
	{
		for (int i = 0; i < part_count-2; i++)
		{
			in_stream.open(argv[part_count-i]);
			((Rotor *)enigma_machine[i+1])->assign_values(in_stream, enigma_machine[i], enigma_machine[i+2]);
			in_stream.close();
		}
	}
	
	/* Import rotor positions */

		// for now, they're all 0;
		
	/* (de/en)crypt a letter */
	
	// Input from user
	char input;
	cout << "Enter a capital letter: ";
	cin >> input;
	
	int enigma_input = input - 65;
	
	// Plugboard
	cout << "We're inputing " << input << " (" << enigma_input
	<< ") into the plugboard." << endl;
	
	((Rotor *)enigma_machine[1])->rotate(); cout << "Rotor #1 rotates!" << endl;
	int pb_out = (((Plugboard *)enigma_machine[0])->swap(enigma_input));
	pb_out = fix_input(pb_out);
	cout << "The plugboard spit out " << pb_out << "." << endl;
	
	// Rotor #1
	int rot1_in = (pb_out + ((Rotor *)enigma_machine[1])->get_position());
	rot1_in = fix_input(rot1_in);
	cout << "Rotor 1 is taking in " << rot1_in << endl;
	
	// The rest of the rotors
	int rotor_in = rot1_in;
	int i = 0;
	while(i < part_count-3)
	{
		rotor_in =
		((Rotor *)enigma_machine[i+1])->swap_fwd(rotor_in)+(((Rotor *)enigma_machine[i+2])->get_position())-(((Plugboard *)enigma_machine[i+1])->get_position());
		rotor_in = fix_input(rotor_in);
		cout << "Rotor " << i+2 << " is taking in " << rotor_in << endl;
		i++;
	}
	
	// Reflector
	int ref_in =
	(((Rotor *)enigma_machine[part_count-2])->swap_fwd(rotor_in)-(((Rotor *)enigma_machine[part_count-2])->get_position()));
	ref_in = fix_input(ref_in);
	cout << "Reflector is taking in " << ref_in << endl;
	
	// The last rotor
	int rot3_back_in =
	(((Reflector *)enigma_machine[part_count-1])->swap(ref_in)+(((Rotor *)enigma_machine[part_count-2])->get_position())-(((Reflector *)enigma_machine[part_count-1])->get_position()));
	rot3_back_in = fix_input(rot3_back_in);
	cout << "Rotor 3 is taking back in " << rot3_back_in << endl;
	
	// The rest of the rotors except the first
	int rotor_back_in = rot3_back_in;
	i = part_count-2;
	while(i > 2)
	{
		rotor_back_in =
		(((Rotor *)enigma_machine[i])->swap_rev(rotor_back_in)+(((Rotor *)enigma_machine[i-1])->get_position())-(((Rotor *)enigma_machine[i])->get_position()));
		rotor_back_in = fix_input(rotor_back_in);
		cout << "Rotor " << i << " is taking back in " << rotor_back_in << endl;
		cout << "i: " << i << endl;
		i = i-1;
	}
	
	// The first rotor
	int rot1_back_in =
	(((Rotor *)enigma_machine[2])->swap_rev(rotor_back_in)+(((Rotor *)enigma_machine[1])->get_position())-(((Rotor *)enigma_machine[2])->get_position()));
	rot1_back_in = fix_input(rot1_back_in);
	cout << "Rotor 1 is taking back in " << rot1_back_in << endl;
	
	// Plugboard
	int pb_back_in =
	(((Rotor *)enigma_machine[1])->swap_rev(rot1_back_in)+(((Plugboard *)enigma_machine[0])->get_position())-(((Rotor *)enigma_machine[1])->get_position()));
	pb_back_in = fix_input(pb_back_in);
	cout << "Plugboard is taking back in " << pb_back_in << endl;
	int pb_back_out = ((Plugboard *)enigma_machine[0])->swap(pb_back_in);
	char output = pb_back_out+65;
	cout << "The plugboard spit out " << pb_back_out << " (" << output << ")." << endl;
	
}

/*
./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos
*/

// Question: How do I get my parent classes to be able to call the child functions?

/* Four Rotors:
./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/IV.rot rotors/II.pos
*/