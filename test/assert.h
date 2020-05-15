#include "../linkedlist.h"
#include <stdio.h>

Status assert_status(Status actual, Status expected);
Status assert_values(List_ptr list, Element *array, int array_length, Matcher matcher);
void print_assert_status(Status status, char *message);
