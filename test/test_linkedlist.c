#include "../linkedlist.h"
#include "assert.h"
#include <stdio.h>

Status is_int_equal(Element element1, Element element2)
{
  return *(int *)element1 == *(int *)element2;
}

Status does_list_empty(List_ptr list)
{
  return list->first == NULL && list->last == NULL && list->length == 0;
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

void test_add_to_list()
{
  printf("add_to_list\n");
  List_ptr list = create_list();
  int number = 5;
  int expected_array[1] = {5};
  Element expected[1] = {&expected_array[0]};
  Status isStatusEqual = assert_status(add_to_list(list, &number), 1);
  Status areElementsEqual = assert_values(list, expected, 1, &is_int_equal);
  Status status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should add at beginning when list is empty");

  int expected_array1[2] = {5, 3};
  int number2 = 3;
  Element expected1[2] = {&expected_array1[0], &expected_array1[1]};
  isStatusEqual = assert_status(add_to_list(list, &number2), 1);
  areElementsEqual = assert_values(list, expected1, 2, &is_int_equal);
  status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should add at last of the list");
}

void test_add_to_start()
{
  printf("add_to_start\n");
  List_ptr list = create_list();
  int number = 5;
  int expected_array[1] = {5};
  Element expected[1] = {&expected_array[0]};
  Status isStatusEqual = assert_status(add_to_start(list, &number), 1);
  Status areElementsEqual = assert_values(list, expected, 1, &is_int_equal);
  Status status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should add at start when list is empty");

  int expected_array1[2] = {3, 5};
  int number2 = 3;
  Element expected1[2] = {&expected_array1[0], &expected_array1[1]};
  isStatusEqual = assert_status(add_to_start(list, &number2), 1);
  areElementsEqual = assert_values(list, expected1, 2, &is_int_equal);
  status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should add at start of the list");
}

void test_insert_invalid_positions()
{
  List_ptr list = create_list();
  int number = 6;
  Element *expected;

  Status isStatusEqual = assert_status(insert_at(list, &number, -1), 0);
  Status areElementsEqual = assert_values(list, expected, 0, &is_int_equal);
  Status status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should not add to list when position is less than zero");

  isStatusEqual = assert_status(insert_at(list, &number, 1), 0);
  areElementsEqual = assert_values(list, expected, 0, &is_int_equal);
  status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should not add to list when position is more than list length");
}

void test_insert_valid_positions()
{
  List_ptr list = create_list();
  int number = 6;
  int expected_array[1] = {6};
  Element expected[1] = {&expected_array[0]};
  Status isStatusEqual = assert_status(insert_at(list, &number, 0), 1);
  Status areElementsEqual = assert_values(list, expected, 1, &is_int_equal);
  Status status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should add at start when list is empty and position is zero");

  int expected_array1[2] = {6, 8};
  int number2 = 8;
  Element expected1[2] = {&expected_array1[0], &expected_array1[1]};
  isStatusEqual = assert_status(insert_at(list, &number2, 1), 1);
  areElementsEqual = assert_values(list, expected1, 2, &is_int_equal);
  status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should add at end of the list when position is equal to list length");
}
void test_insert_at()
{
  printf("insert at\n");
  test_insert_invalid_positions();
  test_insert_valid_positions();
}

void test_reverse()
{
  printf("reverse\n");
  List_ptr list1 = create_list();
  Element *expected;
  List_ptr list2 = reverse(list1);
  Status are_list1_values_equal = assert_values(list1, expected, 0, is_int_equal);
  Status are_list2_values_equal = assert_values(list2, expected, 0, is_int_equal);
  Status status = are_list1_values_equal & are_list2_values_equal;
  print_assert_status(status, "should create empty list when given list is empty");

  int number = 5;
  add_to_start(list1, &number);
  Element expected1[1] = {&number};
  list2 = reverse(list1);
  are_list1_values_equal = assert_values(list1, expected1, 1, is_int_equal);
  are_list2_values_equal = assert_values(list2, expected1, 1, is_int_equal);
  status = are_list1_values_equal & are_list2_values_equal;
  print_assert_status(status, "should create list and return same list when list length is 1");

  int number1 = 8;
  add_to_start(list1, &number1);
  Element list1_expected[2] = {&number1, &number};
  Element list2_expected[2] = {&number, &number1};
  list2 = reverse(list1);
  are_list1_values_equal = assert_values(list1, list1_expected, 2, is_int_equal);
  are_list2_values_equal = assert_values(list2, list2_expected, 2, is_int_equal);
  status = are_list1_values_equal & are_list2_values_equal;
  print_assert_status(status, "should create list and return reverse of given list");
}

void test_remove_from_start()
{
  printf("remove_from_start\n");
  List_ptr list = create_list();
  Element *expected = malloc(sizeof(Element));

  Element element_removed = remove_from_start(list);
  Status are_elements_equal = element_removed == NULL;
  Status are_list_values_equal = assert_values(list, expected, 0, is_int_equal);
  Status status = are_elements_equal && are_list_values_equal && does_list_empty(list);
  print_assert_status(status, "should return NULL when list is empty");

  int number = 5;
  add_to_start(list, &number);

  int *expected_element = malloc(sizeof(int));
  *expected_element = 5;
  element_removed = remove_from_start(list);
  are_elements_equal = is_int_equal(element_removed, expected_element);
  are_list_values_equal = assert_values(list, expected, 0, is_int_equal);
  status = are_elements_equal && are_list_values_equal && does_list_empty(list);
  print_assert_status(status, "should remove from start and make list empty when list have one element");

  int number1 = 8;
  add_to_start(list, &number);
  add_to_start(list, &number1);
  int *expected1_element = malloc(sizeof(int));
  *expected1_element = 8;
  element_removed = remove_from_start(list);
  Element *expected1 = malloc(sizeof(Element));
  *expected1 = &number;
  are_elements_equal = is_int_equal(element_removed, expected1_element);
  are_list_values_equal = assert_values(list, expected1, 1, is_int_equal);
  status = are_elements_equal && are_list_values_equal;
  print_assert_status(status, "should remove element from start");
}

void test_remove_from_end()
{
  printf("remove_from_end\n");
  List_ptr list = create_list();
  Element *expected = malloc(sizeof(Element));

  Element element_removed = remove_from_end(list);
  Status are_elements_equal = element_removed == NULL;
  Status are_list_values_equal = assert_values(list, expected, 0, is_int_equal);
  Status status = are_elements_equal && are_list_values_equal && does_list_empty(list);
  print_assert_status(status, "should return NULL when list is empty");

  int number = 5;
  add_to_start(list, &number);

  int *expected_element = malloc(sizeof(int));
  *expected_element = 5;
  element_removed = remove_from_end(list);
  are_elements_equal = is_int_equal(element_removed, expected_element);
  are_list_values_equal = assert_values(list, expected, 0, is_int_equal);
  status = are_elements_equal && are_list_values_equal && does_list_empty(list);
  print_assert_status(status, "should remove from end and make list empty when list have one element");

  int number1 = 8;
  add_to_start(list, &number);
  add_to_start(list, &number1);
  int *expected1_element = malloc(sizeof(int));
  *expected1_element = 5;
  element_removed = remove_from_end(list);
  Element *expected1 = malloc(sizeof(Element));
  *expected1 = &number1;
  are_elements_equal = is_int_equal(element_removed, expected1_element);
  are_list_values_equal = assert_values(list, expected1, 1, is_int_equal);
  status = are_elements_equal && are_list_values_equal;
  print_assert_status(status, "should remove element from end");
}

void remove_from_invalid_positions()
{
  List_ptr list = create_list();
  Element *expected = malloc(sizeof(Element));

  Element element_removed = remove_at(list, 1);
  Status are_elements_equal = element_removed == NULL;
  Status are_list_values_equal = assert_values(list, expected, 0, is_int_equal);
  Status status = are_elements_equal && are_list_values_equal && does_list_empty(list);
  print_assert_status(status, "should return NULL when list is empty");

  int number = 5;
  add_to_start(list, &number);
  Element expected1[1] = {&number};
  element_removed = remove_at(list, -1);
  are_elements_equal = element_removed == NULL;
  are_list_values_equal = assert_values(list, expected1, 1, is_int_equal);
  status = are_elements_equal && are_list_values_equal;
  print_assert_status(status, "should return NULL when position is less than zero");

  int number1 = 8;
  add_to_start(list, &number1);
  Element expected2[2] = {&number1, &number};
  element_removed = remove_at(list, 3);
  are_elements_equal = element_removed == NULL;
  are_list_values_equal = assert_values(list, expected2, 2, is_int_equal);
  status = are_elements_equal && are_list_values_equal;
  print_assert_status(status, "should return NULL when position is more than length");
}

void remove_from_valid_positions()
{
  List_ptr list = create_list();
  int numbers[4] = {4, 5, 6, 8};
  add_to_start(list, &numbers[0]);
  add_to_start(list, &numbers[1]);
  add_to_start(list, &numbers[2]);
  add_to_start(list, &numbers[3]);

  Element element_removed = remove_at(list, 0);
  Element expected[3] = {&numbers[2], &numbers[1], &numbers[0]};
  Status are_elements_equal = is_int_equal(element_removed, &numbers[3]);
  Status are_list_values_equal = assert_values(list, expected, 3, is_int_equal);
  Status status = are_elements_equal && are_list_values_equal;
  print_assert_status(status, "should remove element at start when position is zero");

  element_removed = remove_at(list, 1);
  Element expected1[2] = {&numbers[2], &numbers[0]};
  are_elements_equal = is_int_equal(element_removed, &numbers[1]);
  are_list_values_equal = assert_values(list, expected1, 2, is_int_equal);
  status = are_elements_equal && are_list_values_equal;
  print_assert_status(status, "should remove element in the list when position is between zero and length");

  Element expected2[1] = {&numbers[2]};
  element_removed = remove_at(list, 1);
  are_elements_equal = is_int_equal(element_removed, &numbers[0]);
  are_list_values_equal = assert_values(list, expected2, 1, is_int_equal);
  status = are_elements_equal && are_list_values_equal;
  print_assert_status(status, "should remove element at start when position is equal to list length");
}

void test_remove_at()
{
  printf("remove_at\n");
  remove_from_invalid_positions();
  remove_from_valid_positions();
}

void test_remove_first_occurrence()
{
  printf("remove_first_occurrence\n");
  List_ptr list = create_list();
  int numbers[4] = {4, 5, 6, 4};

  Element element_removed = remove_first_occurrence(list, &numbers[1], &is_int_equal);
  Element *expected;
  Status are_elements_equal = element_removed == NULL;
  Status are_list_values_equal = assert_values(list, expected, 0, &is_int_equal);
  Status status = are_elements_equal && are_list_values_equal;
  print_assert_status(status, "should return NULL when list is empty");

  add_to_start(list, &numbers[0]);
  add_to_start(list, &numbers[1]);
  add_to_start(list, &numbers[2]);
  add_to_start(list, &numbers[3]);

  int number = 10;
  element_removed = remove_first_occurrence(list, &number, &is_int_equal);
  Element expected1[4] = {&numbers[3], &numbers[2], &numbers[1], &numbers[0]};
  are_elements_equal = element_removed == NULL;
  are_list_values_equal = assert_values(list, expected1, 4, &is_int_equal);
  status = are_elements_equal && are_list_values_equal;
  print_assert_status(status, "should not remove element in the list when given element is not present");

  Element expected2[3] = {&numbers[3], &numbers[1], &numbers[0]};
  element_removed = remove_first_occurrence(list, &numbers[2], &is_int_equal);
  are_elements_equal = is_int_equal(element_removed, &numbers[2]);
  are_list_values_equal = assert_values(list, expected2, 3, &is_int_equal);
  status = are_elements_equal && are_list_values_equal;
  print_assert_status(status, "should remove first occurrence of given element");
}

void test_remove_all_occurrences()
{
  printf("remove_all_occurrences\n");
  List_ptr list = create_list();
  int numbers[4] = {4, 5, 6, 4};

  List_ptr removed_elements_list = remove_all_occurrences(list, &numbers[1], &is_int_equal);
  Element *expected;
  Status are_list_values_equal = assert_values(list, expected, 0, &is_int_equal);
  Status status = does_list_empty(removed_elements_list) && are_list_values_equal;
  print_assert_status(status, "should return NULL when list is empty");

  add_to_start(list, &numbers[0]);
  add_to_start(list, &numbers[1]);
  add_to_start(list, &numbers[2]);
  add_to_start(list, &numbers[3]);

  int number = 10;
  removed_elements_list = remove_all_occurrences(list, &number, &is_int_equal);
  Element expected1[4] = {&numbers[3], &numbers[2], &numbers[1], &numbers[0]};
  are_list_values_equal = assert_values(list, expected1, 4, &is_int_equal);
  status = does_list_empty(removed_elements_list) && are_list_values_equal;
  print_assert_status(status, "should not remove element in the list when given element is not present");

  Element expected2[3] = {&numbers[3], &numbers[1], &numbers[0]};
  Element removed_elements[1] = {&numbers[2]};
  removed_elements_list = remove_all_occurrences(list, &numbers[2], &is_int_equal);
  Status are_elements_in_list_equal = assert_values(removed_elements_list, removed_elements, 1, &is_int_equal);
  are_list_values_equal = assert_values(list, expected2, 3, &is_int_equal);
  status = are_elements_in_list_equal && are_list_values_equal;
  print_assert_status(status, "should remove occurrence of given element when one matched element is present");

  Element expected3[1] = {&numbers[1]};
  Element removed_elements1[2] = {&numbers[0], &numbers[0]};
  removed_elements_list = remove_all_occurrences(list, &numbers[0], is_int_equal);
  are_elements_in_list_equal = assert_values(removed_elements_list, removed_elements1, 2, is_int_equal);
  are_list_values_equal = assert_values(list, expected3, 1, is_int_equal);
  status = are_elements_in_list_equal && are_list_values_equal;
  print_assert_status(status, "should remove all occurrences of given element");
}

void test_add_unique()
{
  printf("add_unique\n");
  List_ptr list = create_list();
  int number = 5;
  int expected_array[1] = {5};
  Element expected[1] = {&expected_array[0]};
  Status isStatusEqual = assert_status(add_unique(list, &number, &is_int_equal), 1);
  Status areElementsEqual = assert_values(list, expected, 1, &is_int_equal);
  Status status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should add to list when list is empty");

  int expected_array1[2] = {5, 3};
  int number2 = 3;
  Element expected1[2] = {&expected_array1[0], &expected_array1[1]};

  isStatusEqual = assert_status(add_unique(list, &number2, &is_int_equal), 1);
  areElementsEqual = assert_values(list, expected1, 2, &is_int_equal);
  status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should add to end when element is not present in the list");

  isStatusEqual = assert_status(add_unique(list, &number2, &is_int_equal), 0);
  areElementsEqual = assert_values(list, expected1, 2, &is_int_equal);
  status = isStatusEqual && areElementsEqual;
  print_assert_status(status, "should not add element when element is already present in the list");
}
void test_clear_list()
{
  printf("clear_list\n");
  List_ptr list = create_list();
  Status isStatusEqual = assert_status(clear_list(list), Failure);
  Status status = isStatusEqual && does_list_empty(list);
  print_assert_status(status, "should return failure when list is empty");

  int numbers[2] = {5, 4};
  add_to_list(list, &numbers[0]);
  add_to_list(list, &numbers[1]);
  isStatusEqual = assert_status(clear_list(list), Success);
  status = isStatusEqual && does_list_empty(list);
  print_assert_status(status, "should clear the list and return Success");
}

void test_map()
{
  printf("map\n");
  List_ptr list = create_list();
  print_assert_status(does_list_empty(map(list, &square)), "should give empty list when given list is empty");

  int array[3] = {1, 2, 3};
  add_to_list(list, &array[0]);
  add_to_list(list, &array[1]);
  add_to_list(list, &array[2]);
  int expected_array[3] = {1, 4, 9};
  Element expected[3] = {&expected_array[0], &expected_array[1], &expected_array[2]};
  Status are_list_values_equal = assert_values(map(list, &square), expected, 3, is_int_equal);
  print_assert_status(are_list_values_equal, "should give the squares of elements in the list");
}

void test_filter()
{
  printf("filter\n");
  int *empty_array;

  List_ptr list = create_list();
  print_assert_status(does_list_empty(filter(list, &is_even)), "should give empty list when given list is empty");

  int array[3] = {1, 3, 7};
  add_to_list(list, &array[0]);
  add_to_list(list, &array[1]);
  add_to_list(list, &array[2]);

  print_assert_status(does_list_empty(filter(list, &is_even)), "should give the empty list when list has no even numbers");

  int array2[3] = {2, 4, 5};
  add_to_list(list, &array2[0]);
  add_to_list(list, &array2[1]);
  add_to_list(list, &array2[2]);
  Element expected_array[2] = {&array2[0], &array2[1]};
  Status status = assert_values(filter(list, &is_even), expected_array, 2, is_int_equal);
  print_assert_status(status, "should filter the even numbers in the array");
}

void test_reduce()
{
  printf("reduce\n");

  int *empty_array;

  List_ptr list = create_list();
  int initial_value = 0;
  int expected_value = 0;

  Status status = is_int_equal(reduce(list, &initial_value, &sum_of_numbers), &expected_value);
  print_assert_status(status, "should give initial value when array is empty");

  int array[4] = {1, 2, 3, 4};
  add_to_list(list, &array[0]);
  add_to_list(list, &array[1]);
  add_to_list(list, &array[2]);
  add_to_list(list, &array[3]);
  initial_value = 0;
  expected_value = 10;
  status = is_int_equal(reduce(list, &initial_value, &sum_of_numbers), &expected_value);
  print_assert_status(status, "should give the sum of elements of the array");
}

int main(void)
{
  test_add_to_list();
  test_add_to_start();
  test_insert_at();
  test_reverse();
  test_remove_from_start();
  test_remove_from_end();
  test_remove_at();
  test_remove_first_occurrence();
  test_remove_all_occurrences();
  test_add_unique();
  test_clear_list();
  test_map();
  test_filter();
  test_reduce();
  return 0;
}