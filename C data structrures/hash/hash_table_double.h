#pragma once

#include "hash.h"

typedef struct tag_hash_table_double {
  hash_item_marked *Data;
  int
    Size, NumElements,
    Hash1, Hash2;
} hash_table_double;

void initTableDouble( hash_table_double *Table, int Size, int Hash1, int Hash2 );
void clearTableDouble( hash_table_double *Table );
int addTableDouble( hash_table_double *Table, char *Str );
int findTableDouble( hash_table_double *Table, char *Str );
int deleteTableDouble( hash_table_double *Table, char *Str );
