#pragma once

#ifndef rbtree_color
typedef enum {
  RBTREE_RED = 0, RBTREE_BLACK = 1
} rbtree_color;
#endif /* rbtree_color */

typedef struct tag_rbll {
  rbtree_color Color;
  int Data;
  struct tag_rbll *Left, *Right;
} rbll;

int rbllIsRed( rbll *Node );
int rbllIsBlack( rbll *Node );
void rbllInitialize( rbll **Root );
int rbllInsert( rbll **Root, int NewElement );
int rbllFind( rbll *Root, const int Key );
int rbllRemove( rbll **Root, int Key );
void rbllClean( rbll **Root );
int rbllIsEmpty( rbll *Root );
