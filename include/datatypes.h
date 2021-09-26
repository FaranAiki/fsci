/*
 *	(C) Copyright 2021 Muhammad Faran Aiki.
 *
 *	This uses macro... which is definitely hard to read.
 */

/*
 *	Table using some multiplier.
 */

#define new_table(table_name, table_type)\
\
typedef struct _table_ ## table_name {\
	unsigned int\
		current;\
		size,\
		multiplier,\
\
	table_type\
		*item;\
} table_ ## table_name; \
\
int table_init_ ## table_name (table_ ## table_name *tab, int initial_size, int multiplier) {\
	tab->current    = 0;\
	tab->size       = initial_size;\
	tab->multiplier = multiplier;\
\
	tab->item       = malloc(tab->size * sizeof(tab->item));\
\
	if (!tab->item) {\
		return 1;\
	}\
	\
	return 0;\
}\
\
int table_check_ ## table_name (table_ ## table_name *tab) {\
	void\
		*temp;\
	\
	if (tab->current >= tab->size) {\
		tab->size *= tab->multiplier;\
		\
		temp  = realloc(tab->item, tab->size * sizeof(tab->item));\
\
		if (!temp) {\
			return 1;\
		}\
\
		tab->item  = temp;\
	}\
\
	return 0;\
}\
\
int table_add_ ## table_name (table_ ## table_name *tab, table_type item) {\
	table_check_ ## table_name (tab);\
\
	tab->item[tab->current] = item;\
	\
	tab->current++;\
}\
\
int table_set_ ## table_name (table_ ## table_name *tab, table_type item, int index) {\
	if (index < tab->current) {\
		tab->item[index] = item;\
		\
		return 0;\
	}\
\
	return 1;\
}\
\
int table_delete_ ## table_name (table_ ## table_name *tab) {\
	tab->current = 0;\
	tab->size    = 0;\
\
	free(tab->item);\
}\
\
table_type table_get_ ## table_name (table_ ## table_name *tab, int index) {\
	return tab->item[index];\
}\
\
table_type table_pop_ ## table_name (table_ ## table_name *tab) {\
	return tab->item[tab->current--];\
}\

new_table(str, char*);
new_table(string, char*);
new_table(int, int);
new_table(float, float);
new_table(double, double);

new_table(table_str, table_str);
new_table(table_string, table_string);
new_table(table_int, table_int);
new_table(table_float, table_float);
new_table(table_double, table_double);

/*
 *	Hash using some tricky function.
 */


