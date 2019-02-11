# CS-288_Programs
A respository containing all of the programs I wrote for my Intensive Programming in Linux course in college.

PROGRAMS:
mastermind.c - A C90 program written to play the game Mastermind against a human opponent. The program takes the code to be guessed as a command-line arguement and uses only standard input and output to communicate with the player. The player recieves feedback in the form of two integers, the first representing the number of colors in the code they have guessed the positions of correctly, and the second being the number of colors in the code whose position they have guessed incorrectly. The player is given 12 attempts to successfully guess the code; when the player either guesses the code correctly or runs out of attempts, the game returns an appropriate message and quits.

SET.c - Another C90 program that implements a mathematical set as a linked list struct. Includes set operations such as intersection, union, difference, cardinality, as well as traversal and modification methods such as search, push, delete, etc. Also includes a test section in main() to test the functionality of the program.
