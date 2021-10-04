/*
 *	(C) Copyright 2021 Muhammad Faran Aiki.
 *
 *	FSCI is a beginner-type of interpreter (I am not a beginner, because I am not a programmer).
 *		This does not uses a third-party library except for FSCI itself.
 * 
 *	This is importable to C++.
 *
 * 	Still a little amount of comment, too lazy to write it. Maybe next time, on Dragon Ball Z.
 *
 */

/*
 *	"prefix_string" is slower than a normal string,
 *		it exists just to serve for a non-null string.
 *
 */

// Undefine for safety purposes.
#undef  FSCI_VERSION
#undef  FSCI_DISTRIBUTION
#undef  FSCI_STABLE
#undef  FSCI_CPP_SUPPORT

// Define, well, this is a little bit boring....
#define FSCI_VERSION      0.01
#define FSCI_DISTRIBUTION "Faran"
#define FSCI_STABLE       0        // 0 For false, 1 for true.
#define FSCI_CPP_SUPPORT  1        // 0 For false, 1 for true.

#if defined(__cplusplus)
	#if !FSCI_CPP_SUPPORT
		#error("Trying to compile a C-only supported version of the code with C++ compiler is no good. Current version '" # FSCI_VERSION # "' is not supported for C++. Contact the developer for more information.")
	#endif
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "./include/strman.h"
#include "./include/datatypes.h"
#include "./include/color.h"
#include "./include/cross-platform.h"

#pragma once

table_pointer
	memory_pointer;

// Still not at its perfect form.
int fsci_print_type(void *obj, int type) {
	char
		*s_temp, *ps_temp;
	
	int
		i_temp = 0, len = 0,
		i;

	switch (type) {
		case type_int:
			i_temp  = *(int*) obj;
			len     = intlen(i_temp) << 1;
			
			s_temp  = (char*) malloc(len * sizeof(*s_temp)); // Unnecessary cast.
			ps_temp = s_temp;

			i = 0;
			
			sprintf(s_temp, "%d", i_temp);
			
			while (*s_temp) {
				putchar(*(s_temp++));
				
				if (i++ > 1) {
					i = 0;
					putchar(' ');
				}
			}

			free(ps_temp);
			
			break;
		case type_string:
			printf("\"%s\"", (char*) obj);
			break;
		case type_prefix_string:
			fwrite((*(prefix_string*) obj).data, sizeof(char), (*(prefix_string*) obj).size, stdout); // Redundancy is good.
			break;
		case type_file:
			printf("<File with Memory '%p'>", *(FILE**) obj);
			break;
		case type_process:
			printf("<Process with Memory '%p'>", *(FILE**) obj);
			break;
		default:
			printf("<Unknown Type Symbol: '%d'>", type);
			break;
	}
	
	return 0;
}

int fsci_print_result(void) {
	int
		i;

	putchar('\n');
	
	if (memory_pointer.current == 1) {
		fsci_print_type(table_get_pointer(&memory_pointer, 0), memory_pointer.type[0]); putchar('\n');
	} else if (memory_pointer.current > 1) {
		putchar('(');
		
		for (i = 0; i < memory_pointer.current - 1; i++) {
			fsci_print_type(table_get_pointer(&memory_pointer, i), memory_pointer.type[i]);
			putchar(','); putchar(' ');
		}

		fsci_print_type(table_get_pointer(&memory_pointer, i), memory_pointer.type[i]);
		
		putchar(')'); putchar('\n');
	}
	
	return 0;
}

int fsci_lazy_eval(char *expr) { // Misnorming.
	char
		*temp = expr;
	
	prefix_string
		pfst;

	expr = strltrim(expr, " ");
	       strrtrim(expr, " ");

	if ( // Strings
		((expr[strlen(expr) - 1] == '"')  && (expr[0] == '"')) ||
		((expr[strlen(expr) - 1] == '\'') && (expr[0] == '\''))
	) {
		expr++;
		expr[strlen(expr) - 1] = 0;

		table_push_pointer(&memory_pointer, strdup(expr), type_string);
	} else if ( // Dynamic string
		((expr[strlen(expr) - 1] == '`')  && (expr[0] == '`'))
	) { 
		expr++;
		expr[strlen(expr) - 1] = 0;
		
		prefix_string_init(&pfst, expr, strlen(expr));
		
		table_push_pointer(&memory_pointer, &pfst, type_prefix_string);
	} else if (
		is_valid_int(expr)
	) {
		table_push_pointer(&memory_pointer, intdup(parse_int(expr)), type_int);
	}
	
	return 0;
} // fsci_lazy_eval(char *expr)

int fsci_eval(char *expr) {
	int
		repeato = 0, needlazy = 1,
		dbquote = 0, ssquote  = 0,
		parenth = 0;

	char
		*temp = expr;
	
	while (*expr) {
		if (*expr == '\'') {
			ssquote = !ssquote;
		} else if (*expr == '\"') {
			dbquote = !dbquote;
		} else if (*expr == '(') {
			parenth++;
		} else if (*expr == ')') {
			parenth--;
		} else if (!parenth && !dbquote && !ssquote) {
			switch (*expr) {
				case ',': case ' ':
					*expr  = 0;

					fsci_eval(temp + repeato);
					
					repeato  = (int) (expr - temp + 1);
					needlazy = 0;
					
					break;
			}
		}
		
		expr++;
	}
	
	if (needlazy) {
		fsci_lazy_eval(temp);
	} else {
		fsci_eval(temp + repeato);
	}
	
	return 0;
}

int fsci_syntax(char *syn) {
	char
		*temp,
		*n_temp;
	
	int
		i,
		type, size;
	
	prefix_string
		*pfst;
	
	if (strst(syn, "echo")) {
		for (i = 0; i < memory_pointer.current; i++) {
			type = memory_pointer.type[i];
			
			switch (type) {
				case type_string:
					printf("%s ", (char*) table_get_pointer(&memory_pointer, i));
					break;
				case type_int:
					printf("%d ", *(int*) table_get_pointer(&memory_pointer, i));
					break;
				case type_float: case type_double:
					printf("%lf ", *(double*) table_get_pointer(&memory_pointer, i));
					break;
			}
		}
	} else if (strcomp(syn, "exit")) {
		exit(EXIT_SUCCESS);
	} else if (strst(syn, "!") || strst(syn, "system")) { // You can use "realloc", but I will not.
		size = 0;
		
		for (i = 0; i < memory_pointer.current; i++) {
			switch (memory_pointer.type[i]) {
				case type_string:
					size += strlen((char*) table_get_pointer(&memory_pointer, i)) + 4;
					break;
				case type_prefix_string:
					size += (*(prefix_string*) table_get_pointer(&memory_pointer, i)).size + 4;
					break;
				case type_int:
					size += intlen(*(int*) table_get_pointer(&memory_pointer, i)) + 4;
					break;
				case type_float:
					break;
			}
		}
		
		temp   = (char*) malloc((size + 1) * sizeof(*temp));
		n_temp = (char*) malloc((size + 1) * sizeof(*n_temp));
		
		// Still uses "snprintf", even if we are safe, we are not!
		for (i = 0; i < memory_pointer.current; i++) {
			strcpy(n_temp, temp);
			
			switch (memory_pointer.type[i]) {
				case type_string:
					snprintf(temp, size, "%s '%s'", n_temp, (char*) table_get_pointer(&memory_pointer, i));
					break;
				case type_prefix_string:
					pfst = (prefix_string*) table_get_pointer(&memory_pointer, i); // Unnecessary cast.
					
					if (prefix_string_check_null(pfst)) {
						// Do if there is a zero character.
					} else {
						snprintf(temp, size, "%s '%s'", n_temp, pfst->data);
					}
					
					break;
				case type_int:
					snprintf(temp, size, "%s '%d'", n_temp, *(int*) table_get_pointer(&memory_pointer, i));
					break;
				case type_float:
					break;
			}
		}

		memory_pointer.current = 0;
		
		table_push_pointer(&memory_pointer, intdup(system(temp)), type_int);
		
		free(n_temp);
		free(temp);
	}
	
	return 0;
} // fsci_syntax(char *syn)

// Messing with the memory pointer table.
int fsci_expr(char *expr) {
	int
		dbquote = 0, ssquote  = 0,
		parenth = 0, fparenth = 0; // Necessary flag.

	char
		*prev = expr;

	while (*expr) {
		if (*expr == '\'') {
			ssquote = !ssquote;
		} else if (*expr == '\"') {
			dbquote = !dbquote;
		} else if (*expr == '(') {
			fparenth = (int) (expr - prev);
			
			parenth++;
		} else if (*expr == ')') {
			parenth--;
			
			if (!parenth && fparenth) {
				memory_pointer.current = 0;
				memory_pointer.current    = 0;
				
				expr[0] = 0;
				fsci_eval(prev + fparenth + 1);
				
				prev[fparenth] = 0;
				fsci_syntax(prev);
			}

			return 0;
		}

		expr++;
	}

	fsci_syntax(prev);

	return 0;
}

// Parse like + or - operator.
int fsci_parse(char *cmd_ndup) {
	int
		dbquote, ssquote,
		parenth; // Necessary flag.
	
	char
		*cmd  = strdup(cmd_ndup),
		*temp = cmd,
		*tmp  = cmd;
	
	while (*cmd) {
		if (*cmd == '\'') {
			ssquote = !ssquote;
		} else if (*cmd == '\"') {
			dbquote = !dbquote;
		} else if (*cmd == '(') {
			parenth++;
		} else if (*cmd == ')') {
			parenth--;
		} else if (!parenth && !dbquote && !ssquote) {
			
		}
		
		cmd++;
	}

	fsci_expr(temp);

	fsci_print_result();
	
	free(tmp);
	
	return 0;
} // fsci_parse(char *cmd_ndup)

void fsci_atexit(void) {
	table_delete_pointer(&memory_pointer);
} // fsci_atexit(void)

int fsci_init(void) {
	if (!(table_init_pointer(&memory_pointer, 128, 4))) {
		atexit(fsci_atexit);

		return 0;
	}

	return 1;
} // fsci_init(void)
