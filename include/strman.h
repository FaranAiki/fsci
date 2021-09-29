#include <string.h>

/*
 * Non-memory allocated.
 */

// Make sure the "another" string's length is lower than the string's length.
int strcomp(const char *string, const char *another) {
	while (*another || *string) {
		if (*(another++) != *(string++)) {
			return 0;
		}
	}

	return 1;
}

// Check whether or not if the string starts with token.
int strst(const char *string, const char *token) {
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

char *strltrim(const char *string, const char *token) {
	const char
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

	return (char*) prev + cur;
}

/*
 * Memory allocated
 */

// Use 'strdup' to avoid segmentation fault!
char *strrtrim(const char *string, const char *token) {
	const char
		*prev = string + strlen(string);
	
	int
		i        = strlen(token), cur = 0,
		tok_size = i;

	string = prev;

	while (*(string--) == token[i] || !token[i]) {
		if (!token[i]) {
			i    = -1;
			string--;
			
			cur += tok_size;
		}
		
		i++;
	}

	return (char*) prev - cur;
}
