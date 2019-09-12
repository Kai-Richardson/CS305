#ifndef ITEM_H
#define ITEM_H

#define MAX_NAME_LENGTH 30

/* item struct */
typedef struct item
{
    double price;
    char* name; //[MAX_NAME_LENGTH + 1]
    int id_number;

} item;

/* function prototypes */
item create_item(double, char *, int);
void print(item);

#endif
