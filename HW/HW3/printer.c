#include "printer.h"
#include "printJob.h"
#include "stdio.h"
#include "stdlib.h"

void add_job(printer* p, char* p_name, char* j_name, int size) {
    if (p->online == false) return;



    return;
}


void update_printer();

void offline(printer* p) {
    weave(p); //weaves printjobs into other printers
    p->online = false;
    return;
}

/* online()
 * Sets the given printer online if it is offline
 */
void online(printer* p) {
    if (p->online == false)
    {
        p->online = true;
    }
}

void print(printer* p) {
    printf("<%s>:<spd: %d>->", p->name, p->speed);
    for (int i = 0; i < queue_length(p->printQueue); i++)
    {
        //traverse between all
        return;
    }
    return;
}

void weave(printer* p) {
    //go through printjobs and weave them into other printers round robin
}

int queue_length(printJob* j) {
    int length = 0;

    printJob* i;
    i = j;
    while(i != NULL){
        i = i->next;
        length++;
    }
    return length;
}

