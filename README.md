# Enigma_Machine
## Introduction
This is a working version of the enigma machine that Alan Turing famously decrypted.

The three folders (rotors, refletors, and plugboards) contain the configuration files for the physical parts of the enigma machine.

If you're not sure how the enigma machine works, check out this [video](https://www.youtube.com/watch?v=G2_Q9FoD-oQ).

main.cpp does a lot of the work and should be split up into multiple functions/files but...
I guess I didn't do that back when I wrote this code so I'm going to leave it that way for now...

## How To Try It:
 1. Download the folder or pull it.
 
 2. Go to the folder that contains the makefile and run make. (This doesn't work on my mac, unfortunately, but it works on my linux machines).
 
 3. Write in the command line something like:
```
./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/I.pos
```
 4. Type in a message and press enter, then an encrypted message will appear.
 
 5. Send that to your friend with the above configuration settings (or crtl+c / ctrl+d out and re-run the same prompt if you can't find any friends). Have your friend repeat the above steps but instead of writing a message, write the encrypted message and press enter.
 
 6. The decrypted message will appear!

For more information check out the [specification pdf](https://github.com/shadykdc/Enigma_Machine/blob/master/spec-550-2-0.pdf).
