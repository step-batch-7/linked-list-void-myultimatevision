#include "linkedlist.h"

int main()
{
  List_ptr list = create_list();
  int *number = malloc(sizeof(int));
  *number = 5;
  add_to_list(list, number);
  number = malloc(sizeof(int));
  *number = 3;
  add_to_start(list, number);
  number = malloc(sizeof(int));
  *number = 2;
  insert_at(list, number, 2);
  List_ptr list2 = reverse(list);
  return 0;
}
