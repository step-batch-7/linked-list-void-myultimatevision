#include "linkedlist.h"

Status is_int_equal(Element element1, Element element2)
{
  return *(int *)element1 == *(int *)element2;
}

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
  Element element = remove_from_start(list2);
  printf("%d\n", *(int *)element);

  element = remove_from_end(list2);
  printf("%d\n", *(int *)element);

  element = remove_at(list2, 0);
  printf("%d\n", *(int *)element);

  element = remove_first_occurrence(list, number, is_int_equal);
  printf("%d\n", *(int *)element);
  return 0;
}
