#if !defined(NULL)
	#include <string.h>
#endif

#include <ctype.h>

#pragma once

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
int strrtrim(char *string, const char *token) {
	char
		*prev = string + strlen(string) - 1;
	
	int
		tok_size = strlen(token),
		i        = 0, cur = 0;

	string = prev;
	
	while (tok_size == i || *(string--) == token[tok_size - i - 1]) {
		if (i == tok_size) {
			i    = -1;
			
			cur += tok_size;
		}
		
		i++;
	}

	*(prev - cur + 1) = 0;

	return 0;
}

// Non-string related, but still related to string.
int itoa10(int digit, char *string) {
	int
		prev,
		current = 0;
	
	while (!digit) {
		prev = digit;
		digit = (int) (digit / 10); // Unnecessary cast for the compiler, but not for me.

		string[current++] = prev - (digit >> 3) + (digit >> 1); // I do not believe in compiler optimization, equivalent to prev - digit * 10;
	}

	string[current] = 0;
	
	return current;
}

// Integer

int intlen(int digit) {
	int
		current = 0;

	while (digit) {
		current++;

		digit = (int) (digit / 10); // Unnecessary casting for the compiler, but not for me.
	}

	return current;
}

// Is validate.

int is_valid_int(char *string) {
	int
		signess_allowed = 1;

	if (!(*string)) {
		return 0;
	}
	
	while (*string) {
		if ((*string - '0') < 10 && (*string - '0') >= 0) {
			signess_allowed = 0;
		} else {
			switch (*string) {
				case '_': case ' ':
					break;
				case '-': case '+':
					if (!signess_allowed) {
						return 0;
					}
					
					break;
				default:
					return 0;
			}
		}

		string++;
	}

	return 1;
}

int is_valid_float(char *string) {
	int
		signess_allowed = 1,
		already_dot     = 0;

	if (!(*string)) {
		return 0;
	}
	
	while (*string) {
		if (isdigit(*string) || (*(string + 1) == 0 && *string == 'f')) {
			signess_allowed = 0;
		} else {
			switch (*string) {
				case '.':
					if (already_dot) {
						return 0;
					} else {
						already_dot = 1;
					}

					break;
				case '-': case '+':
					if (!signess_allowed) {
						return 0;
					}

					break;
				default:
					return 0;
			}
		}

		string++;
	}

	return 1;
}

// Converting into integer

int parse_int(char *string) {
	int
		signess_allowed = 1,
		current = 0,
		sign    = 0;
	
	while (*string) {
		if ((*string - '0') >= 0 && (*string - '0') < 10) {
			current = (current << 3) + (current << 1);
			current += *string - '0';
		} else {
			switch (*string) {
				case '_':
					break;
				case '-':
					sign = !sign;
					break;
				case '+': case ' ':
					break;
				default:
					return 0;
			}
		}

		string++;
	}

	return current;
}

// Duplication

int *intdup(int digit) {
	int
		*temp = (int*) malloc(1 * sizeof(*temp)); // Unnecessary cast, but not for me.

	*temp = digit;
	
	return temp;
}

FILE **filedup(FILE* file) {
	FILE
		**temp = (FILE**) malloc(1 * sizeof(*file));

	*temp = file;

	return temp;
}
