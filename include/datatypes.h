/*
 *	(C) Copyright 2021 Muhammad Faran Aiki.
 *
 *	This uses macro... which is definitely hard to read.
 */

/*
 *	Table using some multiplier.
 */

// Still unused.
enum DATA_NUMBERING {
	INTEGER,
	STRING,
	FLOAT,
	DOUBLE,
	TABLE,
	HASH,
	POINTER,
};

#define new_table(table_name, table_type)\
\
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
\
int table_init_ ## table_name (table_ ## table_name *tab, unsigned int initial_size, unsigned int multiplier) {\
	tab->current    = 0;\
	tab->size       = initial_size;\
	tab->multiplier = multiplier;\
\
	tab->item       = (table_type*) malloc(tab->size * sizeof(tab->item));\
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

new_table(str, char*);     each_deletion(str);
new_table(string, char*);  each_deletion(string);
new_table(int, int);       single_deletion(int);
new_table(float, float);   single_deletion(float);
new_table(double, double); single_deletion(double);
new_table(pointer, void*); each_deletion(pointer);

/*
 *	Hash using some tricky function.
 */
#define new_hash

