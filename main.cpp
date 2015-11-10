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
	if (rotor_count > 0){cout << "There are " << rotor_count << " rotors." << endl;}
	else {cout << "There are 0 rotors." << endl;}
	
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
	}
	ins.close();
		
	// Input from user
	cout << endl << "Enter a message of capital letters: ";
	char input = cin.get();
	cout << endl;
	while(input != '\n')
	{
	int enigma_in = input - 65;
	cout << input << " aka " << enigma_in << " is coming in." << endl;
	
	// Rotations
	rotors[0]->rotate(); // rotor 1 is hitting 0 and not rotation the next one
	cout << "Rotor 1 rotated.  It's position is " << rotors[0]->get_position() << endl;
	for (int i = 0; i < rotor_count; i++)
	{
		if(rotors[i]->get_position() == 0 && rotors[i]->get_rotations() != 0 &&
		i < rotor_count-1)
		{
			rotors[i+1]->rotate();
		}
		if(rotors[i]->get_notch() == rotors[i]->get_position()){
			rotors[i]->rotate();
			if(rotors[i]->get_position() == 0 && i != rotor_count-1){
				rotors[i+1]->rotate();
				cout << endl << "Rotor #" << i+2 << " rotated because Rotor #"
				<< i+1 << " hit A." << endl;
			}
			cout << "Rotor #" << i+1 << " rotated because it has a notch at "
			<< rotors[i]->get_notch() << endl;
		}
	}
	
	// Plugboard
	int rotor_in = pb.swap(enigma_in);
	rotor_in = fix_input(rotor_in);
	cout << "The plugboard spit out " << rotor_in << "." << endl;
	
	// Rotors
	rotor_in = rotor_in + rotors[0]->get_position();
	rotor_in = fix_input(rotor_in);
	rotor_in = rotors[0]->swap_fwd(rotor_in);
	rotor_in = fix_input(rotor_in);
	cout << "Rotor 1 spit out " << rotor_in << endl;
	for(int i = 1; i < rotor_count; i++)
	{
		rotor_in =	rotor_in +
					rotors[i]->get_position() -
					rotors[i-1]->get_position();
		rotor_in = fix_input(rotor_in);
		rotor_in = rotors[i]->swap_fwd(rotor_in);

		cout << "Rotor " << i+1 << " spit out " << rotor_in << endl;
	}
	
	// Reflector
	int rotor_out = ref.swap(rotor_in) + rotors[rotor_count-1]->get_position();
	rotor_out = fix_input(rotor_out);
	cout << "Reflector spit out " << rotor_out << endl;
	
	// Rotors in reverse
	for(int i = rotor_count-1; i > 0; i--)
	{
		rotor_out = rotors[i]->swap_rev(rotor_out) -
					rotors[i]->get_position() +
					rotors[i-1]->get_position();
		rotor_out = fix_input(rotor_out);
		cout << "Rotor " << i+1 << " spit out " << rotor_out << endl;
	}
	rotor_out = rotors[0]->swap_rev(rotor_out) - rotors[0]->get_position();
	rotor_out = fix_input(rotor_out);
	cout << "Rotor " << 1 << " spit out " << rotor_out << endl;
	
	// Plugboard
	rotor_out = pb.swap(rotor_out);
	rotor_out = fix_input(rotor_out);
	char output = rotor_out+65;
	cout << "Final product: " << output << endl;
	//cout << output;
	
	input = cin.get();
	}
	cout << endl << endl;
}


/*
./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos
*/