# Hash Dictionary Auto-Correct
# Author: Ryan Rosiak
<br /> <br />
## Project Description:
This project demonstrates the basic functionality of the multiplication hash function.
This program takes in file of words and hashes them out using a modified multiplication
hashing function. All these words are then used as suggested word edits for a 
sentence that is input by the user. The sentence is corrected and then some 
statistics are posted afterwards.
<br /> <br />
## Files to pay attention to:
* main.o HashList.o, Dictionary.o - These are the compilation linker files
* hashdict - Output file that is run when the program is executed by the user
* Makefile - File that allows the user to compile without having to input specific commands
* english.txt - Sample dictionary file with a large amount of words, any text file dictionary can work
<br /> <br />
## Makefile Instructions:
Type "make" without the quotes and the program will compile everything for you. Then
proceed with using ./main in order to run the program.
<br /> <br />
## Instructions for Program:
Follow the Makefile instructions above to run the program without any manual work. If 
not using Makefile, then you must compile the .cpp files into .o files. 
(g++ -c main.cpp) Then you mus tlink those with a final compilation all while labeling
the output file as hashdict.
**You must use -std=c++11 within your compilation steps**
**Example english.txt file needs specific format**
<br /> <br />
## english.txt Format:
*START OF FILE*\
word1\
word2\
...\
wordn\
*END OF FILE*\
**Formated one word a line and hyphens between words that must be separated**
