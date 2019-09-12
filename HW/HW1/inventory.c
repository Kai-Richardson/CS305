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
    if (item_id) { //is found in rec
        if (rec->stock[item_id] <= 0) {
            printf("Cannot sell item that has 0 inventory count.");
            return;
        }
        //rec.found --;
        printf("Item sold.");
    }
    else { //not found
        printf("Cannot sell item that is not in the inventory.");
    }

}

int delete_item(inventory *rec, int item_id) {
    if(rec->num_items <= 0) {
        printf("Item number %d not found. Store is empty.", item_id);
        return -1;
    }
    for (int i = 0; i < rec->num_items; i++)
    {
        if (rec->items[i].id_number == item_id)
        {
            //delete + shift
            rec->num_items--;
            return 0;
        }
    }

    //item not found
    printf("Item w/ number %d not found in the inventory.", item_id);
    return -1;

}

double calc_min_price(inventory *inv) {
    double found = __DBL_MAX__;

    for (int i = 0; i < inv->num_items; i++)
    {
        if (inv->items[i].price < found)
        {
            found = inv->items[i].price;
        }
    }
    return found;
}
double calc_max_price(inventory *inv) {
    double found = 0;

    for (int i = 0; i < inv->num_items; i++)
    {
        if (inv->items[i].price > found)
        {
            found = inv->items[i].price;
        }
    }
    return found;
}
double calc_inv_value(inventory *inv) {
    double value = 0;

    for (int i = 0; i < inv->num_items; i++)
    {
        value += inv->items[i].price * inv->stock[i];
    }
    return value;
}

void print_inventory(inventory *inv) {
    printf("Store inventory:\n");
    printf("\tprice\tname\tid\tstock");

    for (int i = 0; i < inv->num_items; i++)
    {
        print(inv->items[i]);
    }

    printf("The total inventory is worth: %.2f", calc_inv_value);
    printf("The cheapest item store carries is: %.2f", calc_min_price);
    printf("The most expensive item store carries is: %.2f", calc_max_price);

}
void free_inventory(inventory *inv) {
    free(inv->items);
    free(inv->stock);
    free(inv);
}