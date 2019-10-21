/* queue.c
 * CS 305 lab on queues
 * Authors: Tammy VanDeGrift, Martin Cenek
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* initializes empty queue */
Queue initQueue() {
  Queue q = malloc(sizeof(QueueType));
  q->head = 0;
  q->tail = 0;
  return q;
}

/* returns 1 if queue is empty and 0 otherwise */
int empty(Queue Q) {
  return (Q->head == Q->tail);
}
/* puts data item d into queue */
void enqueue(Queue Q, QueueData d) {
  if(full(Q)) {
    printf("Queue is full. Did not add item.\n");
    return;
  }
  Q->tail++;
  Q->tail = Q->tail % MAX_Q; // in case it goes off array
  Q->data[Q->tail] = d;
}

/* removes data item from queue */
QueueData dequeue(Queue Q) {
  if(empty(Q)) {
    printf("Attempting to remove from empty queue\n");
    exit(1);
  }
  Q->head++;
  Q->head = Q->head % MAX_Q; // in case it goes off array
  return Q->data[Q->head];
}

//LAB EXERCISE
/* checks if queue is full */
int full(Queue Q) {
  if (Q->tail % MAX_Q == Q->head-1)
  {
    return 1;
  }
  return 0;
}

void freeQueue(Queue Q) {
  free(Q);
}

int length(Queue Q) {
  if (Q->tail >= Q->head)
  {
    return Q->tail - Q->head;
  }
  else
  {
    return Q->head + Q->tail;
  }


}