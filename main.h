#if (!defined(FSCI_VERSION) || !defined(FSCI_DISTRIBUTION) || !defined(FSCI_STABLE))
	#error("Must be one packet with \"main.c\".")
#endif

#if !defined(FSCI_INTERPRETER)
	#include "fsci_interpreter.h"
#endif

/*
 *	Precendeces:
 *		**
 *		/ //
 */

// Global variables
extern table_pointer
		memory_pointer;

void fsci_quit() {
	table_delete_pointer(&memory_pointer);

	exit(EXIT_SUCCESS);
}

int prompt_add(const char *__restrict string, int *current_index, int *length_cmd, char *current_cmd) {
	(*current_index) += strlen(string);
	(*length_cmd)    += strlen(string);

	strcpy(current_cmd, string);

	printf("%s", string);
	
	return 0;
}

// Warning ahead: Segmentation fault still exists. Sorry, I got homework to do.

// The shell itself.
int interactive(void) {
	int
		current_history,
		current_index, length_cmd,
		i,
		is_arrow, is_insert = 0;
	
	char
		current_char,
		current_cmd[4096];

	init_termios();
	atexit(atexit_termios);

	table_string
		command_history;

	table_init_string(&command_history, 16, 8);

	printf(bright fore_green "FSCI version 0.01 (unstable).\n");
	printf("Type \"help\" or \"?\" for more information.\n" color_reset);

	current_history = 0;
	
	while (1) {
		current_index = 0, length_cmd = 0;
		is_arrow = 0;

		memset(current_cmd, 0, 4096 * sizeof(current_cmd[0]));
		
		printf(bright fore_cyan ">> " color_reset);
		
		while ((current_char = getch()) != '\n' && current_index < 4095) {
			if (is_arrow && current_char != '[') {
				switch (current_char) {
					case 'A': // up
						if (current_history) {
							for (i = 0; i < length_cmd; i++) {
								printf("\b \b");
							}
							
							prompt_add(table_get_string(&command_history, --current_history), &current_index, &length_cmd, current_cmd);
						} else {
							putchar(7);
						}
						
						break;
					case 'B': // down
						if (current_history < memory_pointer.current) {
							for (i = 0; i < length_cmd; i++) {
								printf("\b \b");
							}
							
							prompt_add(table_get_string(&command_history, ++current_history), &current_index, &length_cmd, current_cmd);
						} else {
							putchar(7);
						}
						
						break;
					case 'C': // right
						if (current_index != length_cmd) {
							current_index++;
							printf("\33[C");
						} else {
							putchar(7);
						}
						
						break;
					case 'D': // left
						if (current_index) {
							current_index--;
							printf("\33[D");
						} else {
							putchar(7);
						}
						
						break;
					case '~':
						printf("EHHH");
						break;
				}

				is_arrow = 0;
			} else if (is_arrow) {
				
			} else {
				switch (current_char) {
					case '\033':  // for arrow
						is_arrow = 1;
						break;
					case 127:     // backspace
						if (current_index != 0) {
							printf("\b \b");

							current_cmd[current_index--] = 0;
							length_cmd--;
						} else {
							putchar(7);
						}
						
						break;
					default:
						putchar(current_char);
						current_cmd[current_index++] = current_char;
						
						length_cmd++;
						break;
				}
			}
		}
		
		putchar('\n');

		if (*current_cmd == '\n' || *current_cmd) {
			fsci_syntax(current_cmd);

			if (!table_push_string(&command_history, strdup(current_cmd))) {
				current_history = command_history.current;
			}
		}
		
		current_cmd[length_cmd] = 0;
	}

	return 0;
} // interactive
