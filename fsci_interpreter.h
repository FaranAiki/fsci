table_pointer
	memory_pointer;

table_int
	memory_type;

int fsci_eval(char *expr_ndup) {
	char
		*expr = strdup(expr_ndup);

	expr = strltrim(expr, " ");
	       strrtrim(expr, " ");
	
	free(expr);
	
	return 0;
}

int fsci_parse(char *cmd) {
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

	return fsci_eval(cmd);
}

int fsci_syntax(char *syn) {
	if (strst(syn, "echo ")) {
		printf("%s\n", syn + 5);
	} else if (strcomp(syn, "exit")) {
		exit(EXIT_SUCCESS);
	} else if (!fsci_parse(syn)) {
		
	} else if (1) {
		system(syn);
	}

	return 0;
}
