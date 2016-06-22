# Enigma_Machine
A working version of the enigma machine that Alan Turing managed to decrypt.

The three folders (rotors, refletors, and plugboards) contain the configuration files for the physical parts of the enigma machine.

If you're not sure how the enigma machine works, check out this [video](https://www.youtube.com/watch?v=G2_Q9FoD-oQ).

main.cpp does a lot of the work and should be split up into multiple functions but...
I guess I didn't do that back when I wrote this code so I'm going to leave it that way for now...

To try out this program, pull the code and run make in the folder with the make file.

Then write in the command line something like:

./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos

Type in a message and then send the garbled output to your friend with the above configuration settings.

If your friend then pulls the code, uses these configuration settings, and puts that garbled message in,
then your original message will appear!

For more information check out the specification pdf.
