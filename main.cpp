//	Integrated Programming Laboratory
//	Exercise 2, The Enigma Machine
//	Kathryn Shea, November 23, 2015

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
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
	if(rotor_count > 0){
		return(rotor_count+2);}
	else {
		return(rotor_count+3);}
}

int main(int argc, char **argv)
{
	/* count how many parts and rotors there are */
	int rotor_count = argc-4;
	int part_count = count_parts(rotor_count);
	//if (rotor_count > 0){cout << "There are " << rotor_count << " rotors." << endl;}
	//else {cout << "There are 0 rotors." << endl;}
	
	/* create plugboard and reflector */
	Plugboard pb;
	ifstream ins;
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
	
	/* Create Rotors */
	if (rotor_count > 0)
	{
		for (int i = 0; i < rotor_count; i++)
		{
			ins.open(argv[part_count-i]);
			(rotors[i])->assign_values(ins);
			ins.close();
		}
	}
	
	/* Import rotor positions */
	ins.open(argv[part_count+1]);
	int num;
	int i = 0;
	while (i < rotor_count && ins >> ws >> num){
		rotors[i]->assign_position(num);
		i++;
		//cout << "Rotor " << i << " has a position of " << rotors[i-1]->get_position() << endl;
	}
	ins.close();
		
	// Input from user
	//cout << endl << "Enter a message of capital letters: ";
	char input = cin.get();
	//cout << endl;
	while(input != '\n')
	{
	int enigma_in = input - 65;
	cout << endl << input << " = " << enigma_in << " is coming in." << endl << endl;
	
	// Rotations
	rotors[0]->rotate();
	cout << "Rotor 1 rotated.  It has rotated "
		<< rotors[0]->get_rotations() << " time(s) and is currently at position "
		<< rotors[0]->get_position() << "." << endl;
	
	for (int i = 0; i < rotor_count-1; i++){
	//	if this rotor has a notch at the current position, rotate the next 1.
		if(rotors[i]->is_a_notch(rotors[i]->get_position())){
			rotors[i+1]->rotate();
			cout << "Rotor #" << i+2 << " rotated because Rotor #" << i+1 << " has a notch in position " << rotors[i]->get_position() << "." << endl;
		}
	//	if a rotor rotates and has A at the top, rotate the next 1.
		if((rotors[i]->get_rotations() > 0) &&
		(rotors[i]->get_position() == 0)){
			rotors[i+1]->rotate();
			cout << "Rotor #" << i+2 << " rotated because Rotor #" << i+1 << " is in position " << rotors[i]->get_position() << "." << endl;
		}
	}

	// Plugboard
	int rotor_in = pb.swap(enigma_in);
	cout << "The plugboard is swapping " << enigma_in << " for " << rotor_in << "." << endl;
	
	// Rotors
	rotor_in = rotor_in + rotors[0]->get_position();
	rotor_in = fix_input(rotor_in);
	cout << "Rotor 1 is swapping " << rotor_in;
	rotor_in = rotors[0]->swap_fwd(rotor_in);
	cout << " for " << rotor_in << "." << endl;
	for(int i = 1; i < rotor_count; i++)
	{
		rotor_in =	rotor_in +
					rotors[i]->get_position() -
					rotors[i-1]->get_position();
		cout << "Rotor " << i+1 << " is swapping " << rotor_in;
		rotor_in = fix_input(rotor_in);
		rotor_in = rotors[i]->swap_fwd(rotor_in);
		cout << " for " << rotor_in << "." << endl;
	}
	
	// Reflector
	cout << "Reflector is swapping " << rotor_in;
	rotor_in = rotor_in - rotors[rotor_count-1]->get_position();
	rotor_in = fix_input(rotor_in);
	int rotor_out = ref.swap(rotor_in) + rotors[rotor_count-1]->get_position();
	rotor_out = fix_input(rotor_out);
	cout << " for " << rotor_out << "." << endl;
	
	// Rotors in reverse
	for(int i = rotor_count-1; i > 0; i--)
	{
		cout << "Rotor " << i+1 << " is swapping " << rotor_out;
		rotor_out = rotors[i]->swap_rev(rotor_out) -
					rotors[i]->get_position() +
					rotors[i-1]->get_position();
		rotor_out = fix_input(rotor_out);
		cout << " for " << rotor_out << "." << endl;
	}
	cout << "Rotor " << 1 << " is swapping " << rotor_out;
	rotor_out = rotors[0]->swap_rev(rotor_out) - rotors[0]->get_position();
	rotor_out = fix_input(rotor_out);
	cout << " for " << rotors[0]->swap_rev(rotor_out) << "." << endl;
	
	// Plugboard
	cout << "The plugboard is swapping " << rotor_out;
	rotor_out = pb.swap(rotor_out);
	cout << " for " << rotor_out << "." << endl;
	rotor_out = fix_input(rotor_out);
	char output = rotor_out+65;
	cout << endl << "Final product: " << output << endl << endl;
	//cout << output;
	
	input = cin.get();
	}
	cout << endl << endl;
}


/*
./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos
*/