#include "../linkedlist.h"
#include "assert.h"
#include <stdio.h>

Status is_int_equal(Element element1, Element element2)
{
  return *(int *)element1 == *(int *)element2;
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

int main(void)
{
  test_add_to_list();
  test_add_to_start();
  test_insert_at();
  return 0;
}