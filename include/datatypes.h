/*
 *	(C) Copyright 2021 Muhammad Faran Aiki.
 *
 * 	This is somehow... not efficient.
 */

enum {
	INTEGER  = 1,
	STRING   = 2,
	DOUBLE   = 3,
	TABLE    = 4,
	HASH     = 5,
	POINTER  = 6,
};

// Table data type.
typedef struct _table {
	unsigned int
		size,       // The current size of array (by malloc).
		current,    // The current allocated memory in the table.
		multiplier; // Each time, the size is multiplied if and only if current > size.

	void
		**item;

	int
		*type;
} table, Table;

// Usage: table_init(&memory, 3, 10);
void table_init(table *tab, int initial_size, int multiplier) {
	
}

// Usage: table_add(&memory, non_heap_memory, 2); beware, that this only works if you understand C.
void table_add(table *tab, void *item, int type) {

}

void table_add_str(table *tab, char *item) {

}

void table_add_int(table *tab, int *item) {

}

void table_add_double(table *tab, double *item) {

}

void table_add_array(table *tab, table item) {

}

void table_add_pointer(table *tab, void *item) {

}

void table_get(table *tab, int index) {
	
}

// Hash data type.
typedef struct _hash {
	unsigned int
		max,
		key;

	table
		item;

	int
		*type;
} hash, Hash;

void hash_init(hash *dict, int initial_size, int multiplier, int key) {

}

void hash_key(void *item, int type) {
	
}

/*
 *	Avoid conflicting.
 */

void table_add_hash(table *tab, hash item) {

}
