/******************************************************************************
 *
 * File Name: palavras.c
 *	      (c) 2012 AED
 * Authors:    AED Team
 * Last modified:
 * Revision:  v2.0
 *
 * COMMENTS:    Version with no globals variables
 *		Passing structure for functions
 *		More compact test for EOF
 *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_STR 100

typedef struct _st_texto {
  int  n_total_palavras;	/* total number of words */
  int  n_dist_palavras;		/* number of distinct words*/
  int  n_max_palavras;          /* number of allocated word pointers */
  char **palavras;		/* Table of strings for words "palavras"*/
  int  *ocorrencias;		/* Table of integers for counting occurences
                                   "ocorrências" */
} st_texto;





/******************************************************************************
 * InicializaVetor()
 *
 * Arguments: s - pointer to vector to initialize
 * Returns: nothing
 * Side-Effects: none
 *
 * Description: Initialzes the s vector to an empty vector with 1 allocated
element
 *
 *****************************************************************************/
void InicializaVetor(st_texto * s) {
  s->n_total_palavras = 0;
  s->n_dist_palavras  = 0;
  s->n_max_palavras   = 1;
  s->palavras         = (char **) malloc(sizeof(char *));
  s->palavras[0]=NULL;
  s->ocorrencias      = (int *)   malloc(sizeof(int));
  s->ocorrencias[0]=0;
}

/******************************************************************************
 * DuplicateVetor()
 *
 * Arguments: s - pointer to vector to double size
 * Returns: nothing
 * Side-Effects: none
 *
 * Description: Doubles the number of allocated elements on vector s
 *
 *****************************************************************************/

void DuplicaVetor(st_texto * s) {
  char ** cpp;
  int * ip;
  cpp = (char **) malloc(sizeof(char *) * s->n_max_palavras*2);
  ip  = (int *)   malloc(sizeof(int) * s->n_max_palavras*2);
  memset(cpp, 0, sizeof(char *) * s->n_max_palavras*2);
  memcpy(cpp, s->palavras   , sizeof(char *) * s->n_max_palavras);
  memcpy(ip , s->ocorrencias, sizeof(int) * s->n_max_palavras);
  memset(ip + s->n_max_palavras, 0, sizeof(int) * s->n_max_palavras);
  
  free (s->palavras);
  free (s->ocorrencias);
  s->palavras = cpp;
  s->ocorrencias = ip;
  s->n_max_palavras *= 2;
}


/******************************************************************************
 * LePalavra()
 *
 * Arguments: f - pointer to file where word will be read
 * Returns: pointer to word just read
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

char *LePalavra ( FILE * f )
{
  static char palavra[MAX_STR];
  /* It is assumed that the words present in the text files do not exceed
     100 characters in length  */
  /* Note that the variable palavra is declared as "static". */
  if ( fscanf ( f, "%s", palavra ) ==1 )
    return (palavra);
  else
    return ((char *) NULL);
}


/******************************************************************************
 * AbreFicheiro()
 *
 * Arguments: nome - pointer to string holding name of file to open
 *            mode - pointer to string holding mode to use for opening file
 * Returns: pointer to opened file
 * Side-Effects: exits if given file cannot be opened with given mode
 *
 * Description:
 *
 *****************************************************************************/

FILE *AbreFicheiro ( char *nome, char *mode )
{
  FILE *f;
  f = fopen ( nome, mode );
  if ( f == NULL ) {
    fprintf ( stderr, "ERROR: It is not possible to open file %s!\n", nome );
    exit ( 1 );
    /* Error messages are sent to the stderr channel.
       Use an exit number different from 0 (zero) in case of error.*/
  }
  return (f);
}


/******************************************************************************
 * NovaPalavra()
 *
 * Arguments: palavra - pointer to string holding a word
 *            st_texto - pointer to structure where run information is kept
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

int NovaPalavra ( char *palavra, st_texto *t )
{
  int i = 0;
  /* This function searches for a word in the table.
     if the word is not found returns -1,
     Otherwise returns the position of the word in the table */
  while ( i < (*t).n_dist_palavras) {
    if ( strcmp ( (*t).palavras[i], palavra ) == 0 )
      return (i);
    i++;
  }
  return (-1);
}


/******************************************************************************
 * PreencheTabelaPalavras()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            st_texto - pointer to structure where information will be saved
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

void PreencheTabelaPalavras ( char *ficheiro, st_texto *t )
{
  FILE *f;
  int n;
  char *palavra;

  f = AbreFicheiro ( ficheiro, "r" );
  while ( ( palavra = LePalavra ( f ) ) != NULL ) {
    t->n_total_palavras++;
    if ( ( n = NovaPalavra ( palavra, &(*t) ) ) == -1 )	{
      if (t->n_dist_palavras == t->n_max_palavras)
        DuplicaVetor(t);
      t->palavras[t->n_dist_palavras] = (char *) malloc(sizeof(char) * (strlen(palavra)+1));
      strcpy ( (*t).palavras[(*t).n_dist_palavras], palavra );
      (*t).ocorrencias[(*t).n_dist_palavras]++;
      (*t).n_dist_palavras++;
    }
    else {
      (*t).ocorrencias[n]++;
    }
  }
  fclose ( f );
  return;
}


/******************************************************************************
 * EscreveFicheiro()
 *
 * Arguments: ficheiro - pointer to string holding name of file to save
 *            st_texto - pointer to structure where information is kept
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

void EscreveFicheiro ( char *ficheiro, st_texto *t )
{
  FILE *f;
  char *nome;
  int i = 0;

  nome = (char *) malloc(sizeof(char)*(strlen(ficheiro)+10));
  if ( nome == NULL ) {
    fprintf ( stderr, "ERROr: not enough memory available!\n" );
    exit ( 5 );
  }
  strcpy ( nome, ficheiro );
  strcat ( nome, ".palavras" );
  f = AbreFicheiro ( nome, "w" );
  for ( i = 0; i < (*t).n_dist_palavras; i++ ) {
    fprintf ( f, "%d: %s\n", (*t).ocorrencias[i], (*t).palavras[i] );
  }
  printf ( "Count of distinct words: %d\n", (*t).n_dist_palavras );
  free(nome);
  fclose ( f );
  return;
}


/******************************************************************************
 * main()
 *
 * Arguments: argc - counter of number of arguments in call
 *            argv - pointer to array of strings holding the arguments
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

int main ( int argc, char **argv )
{
  int i;
  st_texto st_palavras;

  if ( argc < 2 ) {
    fprintf ( stderr, "ERROR: missing filename in argument!\n" );
    exit ( 6 );
  }

  InicializaVetor( &st_palavras );
  PreencheTabelaPalavras ( argv[1],&st_palavras );
  EscreveFicheiro ( argv[1], &st_palavras );
  for (i=0; i<st_palavras.n_dist_palavras; i++) {
    free(st_palavras.palavras[i]);
  }
  free(st_palavras.palavras);
  free(st_palavras.ocorrencias);
  return (0);
}
