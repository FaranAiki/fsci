// Include standard library.
#include <stdio.h>
#include <stdlib.h>

// Include my include library.
#include "./include/strman.h"
#include "./include/datatypes.h"

int main() {
	char
		*y = strdup("1x2xxxxx");

	strrtrim(y, "x");

	printf("%s\n", y);
	
	return 0;
}
