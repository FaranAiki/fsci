#include <string.h>

/*
 * Non-memory allocated.
 */

// Make sure the "another" string's length is lower than the string's length.
int strcomp(char *string, char *another) {
	while (*another || *string) {
		if (*(another++) != *(string++)) {
			return 0;
		}
	}

	return 1;
}

// Check whether or not if the string starts with token.
int strst(char *string, char *token) {
	int
		i,
		tok_size = strlen(token);
	
	for (i = 0; i < tok_size; i++) {
		if (string[i] != token[i]) {
			return 0;
		}
	}

	return 1;
}

char *strltrim(char *string, char *token) {
	char
		*prev = string;

	int
		i        = 0, cur = 0,
		tok_size = strlen(token);

	while (*(string++) == token[i] || !token[i]) {
		if (!token[i]) {
			i    = -1;
			string--;
			
			cur += tok_size;
		}
		
		i++;
	}

	return prev + cur;
}

/*
 * Memory allocated
 */
