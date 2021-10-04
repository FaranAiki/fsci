/*
 *	(C) Copyright 2021 Muhammad Faran Aiki.
 *
 *	This file is owned by Muhammad Faran Aiki.
 *	Any use or copy must submits to Faran license.
 *
 *	This file is portable to C++.
 * 		Meaning, for C code that support C++ (for example: "fsci"), then
 * 		it is possible to compile it with C++.
 *
 *	Filetype:
 * 		C (not C++)
 */

/*
 *	This uses macro... which is definitely hard to read.
 *		I would say no one will understand, even I do not know.... (just kidding, of course)
 */

// "We" (I) do not like capital. 
enum type_numbering {
	type_int,
	type_string,
	type_prefix_string,
	type_float,
	type_double,
	type_table,
	type_hash,
	type_file,
	type_process,
	type_pointer,
}; // enum type_numbering

typedef struct _prefix_string {
	long int
		size;

	char
		*data;
} prefix_string;

int prefix_string_init(prefix_string *pref_str, const char *string, int size) {
	pref_str->size = size;
	pref_str->data = (char*) malloc(size * sizeof(*pref_str->data));

	memcpy(pref_str->data, string, size); // SIG_SEV
	
	return 0;
}

int prefix_string_delete(prefix_string *pref_str) {
	pref_str->size = 0;
	free(pref_str->data);

	return 0;
}

int prefix_string_check_null(prefix_string *pref_str) {
	long
		i;

	for (i = 0; i < pref_str->size; i++) {
		if (!pref_str->data[i]) {
			return 1;
		}
	}

	return 0;
}

int prefix_string_to_string(prefix_string *pref_str, char *string) {
	long
		i;

	prefix_string_check_null(pref_str);

	strcpy(string, pref_str->data);

	return 0;
}

#define init_table_normal(table_name, table_type)\
typedef struct _table_ ## table_name {\
	unsigned int\
		current,\
		size,\
		multiplier,\
		addition;\
\
	table_type\
		*item;\
} table_ ## table_name; \
int table_init_ ## table_name (table_ ## table_name *tab, unsigned int initial_size, unsigned int multiplier) {\
	tab->current    = 0;\
	tab->size       = initial_size;\
	tab->multiplier = multiplier;\
\
	tab->item       = (table_type*) malloc(tab->size * sizeof(*tab->item));\
\
	if (!tab->item) {\
		return 1;\
	}\
	\
	return 0;\
}\

#define init_table_special(table_name, table_type)\
typedef struct _table_ ## table_name {\
	unsigned int\
		current,\
		size,\
		multiplier,\
		addition;\
\
	table_type\
		*item;\
\
	uint \
		*type; \
} table_ ## table_name; \
int table_init_ ## table_name (table_ ## table_name *tab, unsigned int initial_size, unsigned int multiplier) {\
	tab->current    = 0;\
	tab->size       = initial_size;\
	tab->multiplier = multiplier;\
\
	tab->item       = (table_type*) malloc(tab->size * sizeof(*tab->item));\
	tab->type       = (unsigned int*) malloc(tab->size * sizeof(*tab->type));\
\
	if (!tab->item) {\
		return 1;\
	}\
	\
	return 0;\
}\

#define new_table(table_name, table_type)\
int table_check_ ## table_name (table_ ## table_name *tab) {\
	void\
		*temp;\
	\
	if (tab->current >= tab->size) {\
		tab->size  = tab->size * tab->multiplier + tab->addition;\
		\
		temp       = (table_type*) realloc(tab->item, tab->size * sizeof(tab->item));\
\
		if (!temp) {\
			return 1;\
		}\
\
		tab->item  = (table_type*) temp;\
	}\
\
	return 0;\
}\
\
table_type table_get_ ## table_name (table_ ## table_name *tab, unsigned int index) {\
	return tab->item[index];\
}\
\
table_type table_pop_ ## table_name (table_ ## table_name *tab) {\
	return tab->item[tab->current--];\
}\

#define single_deletion(table_name)\
int table_delete_ ## table_name (table_ ## table_name *tab) {\
	free(tab->item);\
\
	return 0;\
}

#define each_deletion(table_name)\
int table_delete_ ## table_name (table_ ## table_name *tab) {\
	unsigned int\
		i;\
\
	for (i = 0; i < tab->current; i++) {\
		free(tab->item[i]);\
	}\
\
	free(tab->item);\
\
	return 0;\
}

#define check_deletion(table_name)\
int table_delete_ ## table_name (table_ ## table_name *tab) {\
	unsigned int\
		i;\
\
	for (i = 0; i < tab->current; i++) {\
\
	}\
\
	free(tab->item);\
\
	return 0;\
}

#define xchg_normal(table_name, table_type) \
int table_push_ ## table_name (table_ ## table_name *tab, table_type item) {\
	table_check_ ## table_name (tab);\
\
	tab->item[tab->current++] = item;\
	\
	return 0;\
}\
\
int table_set_ ## table_name (table_ ## table_name *tab, table_type item, unsigned int index) {\
	if (index < tab->current) {\
		tab->item[index] = item;\
		\
		return 0;\
	}\
\
	return 1;\
}

#define xchg_special(table_name, table_type)\
int table_push_ ## table_name (table_ ## table_name *tab, table_type item, uint type) {\
	table_check_ ## table_name (tab);\
\
	if (tab->item[tab->current]) {\
		switch (tab->type[tab->current]) {\
			case type_file:\
				fclose(*(FILE**) tab->item[tab->current]);\
\
				break;\
			case type_process:\
				pclose(*(FILE**) tab->item[tab->current]);\
\
				break;\
		}\
\
		free(tab->item[tab->current]);\
	}\
\
	tab->item[tab->current] = item;\
	tab->type[tab->current++] = type;\
	\
	return 0;\
}\
\
int table_set_ ## table_name (table_ ## table_name *tab, table_type item, unsigned int index) {\
	if (index < tab->current) {\
		tab->item[index] = item;\
		\
		return 0;\
	}\
\
	return 1;\
}

init_table_normal(str, char*);         new_table(str, char*);            each_deletion(str);        xchg_normal(str, char*);
init_table_normal(string, char*);      new_table(string, char*);         each_deletion(string);     xchg_normal(string, char*);
init_table_normal(int, int);           new_table(int, int);              single_deletion(int);      xchg_normal(int, int);
init_table_normal(uint, unsigned int); new_table(uint, unsigned int);    single_deletion(uint);     xchg_normal(uint, unsigned int);
init_table_normal(integer, int);       new_table(integer, int);          single_deletion(integer);  xchg_normal(integer, int);
init_table_normal(float, float);       new_table(float, float);          single_deletion(float);    xchg_normal(float, float);
init_table_normal(double, double);     new_table(double, double);        single_deletion(double);   xchg_normal(double, double);
init_table_special(pointer, void*);    new_table(pointer, void*);        check_deletion(pointer);   xchg_special(pointer, void*);

/*
 *	Hash using some tricky function.
 */
#define new_hash(hash_name, hash_type)\
typedef struct _hash_ ## hash_name {\
	unsigned int\
		key;\
\
	unsigned int\
		type;\
\
	table_ ## hash_type\
		*item;\
} hash_ ## hash_name;\
\
int hash_init_ ## hash_name (hash_init_ ## hash_name, unsigned int initial_size) {\
	\
}\
\
int hash_hash(void *item, int type, int algorithm) {\
	unsigned int\
		current;\
	\
	switch(type) {\
		case type_int:\
			return current;\
		case type_string:\
			return current;\
		default:\
			return 0;\
	}\
}
