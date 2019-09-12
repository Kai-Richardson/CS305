#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"

/* inventory struct */
typedef struct inventory
{
    item* items;
    int* stock;
    int num_items;
    int max_items;

} inventory;

/* function prototypes */
inventory *create_inventory(int max_it);
int add_item(inventory *rec, item it, int count);
void sold_item(inventory *rec, int item_id);
double calc_min_price(inventory *inv);
double calc_max_price(inventory *inv);
double calc_inv_value(inventory *inv);
int delete_item(inventory *inv, int item_id);
void print_inventory(inventory *inv);
void free_inventory(inventory *inv);
void remove_element(item *array, int index, int array_length);

#endif
