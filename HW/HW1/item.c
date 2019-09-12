/* CS 305
 * HW1
 * @author: Kai Richardson
 */

#include <stdio.h>
#include "item.h"
#include "inventory.h"
#include <string.h>

item create_item(double price, char *namearg, int id_number)
{
    item it;

    //check for null/negative prices
    if (price > 0)
    {
        it.price = price;
    }
    else
    {
        it.price = 0; //default price of free
    }

    //check for null/negative id_number
    if (id_number > -1)
    {
        it.id_number = id_number;
    }
    else
    {
        it.id_number = 0; //default
    }

    //only copy MAX_NAME_LENGTH amt of chars
    strncpy(it.name,namearg,MAX_NAME_LENGTH);

    return it;
}

void print(item it) {
    printf("Item %.2f\t%s\t%i\t", it.price, it.name, it.id_number);
}
