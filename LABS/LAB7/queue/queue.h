#ifndef QUEUE_H
#define QUEUE_H

#define MAX_Q 15  // 1 more than what can be stored in the queue

/* data to store into queue */
typedef int QueueData;  // can change type by updating 'int'
                        // or defining a struct

/* queue data structure */
typedef struct QueueTag QueueType;
typedef struct QueueTag* Queue; // pointer to queue struct
                                // so when it is passed, the values
                                // can be updated in functions

struct QueueTag {
  int head;
  int tail;
  QueueData data[MAX_Q]; // space for items in queue
};

/* function prototypes on queues */
Queue initQueue();
int empty(Queue Q);
void enqueue(Queue Q, QueueData d);
QueueData dequeue(Queue Q);
int full(Queue Q);
void freeQueue(Queue Q);
int length(Queue Q);

#endif

