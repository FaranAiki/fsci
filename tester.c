// Include standard library.
#include <stdio.h>
#include <stdlib.h>

// Include my include library.
#include "./include/strman.h"
#include "./include/datatypes.h"

int main() {
	char
		*y = strdup("A  ");

	strrtrim(y, " ");

	printf("%s", y);
	
	return 0;
}
