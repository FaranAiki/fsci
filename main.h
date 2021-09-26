#if !defined(FSCI_VERSION) || !defined(FSCI_DISTRIBUTION || FSCI_STABLE)
	#error("Must be one packet with \"main.c\".")
#endif

// Expression, such as (1 + 2) or (1 - 2) is invoked through this function.
int eval(char *expr) {
	
}

// Command, such as "'Hello'.lowercase()".
int parse(char *cmd) {
	printf("%s", cmd);
}

// The shell itself.
int interactive() {

}
