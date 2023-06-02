#Deterministic Finite Automaton#
- This program simulates a deterministic finite automaton. A .txt file is asked
as an argument for the execution of the program; it is supposed that in this
file is contained the information for the construction of the automaton.

- While running, the program will ask for strings to validate, displaying
*"Accepted string"* is the introduced string belongs to the language, and
*"String not accepted"* if not.

- To exit the program press *ctrl+C*.

- When running the program, please be careful; a lot of work needs to be done
  to handle exceptions.

#Compile the program#
In console just type "make" and the executable will be created. If you want
to modify something about the compilation process you can modify the 
*Makefile* file.

#Run the program#
You can either run the command *"./DFA DFA.txt"* or *"make run"*.

#Input file#
The file *DFA.txt* contains the necessary and sufficient information to run
the program. To input the automaton of you desire modify this file as 
indicated in this same file.
