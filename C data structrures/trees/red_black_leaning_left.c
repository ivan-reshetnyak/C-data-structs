#include <stdlib.h>

#include "red_black_leaning_left.h"

static rbll Nil; /* = { RBTREE_BLACK, 0, NULL, NULL }; */

void rbllInitialize( rbll **Root ) {
  Nil.Color = RBTREE_BLACK;
  Nil.Left = &Nil;
  Nil.Right = &Nil;

  *Root = &Nil;
}

static rbll * rotateLeft( rbll *Pivot ) {
  rbll *X = Pivot->Right;
  Pivot->Right = X->Left;
  X->Left = Pivot;
  X->Color = Pivot->Color;
  Pivot->Color = RBTREE_RED;
  return X;
}

static rbll * rotateRight( rbll *Pivot ) {
  rbll *X = Pivot->Left;
  Pivot->Left = X->Right;
  X->Right = Pivot;
  X->Color = Pivot->Color;
  Pivot->Color = RBTREE_RED;
  return X;
}

static void colorFlip( rbll *Pivot ) {
  Pivot->Color = 1 - Pivot->Color;
  if (Pivot->Left != &Nil)
    Pivot->Left->Color = 1 - Pivot->Left->Color;
  if (Pivot->Right != &Nil)
    Pivot->Right->Color = 1 - Pivot->Right->Color;
}

int rbllIsRed( rbll *Node ) {
  return /*Node != &Nil && */Node->Color == RBTREE_RED;
}

int rbllIsBlack( rbll *Node ) {
  return /*Node != &Nil && */Node->Color == RBTREE_BLACK;
}

static rbll * moveRedLeft( rbll *Pivot ) {
  colorFlip(Pivot);
  if (rbllIsRed(Pivot->Right->Left)) {
    Pivot->Right = rotateRight(Pivot->Right);
    Pivot = rotateLeft(Pivot);
    colorFlip(Pivot);
  }
  return Pivot;
}

static rbll * moveRedRight( rbll *Pivot ) {
  colorFlip(Pivot);
  if (rbllIsRed(Pivot->Left->Left)) {
    Pivot = rotateRight(Pivot);
    colorFlip(Pivot);
  }
  return Pivot;
}

static rbll * insert( rbll *Pivot, int Key ) {
  if (Pivot == &Nil) {
    rbll *NewNode = malloc(sizeof(rbll));
    NewNode->Color = RBTREE_RED;
    NewNode->Left = NewNode->Right = &Nil;
    NewNode->Data = Key;
    return NewNode;
  }

  if (Pivot->Data == Key)
    Pivot->Data = Key;
  else if (Key < Pivot->Data)
    Pivot->Left = insert(Pivot->Left, Key);
  else
    Pivot->Right = insert(Pivot->Right, Key);

  if (rbllIsRed(Pivot->Right) && !rbllIsRed(Pivot->Left))
    Pivot = rotateLeft(Pivot);
  if (rbllIsRed(Pivot->Left) && rbllIsRed(Pivot->Left->Left))
    Pivot = rotateRight(Pivot);

  if (rbllIsRed(Pivot->Left) && rbllIsRed(Pivot->Right))
    colorFlip(Pivot);

  return Pivot;
}

static rbll * getPlace( rbll *Root, int Key, rbll **Parent ) {
  rbll *CurNode = Root;
  *Parent = &Nil;
  while (CurNode != &Nil && CurNode->Data != Key) {
    *Parent = CurNode;
    if (Key < CurNode->Data)
      CurNode = CurNode->Left;
    else
      CurNode = CurNode->Right;
  }

  return CurNode;
}

int rbllFind( rbll *Root, const int Key ) {
  rbll *Parent, *Place = getPlace(Root, Key, &Parent);

  return Place != &Nil;
}

int rbllInsert( rbll **Root, int NewElement ) {
  if (!rbllFind(*Root, NewElement)) {
    *Root = insert(*Root, NewElement);
    (*Root)->Color = RBTREE_BLACK;
    return 1;
  }

  return 0;
}

static rbll * fixUp( rbll *Pivot ) {
  if (rbllIsRed(Pivot->Right))
    Pivot = rotateLeft(Pivot);

  if (rbllIsRed(Pivot->Left) && rbllIsRed(Pivot->Left->Left))
    Pivot = rotateRight(Pivot);

  if (rbllIsRed(Pivot->Left) && rbllIsRed(Pivot->Right))
    colorFlip(Pivot);

  return Pivot;
}

static rbll * minElement( rbll *Pivot ) {
  if (Pivot == &Nil)
    return Pivot;

  while (Pivot->Left != &Nil)
    Pivot = Pivot->Left;
  return Pivot;
}

static rbll * removeMin( rbll *Pivot ) {
  if (Pivot->Left == &Nil) {
    free(Pivot);
    return &Nil;
  }

  if (!rbllIsRed(Pivot->Left) && !rbllIsRed(Pivot->Left->Left))
    Pivot = moveRedLeft(Pivot);

  Pivot->Left = removeMin(Pivot->Left);

  return fixUp(Pivot);
}

static rbll * remove( rbll *Pivot, int Key ) {
  if (Pivot == &Nil)
    return &Nil;

  if (Key < Pivot->Data) {
    if (!rbllIsRed(Pivot->Left) && !rbllIsRed(Pivot->Left->Left))
      Pivot = moveRedLeft(Pivot);
    Pivot->Left = remove(Pivot->Left, Key);
  } else {
    if (rbllIsRed(Pivot->Left))
      Pivot = rotateRight(Pivot);

    if (Key == Pivot->Data && Pivot->Right == &Nil) {
      free(Pivot);
      return &Nil;
    }

    if (!rbllIsRed(Pivot->Right) && !rbllIsRed(Pivot->Right->Left))
      Pivot = moveRedRight(Pivot);

    if (Key == Pivot->Data) {
      Pivot->Data = minElement(Pivot->Right)->Data;
      Pivot->Right = removeMin(Pivot->Right);
    } else
      Pivot->Right = remove(Pivot->Right, Key);
  }

  return fixUp(Pivot);
}

int rbllRemove( rbll **Root, int Key ) {
  if (!rbllFind(*Root, Key)) {
    *Root = remove(*Root, Key);
    (*Root)->Color = RBTREE_BLACK;
    return 1;
  }

  return 0;
}

void rbllClean( rbll **Root ) {
  while (!rbllIsEmpty(*Root))
    *Root = removeMin(*Root);
}

int rbllIsEmpty( rbll *Root ) {
  return Root == &Nil;
}
