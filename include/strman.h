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

	return (char*) (prev + cur); // Unnecessary casting, just a reminder.
}

/*
 * Memory allocated
 */

// Use 'strdup' to avoid segmentation fault!
char *strrtrim(char *string, const char *token) {
	char
		*prev = string + strlen(string) - 1;
	
	int
		i        = strlen(token) - 1, cur = 0,
		tok_size = i + 1;

	string = prev;

	while (*(string--) == token[i] || !token[i]) {
		if (!token[i]) {
			i    = tok_size;
			string++;
			
			cur += tok_size;

		}
		
		i--;
	}

	*(prev - cur + 1) = 0;
}
