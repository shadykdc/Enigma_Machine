// enigma: helper.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "classes.h"
#include "errors.h"
#include "helpers.h"
#include "checks.h"

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
	while (out_of_range(input)){
		input = set_in_range(input);}
	return(input);
}

int count_parts(int rotor_count)
{
	if(rotor_count > 0){
		return(rotor_count+2);}
	else {
		return(rotor_count+3);}
}
