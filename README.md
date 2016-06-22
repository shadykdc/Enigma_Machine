# Enigma_Machine
A working version of the enigma machine that Alan Turing managed to decrypt.

The three folders (rotors, refletors, and plugboards) contain the configuration files for the physical parts of the enigma machine.

If you're not sure how the enigma machine works, check out this [video](https://www.youtube.com/watch?v=G2_Q9FoD-oQ).

main.cpp does a lot of the work and should be split up into multiple functions but...
I guess I didn't do that back when I wrote this code so I'm going to leave it that way for now...

To try out this program, pull the code and run make in the folder with the make file.

Then write in the command line something like:

    ./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos

Type in a message and an encrypted message will appear. Send that to your friend with the above configuration settings.

Have your friend pull the code, use these configuration settings, and put that encrypted message in.

Then the enigma machine will decrypt the message!

For more information check out the [specification pdf](https://github.com/shadykdc/Enigma_Machine/blob/master/spec-550-2-0.pdf).
