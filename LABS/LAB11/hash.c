/* CS 305
 * Hashing lab
 * Author: Tammy VanDeGrift, Martin Cenek, hash function: Steve Vegdahl
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define DELETE "D"

/* hash table struct */
typedef struct HT {
  unsigned int size;		 // max size of hash table
  unsigned int numItems;	 // num items in hash table
  char ** table;			 // array of strings
} HT;

// prototypes
HT * initTable(int n);
void freeTable(HT * t);
int insert(char * key, HT * t);
int find(char * key, HT * t);
int delete(char * key, HT * t);
void printTable(HT * t);
unsigned int hash(char *key);


/* initTable returns pointer to empty hash table */
HT * initTable(int n) {
  HT * t = (HT *)malloc(sizeof(HT));
  if(t == NULL || n <= 0) {
	return NULL;  // memory not allocated
  }
  t->size = n;
  t->numItems = 0;
  t->table = (char **)malloc(sizeof(char *) * n);
  if(t->table == NULL) {
	return NULL;  // memory not allocated
  }
  int i;
  for(i = 0; i < t->size; i++) {
	t->table[i] = NULL;
  }
  return t;
}

/* freeTable frees all memory associated with the hash table */
void freeTable(HT * t) {
  if(t == NULL) return;
  free(t->table);
  free(t);
  t = NULL;
}

/* insert puts key into hash table
   if did not get inserted, return 0; else, return 1 */
int insert(char * key, HT * t) {
  if(key == NULL || t == NULL || t->numItems == t->size) {
	printf("%s not inserted.\n", key);
	return 0;
  }
  if(find(key, t) >= 0) {
	printf("%s is already in hash table.\n", key);
	return 0;
  }
  // hash the key using the hash function and find location
  unsigned int hashValue = hash(key);
  unsigned int location = hashValue % t->size;
  while(t->table[location] != NULL && t->table[location] != DELETE) {
	location = location + 1;
	location = location % t->size;	// wrap-around if necessary
  }
  // at this point, we have a location that is empty or has a delete flag
  t->table[location] = key;
  t->numItems++;
  return 1;
}

/* find searches for the key in the hash table and returns -1
   if not found and the array index of the key if it is found */
int find(char * key, HT * t) {

	if(key == NULL || t == NULL) return -1;

	unsigned int hashValue = hash(key);
	unsigned int location = hashValue % t->size;
	unsigned int originalLocation = location;

	while(t->table[location] != NULL) {
		if(strcmp(key, t->table[location]) != 0) {
			location = location + 1;
			location = location % t->size;
		}
		else {
			return location;
		}

		if(location == originalLocation) {
			return -1;
		}
	}
  return -1;
}

/* delete removes the key from the hash table */
int delete(char * key, HT * t) {
  if(key == NULL || t == NULL) {
	return 0;
  }
  int location = find(key, t);
  if(location < 0) {  // key not in hash table
	return 0;
  }
  t->table[location] = DELETE;
  t->numItems--;
  return 1;
}

/* printTable prints the locations and keys of non-null cells
   shows "D" for cells that have deleted items */
void printTable(HT * t) {
  int i = 0;
  if(t == NULL) {
	return;
  }
  printf("\nHASH TABLE CONTENTS:\n");
  printf("Num items: %d\n", t->numItems);
  printf("-----------------------\n");

  while (i < t->size)
  {
    printf("Slot %d: %s\n", i, t->table[i]);
    i++;
  }

  printf("-----------------------\n\n");
}

/* hash function maps strings to unsigned ints */
unsigned int hash(char *key) {
  unsigned int rtnVal = 3253;
  char *p;
  for (p = key; *p != '\0'; p++) {
	rtnVal *= 28277;
	rtnVal += *p * 2749;
  }
  return rtnVal;
}

/* main creates hash table, inserts items, deletes items, and finds items */
int main(void) {
  unsigned int N = 11;	//default hash table size
  HT * ht = initTable(N);
  int ok1 = insert("orange", ht);
  int ok2 = insert("banana", ht);
  int ok3 = insert("strawberry", ht);
  int ok4 = insert("pineapple", ht);
  int ok5 = insert("orange", ht);
  int ok6 = insert("chocolate", ht);
  int ok7 = insert("rice", ht);
  int ok8 = insert("corn", ht);
  int ok9 = insert("papaya", ht);

  printTable(ht);
  int loc1 = find("orange", ht);
  int loc2 = find("mango", ht);

  int d1 = delete("orange", ht);
  int d2 = delete("banana", ht);
  int d3 = delete("popcorn", ht);

  printTable(ht);

  int ok10 = insert("peanuts", ht);
  int ok11 = insert("green beans", ht);

  printTable(ht);

  int loc3 = find("peanuts", ht);
  int loc4 = find("orange", ht);

  int ok12 = insert("tangerine", ht);
  int ok13 = insert("hummus", ht);
  int ok14 = insert("yogurt", ht);

  printTable(ht);

  int loc5 = find("yogurt", ht);
  int loc6 = find("cereal", ht);

  freeTable(ht);
  return EXIT_SUCCESS;
}
