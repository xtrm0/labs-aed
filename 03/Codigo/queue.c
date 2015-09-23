#include "queue.h"
Queue *QueueNew() {
	Queue * Q = malloc(sizeof(Queue)); /*Alloca memoria para a queue*/
	memset(Q,0,sizeof(Queue)); /*Inicializa tudo a NULL*/
	return Q;
}

Element *GetFirst(Queue* Q) {
	Element * ret = Q->first;
	Q->first = Q->first->next;
	return ret;
}

void  InsertLast(Queue* Q, Node* node, int lvl) {
	Element * el = malloc(sizeof(Element));
	el->node = node;
	el->level = lvl;
	el->next = NULL;
	if (Q->first == NULL) {
		Q->first = Q->last = el;
	} else {
		Q->last->next = el;
		Q->last = el;
	}
}
