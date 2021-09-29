// Include standard library.
#include <stdio.h>
#include <stdlib.h>

// Include my include library.
#include "./include/strman.h"
#include "./include/datatypes.h"

int main() {
	char t[4096];

	while (1) {
		while (fgets(t, 4096, stdin))
			printf("%s", t);
	}
	
	return 0;
}
