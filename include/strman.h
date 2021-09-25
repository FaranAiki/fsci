#ifndef NULL
	#include <string.h>
#endif 

/*
 * Non-memory allocated.
 */

// Make sure the "another" string's length is lower than the string's length
int strcomp(char *string, char *another) {
	while (another) {
		if (*(another++) != *(string++)) {
			return 0;
		}
	}

	return 1;
}

int strst(char *string, char *token) {
	int
		i = 0,
		tok_size = strlen(token) - 1;
	
	for (i = 0; i < tok_size; i++) {
		if (string[i] != token[i]) {
			return 0;
		}
	}

	return 1;
}

int strltrim(char *string, char *token) {
	int
		i = 0,
		tok_size = st
}
