/******************************************************************************
 *
 * File Name: hash.c
 *	      (c) 2010 AED
 * Author:    AED Team
 * Revision:  v2.2 ACR
 *
 * NAME
 *	lab10 - Hash Table
 *
 * SYNOPSIS
 *	#include <stdlib.h>
 *	#include <stdio.h>
 *
 * DESCRIPTION
 *
 * DIAGNOSTICS tested
 *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "pal.h"

/******************************************************************************
 * main()
 *
 * Arguments: argc - number of comand line arguments
 *            argc - array of pointers to command line arguments
 * Returns: success or error
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

int main (int argc, char **argv)
{
  Hash *tabela;     /* pointer for a vector of No */
  Info h;

  if (argc < 3) {
    printf("usage: %s infile m\n", argv[0]);
    return -1;
  }
  h.num_comp = 0;
  h.numPalavras = 0;
  h.m = atoi (argv[2]);
  h.num_pal=(int*)calloc(h.m,sizeof(int));
  tabela = AlocaTabela(h.m);
  PreencheTabelaPalavras(tabela, &h, argv[1]);
  EscreveFicheiro(tabela, argv[1], h.m);

  /* shows graphically the distribution of the words in the hash table */

  MostraDistribuicao(tabela, &h);
  printf("\n Number of diferent words: %d \n\n\t", h.numPalavras);
  printf("Number of comparisons = %d\n\n", h.num_comp);

  LibertarTabela(h.m, tabela);
  free(h.num_pal);

  return 0;
}
