#include <stdio.h>

/* for prelab 2, question 3 */

int array1[20];
int main()
{
  int x = 0;
  int array2[30];
  int *ptr1 = array1;      // points to first element (element 0) of array1
  int *ptr2 = array2;      // points to first element of array2
  int *ptr3 = &array1[3];  // point to element 3 of array1
  int *ptr4 = &array2[17]; // points to element 17 of array2

  printf("ptr2-ptr1 is %d\n", ptr2 - ptr1);
  printf("ptr3-ptr1 is %d\n", ptr3 - ptr1);
  printf("ptr4-ptr1 is %d\n", ptr4 - ptr1);
  printf("ptr3-ptr2 is %d\n", ptr3 - ptr2);
  printf("ptr4-ptr2 is %d\n", ptr4 - ptr2);
  printf("ptr4-ptr3 is %d\n", ptr4 - ptr3);

  return 0;
}
