#ifndef QUEUE_H
#define QUEUE_H
/******************************************************************************
 *
 * File Name: queue.h
 *	      (c) 2010 AED
 * Author:    AED team
 * Revision:  v2.3 ACR
 * NAME
 *     queue.h - prototypes
 *
 * SYNOPSIS
 *     #include <stdlib.h>
 *     #include <stdio.h>
 *     #include <string.h>
 *
 * DESCRIPTION
 *		Definitions useful to implement breath scan
 * DIAGNOSTICS
 *
 *****************************************************************************/
#include "tree.h"
#include "string.h"

typedef struct _element {
  Node *node;
  int level;
  struct _element *next;
} Element;

typedef struct _queue {
  Element *first;
  Element *last;
} Queue;


Queue *QueueNew();                    /* creates empty list */
Element *GetFirst(Queue*);            /* get first element of the queue */
void  InsertLast(Queue*, Node*, int);      /* insertion at the end of queue */

#endif
