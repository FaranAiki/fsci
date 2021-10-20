/*
 *	(C) Copyright 2021 Muhammad Faran Aiki.
 *
 *	FSCI stands for....
 * 		Faran/Fast (Far-Advanced) Shell/Standard/Scripting Command/Cool Interactive/Interpreter
 * 		[Forgot to fix it at GitHub, because the real acronym for "fsci" is "Faran Shell Command Interpreter"]
 *
 * 	By the way, I use arch... and geany... and C with C only (no C++).
 *
 *	Since this MUST support C++, I will cast the result of a malloc.
 *		Hence, maybe this work below C99.
 */

/*
 *	Always treat "sizeof" like a function (or macro)!
 */

#undef  FSCI_INTERPRETER

#define FSCI_INTERPRETER 1

// Include standard library.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include its reciprocal.
#include "./main.h"

extern table_pointer
	memory_pointer;

/*
 *  Use "strcomp" instead of "strcmp" to check whether or not two strings are equal.
 *  This is used due to speed and more customabilization.
 */

// The main itself is the-how the program runs and accept flags.
int main(int argc, char **argv) {
	char
		*arg_holder;   // This is a chord substitution, except it is an argument vector (and except it was a bad analogy), not a chord. 
	
	int
		interp = 1,
		in_arg = 0,    // This little variable is the reminder for the program to tell which flag is the last flag.
		i;             // This little guy is the variable substitution. You do not need this, apparently.

	// Initialization.
	atexit(interactive_quit);
	
	fsci_init();
	
	for (i = 1; i < argc; i++) {
		if (strst(argv[i], "-") || strst(argv[i], "/")) {
			in_arg = i;

			arg_holder = strltrim(strltrim(argv[i], "-"), "/");
			
			if (
				strcomp(arg_holder, "help") ||
				strcomp(arg_holder, "h") ||
				strcomp(arg_holder, "?")
			) {
				printf(fore_green "Here is your helper.\n" color_reset);
			}
		} else if (in_arg) {
			arg_holder = strltrim(strltrim(argv[in_arg], "-"), "/");
			
			if (
				strcomp(arg_holder, "e") || strcomp(arg_holder, "exec") || strcomp(arg_holder, "execute") ||
				strcomp(arg_holder, "do") 
			) {
				interp = 0;
				fsci_parse(argv[i]);
			}
			
			in_arg = 0;
		} // if 
	} // for
	
	if (interp) {
		interactive();
	} // interp
	
	return EXIT_SUCCESS; // Trying to be careful.
} // main
