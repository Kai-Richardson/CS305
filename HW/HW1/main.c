/* CS 305, Fall 201
 * HOMEWORK 1
 *
 * main.c
 * author: Martin Cenek
 * Fall 201 -
 * v1: 09/01/201
 * creates inventory and items
 * main.c driver provides tests of inventory and item
 *
 * compile with inventory.c and item.c
 * gcc inventory.c item.c main.c
 * OR
 * gcc -o store inventory.c item.c main.c
 *
 * If creating store object file, then run with command:
 * store
 * Otherwise, run with command:
 * a.out
 */

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "item.h"

/* prototypes */
int run_test(void);

/* main
 * using void paramater since we are not using command line arguments
 * for this program
 */
int main(void)
{
  run_test();
}

/* run_test
 * runs a test, creating store inventories and adding/deleting items
 */
int run_test(void)
{
  /* create two store inventories */
  /* note: using pointers for store inventories so the inventory data can be
     modified */
  inventory *rei = create_inventory(-3);
  inventory *amazon = create_inventory(2);

  // create items
  // note: not using pointers to items since once they are created
  // they are not later modified -- only used as data
  // create items
  item gloves = create_item(10.25, "WarmFingers", 1);
  item hat = create_item(5.75, "WarmEars", 2);
  item boots = create_item(35.22, "KeepOnStomping", 3);
  item skateboard = create_item(67.04, "PlankOnWheels", 4);
  item skis = create_item(352.00, "QuickPlanks", 5);
  item tent = create_item(223.47, "Fortress007", 6);
  item slBag = create_item(125.17, "WarmDreams", 7);
  item slPad = create_item(63.58, "SoftDreams", 8);
  item canoe = create_item(458.46, "QuickDownTheRiver", 9);
  item stove = create_item(25.14, "Burn Hot", 10);
  item mug = create_item(8.25, "Big brown mug", 11);
  item backpack = create_item(125.54, "Heavy sturdy backpack", 12);

  // put some items into inventory
  add_item(rei, gloves, 10);
  add_item(rei, hat, 2);
  add_item(rei, boots, -1);
  add_item(rei, skateboard, 0);

  // for write-up: draw a picture of what rei's store inventory looks like

  // print inventory
  print_inventory(rei);

  // put more items into rei's inventory
  add_item(rei, skis, 5);
  add_item(rei, tent, 2);
  add_item(rei, slBag, 10);
  add_item(rei, slPad, 12);

  // print inventory
  print_inventory(rei);

  // add items
/*  add_item(rei, canoe, 4);
  add_item(rei, stove, 6);

  // print inventory
  print_inventory(rei);

  // add items to amazon
  add_item(amazon, hat, 7);
  add_item(amazon, tent, 3);
  print_inventory(amazon);

  // add another item
  add_item(amazon, slBag, 4);
  print_inventory(amazon);

  // put more items in
  add_item(rei, canoe, 2);
  printf("Trying to add alrady existing item\n");
  add_item(rei, canoe, 4);
  add_item(rei, mug, 7);
  add_item(rei, backpack, 3);

  // print the inventory
  print_inventory(rei);

  //item_sold();
  //print the inventory
  print_inventory(rei);

  // at point to draw picture 1 in report

  // delete items
  //printf("Trying to delete item with ID 11\n");
  delete_item(rei, 11);
  sold_item(rei, 9);
  // print the inventory
  print_inventory(rei);

  sold_item(rei, 9);
  sold_item(rei, 9);
  sold_item(rei, 9);
  sold_item(rei, 9);
  sold_item(rei, 999);
  // at point to draw picture 2 in report

  // delete item
  //printf("Trying to delete item 222\n");
  delete_item(rei, 222);

  // add items to amazon
  add_item(amazon, backpack, 2);
  add_item(amazon, mug, -2);

  // print inventory
  print_inventory(amazon);

  // add another items to amazon
  add_item(amazon, gloves, 3);
  add_item(amazon, skis, 2);

  // delete items
  //printf("Trying to delete item 11\n");
  delete_item(amazon, 11);
  //printf("Trying to delete item 12\n");
  delete_item(amazon, 12);
  print_inventory(amazon);
  //printf("Trying to delete item 6\n");
  delete_item(amazon, 6);
  print_inventory(amazon);
  //printf("Trying to add item in the store\n");
  add_item(amazon, hat, 3);
  print_inventory(amazon);

  //printf("Trying to delete item 2\n");
  delete_item(amazon, 2);
  print_inventory(amazon);

  // add items to amazon
  add_item(amazon, slBag, 5);
  add_item(amazon, slPad, 5);
  print_inventory(amazon);
*/
  // free memory for store inventories
  free_inventory(amazon);
  free_inventory(rei);

  return EXIT_SUCCESS;
} // end main
