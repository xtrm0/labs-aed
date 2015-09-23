/*
 *  File name: lab03b.c
 *
 *  Author: 2013 Fall Semester AED Team
 *
 *  Release date: 2013/10/04
 *
 *  Description: See the handout for Lab 03.
 *
 *  Version: 1.0
 *
 *  Change log: N/A
 *
 */



/* Header Inclusions                                              */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Entry.h"

#define ASCENDENTE  1
#define DESCENDENTE 2

#define ID 1
#define AGE 2
#define HEIGHT 3
#define WEIGHT 4


int comparisonIdAsc(Item item1, Item item2) {
  return (getIdEntry(item1) < getIdEntry(item2) ? 1:0);
}
int comparisonAgeAsc(Item item1, Item item2) {
  return (getAgeEntry(item1) < getAgeEntry(item2) ? 1:0);
}
int comparisonHeightAsc(Item item1, Item item2) {
  return (getHeightEntry(item1) < getHeightEntry(item2) ? 1:0);
}
int comparisonWeightAsc(Item item1, Item item2) {
  return (getWeightEntry(item1) < getWeightEntry(item2) ? 1:0);
}


/*
 *  Function:
 *    readEntryFile2LinkedList
 *
 *  Description:
 *    Reads the entries from a file and creates a linked list with
 *   these entries in the inverse order.
 *
 *  Arguments:
 *    Pointer to the file stream:
 *        FILE * fp
 *
 *  Return value:
 *    Pointer to the first node of the linked list.
 */
LinkedList * readEntryFile2LinkedList(FILE * fp, int parametro)
{
  int id;
  int age;
  int height;
  int weight;
  int err=0;

  LinkedList * lp;
  Entry * entry;

  /* Initialize linked list                                       */
  lp = initLinkedList();

  /* Cycle through file rows                                      */
  while(fscanf(fp, "%d %d %d %d", &id, &age, &height, &weight) == 4)
  {
    /* Create new entry                                           */
    entry = newEntry(id, age, height, weight);
    /* Store entry in the linked list                             */
    if( parametro == ID )
      lp = insertSortedLinkedList(lp,(Item) entry, &comparisonIdAsc, &err);
    else if( parametro == AGE )
      lp = insertSortedLinkedList(lp,(Item) entry, &comparisonAgeAsc, &err);
    else if( parametro == HEIGHT )
      lp = insertSortedLinkedList(lp,(Item) entry, &comparisonHeightAsc, &err);
    else
      lp = insertSortedLinkedList(lp,(Item) entry, &comparisonWeightAsc, &err);

    if (err==2) {
      printf("Erro de memoria");
      exit(2);
    }
  }
/*caso queiramos ordenar a lista toda:*/
/*
if( parametro == ID ){
  if( sentido == ASCENDENTE )
    lp = insertSortedLinkedList(lp,(Item) entry, &comparisonIdAsc, &err);
  else
    lp = insertSortedLinkedList(lp,(Item) entry, &comparisonIdDesc, &err);
}
else if( parametro == AGE ){
  if( sentido == ASCENDENTE )
    lp = insertSortedLinkedList(lp,(Item) entry, &comparisonAgeAsc, &err);
  else
    lp = insertSortedLinkedList(lp,(Item) entry, &comparisonAgeDesc, &err);
}
else if( parametro == HEIGHT ){
  if( sentido == ASCENDENTE )
    lp = insertSortedLinkedList(lp,(Item) entry, &comparisonHeightAsc, &err);
  else
    lp = insertSortedLinkedList(lp,(Item) entry, &comparisonHeightDesc, &err);
}
else {
  if( sentido == ASCENDENTE )
    lp = insertSortedLinkedList(lp,(Item) entry, &comparisonWeightAsc, &err);
  else
    lp = insertSortedLinkedList(lp,(Item) entry, &comparisonWeightDesc, &err);
}
*/

  return lp;
}



/*
 *  Function:
 *    writeEntryFile
 *
 *  Description:
 *    Writes the entries from a linked list to a file.
 *
 *  Arguments:
 *    Pointer to the first node of the linked list:
 *      LinkedList * lp
 *    Pointer to the file stream:
 *      FILE * fp
 *
 *  Return value:
 *    None.
 */
void writeEntryFile(LinkedList * lp, FILE *fp)
{
  LinkedList * aux;

  aux = lp;
  while(aux != NULL)
  {
    printEntry((Entry *) getItemLinkedList(aux), fp);
    aux = getNextNodeLinkedList(aux);
  }
}

void writeEntryFileRev(LinkedList * lp, FILE * fp);
void writeEntryFileRev(LinkedList * lp, FILE * fp) {
  if(lp==NULL) return;
  writeEntryFileRev(getNextNodeLinkedList(lp), fp);
  printEntry((Entry *) getItemLinkedList(lp), fp);
}



/*
 *  Function:
 *    freeEntryItem
 *
 *  Description:
 *    Frees the memory allocated to an Item of the type Entry
 *
 *  Arguments:
 *    Pointer to the item
 *      Item item
 *
 *  Return value:
 *    None.
 */
void freeEntryItem(Item item)
{
  freeEntry((Entry *) item);
}





/*
 * Function:
 *   main
 */
int main(int argc, char *argv[])
{
  FILE * fp;
  LinkedList * lp;

  int sentido = ASCENDENTE;
  int parametro = ID;

  char extOut[] = ".sort";
  char * fileNameIn;
  char * fileNameOut;


  /* Check number of arguments                                    */
  if(argc < 2)
  {
    printf("Usage: lab03b [filename] [arguments opcions]\n");
    exit(1);
  }


  /* Open input file                                              */
  fileNameIn = argv[1];

  argv++;                       /* increments index of argv to point to the
                                   second argument */
  while (*(++argv)) {
    if (strcmp(*argv, "-id") == 0)
      parametro = ID;
    else if (strcmp(*argv, "-age") == 0)
      parametro = AGE;
    else if (strcmp(*argv, "-height") == 0)
       parametro = HEIGHT;
    else if (strcmp(*argv, "-weight") == 0)
       parametro = WEIGHT;
     else if (strcmp(*argv, "-a") == 0)
      sentido = ASCENDENTE;
    else if (strcmp(*argv, "-d") == 0)
      sentido = DESCENDENTE;
    else {
      fprintf(stderr, "Wrong arguments\n");
      exit(3);
    }
  }

  fp  = fopen(fileNameIn, "r");
  if(fp == NULL)
  {
    printf("Open error of input file.\n");
    exit(2);
  }

  /* Read input file and construct linked list with entries       */
  lp = readEntryFile2LinkedList(fp, parametro);

  /* Close input file                                             */
  fclose(fp);


  /* Determine output filename                                    */
  fileNameOut = (char *) malloc(sizeof(char) *
                                 (strlen(fileNameIn) +
                                  strlen(extOut) + 1));
  if(fileNameOut == NULL)
  {
    printf("Memory allocation error for fileNameOut.\n");
    exit(1);
  }

  strcpy(fileNameOut, fileNameIn);
  strcat(fileNameOut, extOut);


  /* Open output file                                             */
  fp  = fopen(fileNameOut, "w");

  if(fp == NULL)
  {
    printf("Open error of input file.\n");
    exit(2);
  }


  /* Write entries to output file                                 */
  if (sentido==ASCENDENTE)
    writeEntryFile(lp, fp);
  else if (sentido==DESCENDENTE)
    writeEntryFileRev(lp, fp);


  /* Free space allocated to fileNameOut                          */
  free(fileNameOut);


  /* Close output file                                            */
  fclose(fp);


  /* Free linked list with entries                                */
  freeLinkedList(lp, freeEntryItem);


  return 0;
}
