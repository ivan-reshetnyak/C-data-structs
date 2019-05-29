#pragma once

typedef struct tag_hash_item_marked {
  char *Ptr;
  int IsDeleted;
} hash_item_marked;

unsigned int hash( char *Str, int Mul );
unsigned int hashPow2( char *Str, int Pow );