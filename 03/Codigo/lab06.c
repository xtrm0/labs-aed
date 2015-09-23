/******************************************************************************
 * File Name: lab06.c
 *	      (c) 2010 AED
 * Author:    AED Team
 * Revision:  v2.3 AED Team
 *            v3.0 AED Team Out 2013
 * NAME
 *     Lab06 - Trees
 * SYNOPSIS
 *		#include <stdlib.h>
 *		#include <stdio.h>
 * DESCRIPTION
 * DIAGNOSTICS tested
 *****************************************************************************/

#include "tree.h"
#include "queue.h"


/******************************************************************************
 * main()
 *
 * Arguments: argc - number of comand line arguments
 *            argv - array of pointers to command line arguments
 * Returns: success or error
 * Side-Effects: none
  *
 * Description:
 *
 *****************************************************************************/

int main(int argc, char *argv[])
{
    Node *root;
    
    FILE *fp;
    
    /* must have at least one argument besides the exec name */
    if (argc < 2) {
        fprintf(stderr, "This program must have at least one argument besides the exec name.\n");
        exit(0);
    }
    
    /* open file and read array size */
    fp = (FILE *) fopen(argv[1], "r");
    if (fp == (FILE *) NULL) {
        fprintf(stderr, "File %s cannot be read.  Please correct.\n", argv[1]);
        exit(0);
    }
    
    root = Construct(fp, argv[1]);
    fclose(fp);
    
    printf("\nPreFix dump:\n");
    PreFixed(root, 0);
    putchar('\n');
    printf("\nIn-Fix:\n");
    InFixed(root, 0);
    putchar('\n');
    printf("\nPos-Fix:\n");
    PosFixed(root, 0);
    putchar('\n');
    printf("Depth First:\n");
    sweepDepth(root, 0);
    putchar('\n');
    printf("Breath First:\n");
    sweepBreadth(root);
    putchar('\n');
    if (isTreeOrdered(root))
        printf("The tree is ordered...!\n");
    else
        printf("The tree is not ordered...!\n");
    
    if (isTreeBalanced(root))
        printf("The tree is balanced...!\n");
    else
        printf("The tree is not balanced...!\n");
    FreeTree(root);
    return (0);
}
