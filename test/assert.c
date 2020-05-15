#include "assert.h"

Status assert_values(List_ptr list, Element *array, int array_length, Matcher matcher)
{
  Status status = Success;
  status = status && (list->length == array_length);
  Node_ptr pwalk = list->first;
  for (int i = 0; i < array_length && pwalk != NULL; i++)
  {
    status = status && matcher(pwalk->element, array[i]);
    pwalk = pwalk->next;
  }
  return status && pwalk == NULL;
}

Status assert_status(Status actual, Status expected)
{
  return actual == expected ? Success : Failure;
}

void print_assert_status(Status status, char *message)
{
  char *status_message = status ? "Success" : "Failure";
  printf("\t%s! %s\n", status_message, message);
}