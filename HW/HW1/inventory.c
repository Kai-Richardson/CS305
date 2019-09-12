/* CS 305
 * HW1
 * @author: Kai Richardson
 */

#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "inventory.h"

inventory* create_inventory(int max_it) {
    inventory* inv = (inventory*)malloc(sizeof(struct inventory));

    inv->num_items = 0;

    if (max_it > 0) {
        inv->max_items = max_it;
    }
    else {
        inv->max_items = 10;
    }

    item* items = (item*)malloc(sizeof(struct item) * inv->max_items);

    int* stock = (int*)malloc(sizeof(int) * inv->max_items);

    return inv;

}

int add_item(inventory *rec, item it, int count) {
    if (rec->num_items >= rec->max_items)
    {
        printf("Cannot add another item to inventory. Max inventory size exceeded.");
        return -1;
    }
    else if (it.id_number) //doesn't exist in inventory rec
    {
        rec->items[rec->num_items] = it; //stores in array
        rec->num_items += count; //says ++ in instructions, this makes more sense though
        return 0;
    }
    else //already exists
    {
        printf("Canot add item to inventory. Duplicate item ID number.");
    }




}
void sold_item(inventory *rec, int item_id) {

}
double calc_min_price(inventory *inv) {

}
double calc_max_price(inventory *inv) {

}
double calc_inv_value(inventory *inv) {

}
int delete_item(inventory *inv, int item_id) {

}
void print_inventory(inventory *inv) {

}
void free_inventory(inventory *inv) {

}