// Include standard library.
#include <stdio.h>
#include <stdlib.h>

// Include my include library.
#include "./include/strman.h"
#include "./include/datatypes.h"

int main() {
	table_int faran; table_init_int(&faran, 10, 10);
	int i;
	for (i = 0; i < 100000; i++) {
		table_add_int(&faran, i);
	}

	printf("%d", table_get_int(&faran, 2));
	
	return 0;
}
