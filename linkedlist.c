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

Element remove_from_start(List_ptr list)
{
  if (list->first == NULL)
  {
    return NULL;
  }
  Node_ptr p_walk = list->first;
  Element elementRemoved = p_walk->element;
  list->first = p_walk->next;
  if (p_walk == list->last)
  {
    list->last = NULL;
  }
  free(p_walk);
  list->length--;
  return elementRemoved;
}

Element remove_from_end(List_ptr list)
{
  if (list->last == NULL)
  {
    return NULL;
  }
  Prev_Current_Pair *pair = malloc(sizeof(Prev_Current_Pair));
  pair->prev = NULL;
  pair->current = list->first;

  while (pair->current != list->last)
  {
    pair->prev = pair->current;
    pair->current = pair->current->next;
  }
  Node_ptr *ptr_to_set = &list->first;
  if (pair->current != list->first)
  {
    ptr_to_set = &pair->prev->next;
  }
  *ptr_to_set = NULL;
  Element element_removed = pair->current->element;
  free(pair->current);
  list->last = pair->prev;
  list->length--;
  return element_removed;
}

Element remove_at(List_ptr list, int position)
{
  if (list->last == NULL || position < 0 || position >= list->length)
  {
    return NULL;
  }
  if (position == 0)
  {
    return remove_from_start(list);
  }
  if (position == list->length - 1)
  {
    return remove_from_end(list);
  }

  Prev_Current_Pair *pair = malloc(sizeof(Prev_Current_Pair));
  pair->prev = NULL;
  pair->current = list->first;
  int count = 0;

  while (count != position)
  {
    pair->prev = pair->current;
    pair->current = pair->current->next;
    count++;
  }
  Element element_removed = pair->current->element;
  pair->prev->next = pair->current->next;
  free(pair->current);
  list->length--;
  return element_removed;
}

Element remove_first_occurrence(List_ptr list, Element element, Matcher matcher)
{
  Node *p_walk = list->first;
  int position = 0;
  while (p_walk != NULL && !matcher(p_walk->element, element))
  {
    p_walk = p_walk->next;
    position++;
  }
  return p_walk == NULL ? NULL : remove_at(list, position);
}

List_ptr remove_all_occurrences(List_ptr list, Element element, Matcher matcher)
{
  List_ptr removed_elements_list = create_list();
  Element element_removed = remove_first_occurrence(list, element, matcher);
  while (element_removed != NULL)
  {
    add_to_list(removed_elements_list, element);
    element_removed = remove_first_occurrence(list, element, matcher);
  }
  return removed_elements_list;
}

Status add_unique(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr p_walk = list->first;
  while (p_walk != NULL && !matcher(p_walk->element, element))
  {
    p_walk = p_walk->next;
  }
  return p_walk == NULL ? add_to_list(list, element) : Failure;
}

Status clear_list(List_ptr list)
{
  if (list->first == NULL)
  {
    return Failure;
  }
  Prev_Current_Pair *pair = malloc(sizeof(Prev_Current_Pair));
  pair->prev = NULL;
  pair->current = list->first;
  while (pair->current != NULL)
  {
    pair->prev = pair->current;
    pair->current = pair->current->next;
    free(pair->prev);
  }
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return Success;
}

List_ptr map(List_ptr list, Mapper mapper)
{
  List_ptr mapped_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    add_to_list(mapped_list, (*mapper)(p_walk->element));
    p_walk = p_walk->next;
  }
  return mapped_list;
}

List_ptr filter(List_ptr list, Predicate predicate)
{
  List_ptr filtered_list = create_list();
  Node_ptr p_walk = list->first;
  Element element;
  Status status;
  while (p_walk != NULL && status)
  {
    element = p_walk->element;
    if ((*predicate)(element))
    {
      status = add_to_list(filtered_list, element);
    }
    p_walk = p_walk->next;
  }
  return filtered_list;
}

Element reduce(List_ptr list, Element initial_value, Reducer reducer)
{
  List_ptr filtered_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    initial_value = (*reducer)(initial_value, p_walk->element);
    p_walk = p_walk->next;
  }
  return initial_value;
}

void forEach(List_ptr list, ElementProcessor processor)
{
  List_ptr filtered_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL)
  {
    (*processor)(p_walk->element);
    p_walk = p_walk->next;
  }
}