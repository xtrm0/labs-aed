#ifndef TREE_H
#define TREE_H
/******************************************************************************
 *
 * File Name: tree.h
 *	      (c) 2009 AED
 * Author:    AED team
 * Revision:  v2.2 ACR
 *            v3.0 AED Team Out 2013
 *
 * NAME
 *     tree  - prototypes
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <malloc.h>
 *
 * DESCRIPTION
 *		implements tree auxiliary functions
 * DIAGNOSTICS
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>

#define MAX(X,Y) ((X) < (Y) ? (Y) : (X))
#define MIN(X,Y) ((X) > (Y) ? (Y) : (X))

typedef enum
{
    FALSE=0,
    TRUE=1
} Boolean;


typedef struct _Node {
  int value;
  struct _Node *left, *right;
} Node;

#include "queue.h"







Node *AllocNode ();
Node *NewNode (int num);
Node *Construct (FILE *fp, char * filename);
void FreeTree(Node *root);
void espaco (int n);
void PreFixed (Node *root, int n);
void InFixed (Node *root, int n);
void PosFixed (Node *root, int n);
void sweepDepth (Node *root, int n);
void sweepBreadth (Node *root);
Boolean isTreeOrdered(Node *root);
Boolean isTreeBalanced(Node *root);

#endif

