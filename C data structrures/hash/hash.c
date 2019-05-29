#include "hash.h"

unsigned int hash( char *Str, int Mul ) {
  unsigned int Num = 1, Hash = 0;

  while (*Str != 0) {
    Hash += (int)*Str * Num;
    Num *= Mul;
    Str++;
  }
  return Hash;
}

unsigned int hashPow2( char *Str, int Pow ) {
  unsigned int Num = 1, Hash = 0;

  while (*Str != 0) {
    Hash += (int)*Str * Num;
    Num <<= Pow;
    Str++;
  }
  return Hash;
}
