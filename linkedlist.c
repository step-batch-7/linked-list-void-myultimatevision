#include "linkedlist.h"
List_ptr create_list(void)
{
  List_ptr list = malloc(sizeof(LinkedList));
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return list;
}

Node_ptr create_node(Element element)
{
  Node_ptr new_node = malloc(sizeof(Node));
  if (new_node != NULL)
  {
    new_node->element = element;
    new_node->next = NULL;
  }
  return new_node;
}

Status add_to_list(List_ptr list, Element element)
{
  Node_ptr new_node = create_node(element);
  if (new_node == NULL)
  {
    return Failure;
  }
  Node_ptr *ptr_to_set = &list->first;
  if (list->first != NULL)
  {
    ptr_to_set = &list->last->next;
  }
  *ptr_to_set = new_node;
  list->last = new_node;
  list->length++;
  return Success;
}

Status add_to_start(List_ptr list, Element element)
{
  Node_ptr new_node = create_node(element);
  if (new_node == NULL)
  {
    return Failure;
  }
  Node_ptr *ptr_to_set = &list->last;
  if (list->last == NULL)
  {
    list->last = new_node;
  }
  else
  {
    new_node->next = list->first;
  }
  list->first = new_node;
  list->length++;
  return Success;
}

Status insert_at(List_ptr list, Element element, int position)
{

  if (position == 0)
  {
    return add_to_start(list, element);
  }
  if (position == list->length)
  {
    return add_to_list(list, element);
  }

  Node_ptr new_node = create_node(element);
  if (position < 0 || position > list->length || new_node == NULL)
  {
    return Failure;
  }
  int count = 1;
  Node_ptr p_walk = list->first;
  while (count < position)
  {
    p_walk = p_walk->next;
    count++;
  }
  new_node->next = p_walk->next;
  p_walk->next = new_node;
  list->length++;
  return Success;
}

List_ptr reverse(List_ptr list)
{
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    add_to_start(new_list, p_walk->element);
    p_walk = p_walk->next;
  }
  return new_list;
}