/* main.c
 * CS 305 lab on queues
 * Authors: Tammy VanDeGrift, Martin Cenek
 * main function tests queue data structure
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* main tests queue data structure */
int main(void) {
  Queue q = initQueue();
  enqueue(q, 5);
  enqueue(q, 8);
  enqueue(q, 4);
  printf("Length: %d\n", length(q));
  printf("Value of head: %d, Value of tail: %d\n", q->head, q->tail);
  QueueData a = dequeue(q);
  printf("Just dequeued: %d\n", a);
  printf("Length: %d\n", length(q));
  QueueData b = dequeue(q);
  printf("Just dequeued: %d\n", b);
  printf("Length: %d\n", length(q));

  enqueue(q, 20);
  printf("Value of head: %d, Value of tail: %d\n", q->head, q->tail);
  enqueue(q, 40);
  enqueue(q, 50);
  enqueue(q, 6);
  enqueue(q, 14);
  printf("Value of head: %d, Value of tail: %d\n", q->head, q->tail);
  printf("Length: %d\n", length(q));

  printf("Queue contents: ");
  while(!empty(q)) {
    printf("%d ", dequeue(q));
  }
  printf("\n");
  freeQueue(q);
  return EXIT_SUCCESS;
}
