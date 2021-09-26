#if (!defined(FSCI_VERSION) || !defined(FSCI_DISTRIBUTION) || !defined(FSCI_STABLE))
	#error("Must be one packet with \"main.c\".")
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

int eval(char *expr) {
	
}

int parse(char *cmd) {
	int
		dbquote, ssquote; // Necessary flag.
	
	char
		*temp = cmd;
	
	while (*(cmd++)) {
		if (*cmd == '\'') {
			ssquote = !ssquote;
		} else if (*cmd == '\"') {
			dbquote = !dbquote;
		}
	}
}

int syntax(char *syn) {
	if (strst(syn, "echo ")) {
		printf("%s", syn + 5);
	} else if (strcomp(syn, "exit")) {
		exit(EXIT_SUCCESS);
	} else if (1) {
		system(syn);
	}
}

// The shell itself.
int interactive() {
	char
		current_cmd[4096];

	table_string
		command_history;

	table_init_string(&command_history, 16, 8);
	
	while (1) {
		printf(">> ");
		
	}

	table_delete(command_history);
}
