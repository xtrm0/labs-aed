/*
 * lab4b.c
 *
 *  Created on: 25/05/2015
 *      Author: mig/afonso
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "LinkedList.h"

typedef struct _graph{
	int N; /*# nodes*/
	int nMax;
	int nZeros;
	int nEdges;
	LinkedList **adjLst;
}Graph;

Item createEdge(int dest, int w){

	Item e_ptr;

	e_ptr = (Item) malloc(sizeof(Edge));
	if(e_ptr == NULL ){
		printf("No memory to allocate Edge!");
		exit(-1);
	}
	e_ptr->dest = dest;
	e_ptr->w    = w ;
	return e_ptr;
}

/**
 *
 */
void destroyEdge( Item item ){
	free((Edge*)item);
}

/**
 *
 */
void destroyGraph( Graph* graph_ptr ){
	int i;
	for( i = 0; i < graph_ptr->N; i++ ){
		freeLinkedList( graph_ptr->adjLst[i], &destroyEdge);
	}
	free(graph_ptr->adjLst);
	free(graph_ptr);
}

/**
 *
 */
Graph* createGraph( int N ){
	Graph* graph_ptr;
	int i;

	graph_ptr = (Graph*)malloc( sizeof(Graph) );
	if( graph_ptr == NULL ){
		printf("No memory for graph allocation!");
		exit(-1);
	}

	graph_ptr->N = N;
	graph_ptr->nEdges = 0;
	graph_ptr->nMax   = 0;
	graph_ptr->nZeros = 0;
	graph_ptr->adjLst = (LinkedList**)malloc(sizeof(LinkedList*)*N);
	for( i = 0; i < N; i++ ){
		graph_ptr->adjLst[i] = initLinkedList();
	}
	return graph_ptr;
}

int comparisonNodesFnc(Item item1, Item item2){
 	Edge* ptr1 = (Edge*)item1;
	Edge* ptr2 = (Edge*)item2;
	if( ptr1->dest < ptr2->dest ){
		return -1;
	}else if(ptr1->dest > ptr2->dest){
		return 1;
	}
	return 0;
}

/**
 *
 */
void addEdgeToGraph( Graph* graph_ptr, int i, int j, int w ){
	Edge* e_ptr;
	int err=0;
	if( w == 0 ){
		graph_ptr->nZeros++;
		return;
	}
	e_ptr = createEdge(j, w);
	graph_ptr->adjLst[i] = insertSortedLinkedList(graph_ptr->adjLst[i],e_ptr,&comparisonNodesFnc, &err);
	if (err!=0) {
		printf("Something went wrong!\n");
		exit(0);
	}
	graph_ptr->nEdges++;
}


FILE *AbreFicheiro ( char *nome, char *mode )
{
  FILE *f;
  f = fopen ( nome, mode );

  if ( f == NULL ) {
    fprintf ( stderr, "ERRO: Não foi possivel abrir o ficheiro %s!\n", nome );
    exit ( -1 );
    /* Error messages are sent to the stderr channel.
       Use an exit number different from 0 (zero) in case of error.*/
  }
  return (f);
}



/**
 *
 */
void closeFile( FILE *fp ){
	fclose(fp);
}


Graph* readGraph( char* filename ){
	Graph* graph_ptr;
	FILE * fp;
	int N, val;
	int l;
	int i, j;
	int r;

	/*Open File*/
	fp = AbreFicheiro(filename, "r");

	/*Read the maximum number of nodes*/
	fscanf(fp,"%d", &N);
	printf("Number of Nodes: %d\n", N);
	graph_ptr = createGraph(N);
	fscanf(fp, "%d", &r);

	for( l = 0; l < r; l++ ){
			fscanf(fp,"%d %d %d", &i, &j, &val);
			addEdgeToGraph( graph_ptr, i, j, val );
			addEdgeToGraph( graph_ptr, j, i, val );
	}

	closeFile(fp);
	return graph_ptr;
}

void writeRam( Graph* graph_ptr, char* filename ){
	FILE * fp;
	Edge* node_ptr;
	LinkedList* list_ptr;
	int i;

	/*Open File*/
	fp = AbreFicheiro( filename, "w");

	fprintf(fp, "%d\n", graph_ptr->N);
	for( i = 0; i < graph_ptr->N; i++){
		list_ptr = graph_ptr->adjLst[i];
		if (list_ptr != NULL) {
			do {
				node_ptr = getItemLinkedList(list_ptr);
				list_ptr = getNextNodeLinkedList( list_ptr );
				fprintf(fp, "%d:%d ", node_ptr->dest, node_ptr->w);
			} while( list_ptr != NULL );
		}
		fprintf(fp, "-1\n");
	}
	closeFile(fp);
}


void printUsage() {
	puts("Utilizacao: \n"
  "     ./lab5b <ficheiro de input>.ram");
}
/**
 *
 */
int main( int argc, char** argv ) {
	Graph* graph_ptr;
	char *filenameIn;
	char *filenameOut;
	int tamanho;

	if( argc != 2 ){
		printUsage();
		exit(1);
	}

	if (strlen(argv[1]) < 4 || strcmp(argv[1] + strlen(argv[1]) - 4, ".ram") != 0) {
    printUsage();
    exit(1);
  }
	filenameIn  = argv[1];
	tamanho = (strlen(filenameIn)+1);
	filenameOut = (char*)malloc( sizeof(char)*(tamanho+1));
	strcpy( filenameOut, filenameIn);
	strcpy( filenameOut+tamanho-4, "ladj");
	printf("Input  File: %s\n", filenameIn);
	printf("Output File: %s\n", filenameOut);
	graph_ptr = readGraph( filenameIn );
	writeRam( graph_ptr, filenameOut );
	destroyGraph( graph_ptr );
	free(filenameOut);
	return EXIT_SUCCESS;
}
