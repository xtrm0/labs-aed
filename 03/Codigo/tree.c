/******************************************************************************
 *
 * File Name: tree.c
 *	      (c) 2010 AED
 * Author:    AED team
 * Revision:  v2.3 ACR
 *            v3.0 AED Team Out 2013
 *
 * NAME
 *     Tree - different forms of tree sweep
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

#include "tree.h"



/******************************************************************************
 * AllocNode()
 *
 * Arguments: (none)
 * Returns: new node
 * Side-Effects: none
 *
 * Description: allocates space for a new node
 *
 *****************************************************************************/


Node *AllocNode() {
  return ((Node *) malloc(sizeof(Node)));
}


/******************************************************************************
 * NewNode()
 *
 * Arguments: integer
 * Returns: new node
 * Side-Effects: none
 *
 * Description: creates a new node with a integer value
 *
 *****************************************************************************/

Node *NewNode(int num)
{
    Node *aux;
    
    if (num==-1)
        return NULL;
    
    aux = AllocNode();
    aux->value = num;
    aux->right = aux->left = NULL;
    
    return aux;
}

/******************************************************************************
 * Construct()
 *
 * Arguments: input file and filename
 * Returns: pointer to root node of the tree
 * Side-Effects: none
 *
 * Description: constructs a tree reading integer numbers from file
 *
 *****************************************************************************/

Node *Construct(FILE *fp, char * filename)
{
    Node *nodeRoot;
    int num;
    
    if (fscanf(fp,"%d", &num) == EOF)
    {
        fprintf(stderr, "File %s has an insufficient number of values.  Please correct.\n", filename);
        exit(0);
    }
    
    if ((nodeRoot = NewNode(num)) != NULL)
    {
        /* links to child */
        nodeRoot->left  = Construct(fp, filename);
        nodeRoot->right = Construct(fp, filename);
    }
    
    return nodeRoot;
}

/******************************************************************************
 * FreeTree()
 *
 * Arguments: node - a tree root
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: frees the tree
 *
 *****************************************************************************/

void FreeTree(Node * root)
{
    if (root != NULL) {
	FreeTree(root->left);
	FreeTree(root->right);
	free(root);
    }
}

/******************************************************************************
 * spaces()
 *
 * Arguments: n - number of spaces
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints n spaces
 *
 *****************************************************************************/

void spaces(int n)
{
  int i;

  for (i = 0; i < n; i++)
    printf("    ");
  return;
}


/******************************************************************************
 * PreFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the PreFix format
 *
 *****************************************************************************/

void PreFixed(Node *root, int n)
{
  if (root != NULL) {
    spaces(n);
    printf("%4d\n", root->value);
    PreFixed(root->left, n + 1);
    PreFixed(root->right, n + 1);
  }

  return;
}


/******************************************************************************
 * InFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the InFix format
 *
 *****************************************************************************/

void InFixed(Node *root, int n)
{
  if (root != NULL) {
    InFixed(root->left, n + 1);
    spaces(n);
    printf("%4d\n", root->value);    
    InFixed(root->right, n + 1);
  }
  return;
}


/******************************************************************************
 * PosFixed()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the PosFix format
 *
 *****************************************************************************/

void PosFixed(Node *root, int n)
{
  if (root != NULL) {
    PosFixed(root->left, n + 1);
    PosFixed(root->right, n + 1);
    spaces(n);    
    printf("%4d\n", root->value);     
  }
  return;
}


/******************************************************************************
 * sweepDepth()
 *
 * Arguments: root - root of the tree
 *	      n - height of the tree
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the depthfirst format
 *
 *****************************************************************************/

void sweepDepth(Node *root, int n)
{
  PreFixed(root, n);
  return;
}


/******************************************************************************
 * sweepBreadth()
 *
 * Arguments: root - root of the tree
 *
 * Returns: void
 * Side-Effects: none
 *
 * Description: prints the tree in the Breathfirst format
 *
 *****************************************************************************/

void sweepBreadth(Node *root)
{
    Queue * Q = QueueNew();
    Element * aux; 
    InsertLast(Q,root,0);
    while (Q->first != NULL) {
        aux = GetFirst(Q);
        if (aux->node == NULL) {
            free(aux);
            continue;
        }
        spaces(aux->level);    
        printf("%4d\n", aux->node->value);
        InsertLast(Q,aux->node->left,aux->level+1);
        InsertLast(Q,aux->node->right,aux->level+1);
        free(aux);
    }
    free(Q);
    return;
}



Boolean _isTreeOrdered(Node * root, int * mini) {
    if (root==NULL) return TRUE;
    
    if (!_isTreeOrdered(root->left, mini)) return FALSE;
    
    if (root->value < *mini) return FALSE;    
    *mini = root->value;
    
    if (!_isTreeOrdered(root->right, mini)) return FALSE;
    return TRUE;    
}
/******************************************************************************
 * IsTreeOrdered()
 *
 * Arguments: node - a tree root
 *
 * Returns: Boolean (TRUE or FALSE)
 * Side-Effects: none
 *
 * Description: checks if a tree is ordered
 *
 *****************************************************************************/

Boolean isTreeOrdered(Node * root)
{
    int aux = INT_MIN;
    return _isTreeOrdered(root, &aux);
}


int _isTreeBalanced(Node * root) {
    int dir=0, esq=0;
    if (root==NULL) return 0;
    
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    
    if (root->left!=NULL)
        esq = _isTreeBalanced(root->left);
    if (root->right!=NULL)
        dir = _isTreeBalanced(root->right);
    
    if (dir==-1 || esq == -1) return -1;
    if (abs(dir-esq)>1) return -1;
    
    
    return 1 + MAX(dir,esq);
}

/******************************************************************************
 * IsTreeBalanced()
 *
 * Arguments: node - a tree root
 *
 *
 * Returns: Boolean (TRUE or FALSE)
 * Side-Effects: none
 *
 * Description: checks if a tree is AVL balanced
 *
 *****************************************************************************/

Boolean isTreeBalanced(Node * root)
{
    if (_isTreeBalanced(root)==-1) return FALSE;
    return TRUE;
}




