#include <stdlib.h>
#include <string.h>

#include "hash_table_double.h"
#include "hash.h"

void initTableDouble( hash_table_double *Table, int Size, int Hash1, int Hash2 ) {
  Table->Data = malloc(sizeof(hash_item_marked) * Size);
  memset(Table->Data, 0, sizeof(hash_item_marked) * Size);
  Table->Size = Size;
  Table->NumElements = 0;
  Table->Hash1 = Hash1;
  Table->Hash2 = Hash2;
}

void clearTableDouble( hash_table_double *Table ) {
  int i;
  for (i = 0; i < Table->Size; i++)
    if (Table->Data[i].Ptr != NULL)
      free(Table->Data[i].Ptr);

  Table->Size = 0;
  Table->NumElements = 0;
  free(Table->Data);
}

static unsigned int hash1( hash_table_double *Table, char *Str ) {
  return hash(Str, Table->Hash1);
}

static unsigned int hash2( hash_table_double *Table, char *Str ) {
  return hash(Str, Table->Hash2) % (Table->Size - 1) + 1;
}

static int findStr( hash_table_double *Table, char *Str ) {
  unsigned int
    Hash1 = hash1(Table, Str),
    Hash2 = hash2(Table, Str);
  int
    i, Place;

  for (i = 0; i < Table->Size; i++) {
    Place = (Hash1 + i * Hash2) % Table->Size;
    if (!Table->Data[Place].IsDeleted && Table->Data[Place].Ptr != NULL)
      return Place;
  }
  return -1;
}

int addTableDouble( hash_table_double *Table, char *Str ) {
  unsigned int
    Hash1 = hash1(Table, Str),
    Hash2 = hash2(Table, Str);
  int i, Place;

  for (i = 0; i < Table->Size; i++) {
    Place = (Hash1 + i * Hash2) % Table->Size;
    if (Table->Data[Place].IsDeleted || Table->Data[Place].Ptr == NULL) {
      /* Found place */
      if (Table->Data[Place].Ptr != NULL)
        free(Table->Data[Place].Ptr);

      Table->Data[Place].Ptr = malloc(sizeof(char) * strlen(Str) + 1);
      strcpy(Table->Data[Place].Ptr, Str);
      Table->Data[Place].IsDeleted = 0;
      return 1;
    }
  }

  return 0;
}

int findTableDouble( hash_table_double *Table, char *Str ) {
  return findStr(Table, Str) != -1;
}

int deleteTableDouble( hash_table_double *Table, char *Str ) {
  int Place = findStr(Table, Str);

  if (Place == -1)
    /* String does not exist */
    return 0;

  Table->Data[Place].IsDeleted = 1;
  return 1;
}
