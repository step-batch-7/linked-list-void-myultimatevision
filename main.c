#include "linkedlist.h"

Status is_int_equal(Element element1, Element element2)
{
  return *(int *)element1 == *(int *)element2;
}

Element square(Element data)
{
  int number = *(int *)data;
  int *square = malloc(sizeof(int));
  *square = number * number;
  return square;
}

Status is_even(Element data)
{
  int number = *(int *)data;
  return number % 2 == 0;
}

Element sum_of_numbers(Element initial, Element data)
{
  int number = *(int *)data;
  int *sum = malloc(sizeof(int));
  *sum = *(int *)initial + number;
  return sum;
}

void print_element(Element element)
{
  printf("%d\n", *(int *)element);
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

  List_ptr mapped_list = map(list, &square);
  List_ptr filtered_list = filter(list, &is_even);
  int initial = 0;
  Element sum = reduce(list, &initial, &sum_of_numbers);
  forEach(list, print_element);
  return 0;
}
