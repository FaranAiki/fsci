/*
 *	(C) Copyright 2021 Muhammad Faran Aiki.
 *
 *	FSCI stands for....
 * 		Faran/Fast (Far-Advanced) Shell/Standard/Scripting Command/Cool Interactive/Interpreter
 * 		[Forgot to fix it at GitHub, because the real acronym for "fsci" is "Faran Shell Command Interpreter"]
 *
 * 	By the way, I use arch... and geany... and C with C only (no C++).
 *
 *	Since this does not support C++, I will not cast the result of malloc.
 *		Hence, the required minimum C version is C99.
 */

// Define, well, this is a little bit boring....
#define FSCI_VERSION      0.01
#define FSCI_DISTRIBUTION "Faran"
#define FSCI_STABLE       0        // 0 For false, 1 for true.

// Include standard library.
#include <stdio.h>
#include <stdlib.h>

// Include my include library.
#include "./include/strman.h"
#include "./include/datatypes.h"

// Include its reciprocal.
#include "./main.h"

table_pointer
	memory_pointer;

/*
 *  Use "strcomp" instead of "strcmp".
 *  This is used due to speed and more customabilization.
 */

// The main itself is the-how the program runs and accept flags.
int main(int argc, char **argv) {
	char
		*arg_holder;   // This is a chord substitution, except it is an argument vector (and except it was a bad analogy), not a chord. 
	
	int
		in_arg = 0,    // This little variable is the reminder for the program to tell which flag is the last flag.
		i;             // This little guy is the variable substitution. You do not need this, apparently.

	// Initialization
	atexit(fsci_quit);
	
	table_init_pointer(&memory_pointer, 128, 4);
	
	for (i = 1; i < argc; i++) {
		if (strst(argv[i], "-") || strst(argv[i], "/")) {
			in_arg = i;

			arg_holder = strltrim(strltrim(argv[i], "-"), "/");
			
			if (
				strcomp(arg_holder, "help") ||
				strcomp(arg_holder, "h") ||
				strcomp(arg_holder, "?")
			) {
				printf("Here is your helper.\n");
			}
		} else if (in_arg) {
			arg_holder = strltrim(strltrim(argv[in_arg], "-"), "/");
			
			if (
				strcomp(arg_holder, "e") || strcomp(arg_holder, "exec") || strcomp(arg_holder, "execute") ||
				strcomp(arg_holder, "do") 
			) {
				syntax(argv[i]);
			}
			
			in_arg = 0;
		} // if 
	} // for

	interactive();
	
	return EXIT_SUCCESS; // Trying to be careful.
} // main
