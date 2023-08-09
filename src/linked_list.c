/*
 * Copyright 2023 Adam Bishop Comer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "../include/linked_list.h"
#include <stdlib.h>

struct LinkedList*
LinkedList_new()
{
  struct LinkedList* ll = malloc(sizeof(struct LinkedList));
  ll->node = NULL;
  ll->length = 0;

  return ll;
}

void
LinkedList_free(struct LinkedList* ll)
{
  struct LinkedListNode* curr = ll->node;
  while (curr != NULL) {
    struct LinkedListNode* next = curr->next;
    LinkedListNode_free(curr);
    curr = next;
  }
  free(ll);
}

struct LinkedListNode*
LinkedListNode_new()
{
  struct LinkedListNode* node = malloc(sizeof(struct LinkedListNode));
  node->next = NULL;
  node->data = NULL;

  return node;
}

void
LinkedListNode_free(struct LinkedListNode* node)
{
  free(node);
}

struct LinkedListNode*
LinkedList_get(struct LinkedList* ll, unsigned int idx)
{
  if (ll->length <= idx) {
    return NULL;
  }

  struct LinkedListNode* curr = ll->node;
  while (curr != NULL) {
    if (idx == 0) {
      return curr;
    }
    idx -= 1;
    curr = curr->next;
  }

  return NULL;
}

struct LinkedListNode*
LinkedList_first(struct LinkedList* ll)
{
  return ll->node;
}

struct LinkedListNode*
LinkedList_last(struct LinkedList* ll)
{
  struct LinkedListNode* curr = ll->node;
  if (curr == NULL) {
    return NULL;
  }

  while (curr->next) {
    curr = curr->next;
  }

  return curr;
}

void
LinkedList_append(struct LinkedList* ll, struct LinkedListNode* node)
{
  if (ll->length == 0) {
    ll->node = node;
    ll->length = 1;
    return;
  }

  struct LinkedListNode* last = LinkedList_last(ll);
  last->next = node;
  ll->length += 1;
}

void
LinkedList_insert(struct LinkedList* ll,
                  struct LinkedListNode* node,
                  unsigned int idx)
{
  if (idx == 0) {
    node->next = ll->node;
    ll->node = node;
    ll->length += 1;
    return;
  }

  struct LinkedListNode* preceding_node = LinkedList_get(ll, idx - 1);
  if (preceding_node == NULL)
    return;

  node->next = preceding_node->next;
  preceding_node->next = node;
  ll->length += 1;
}

struct LinkedList*
LinkedList_concatenate(struct LinkedList* ll_a, struct LinkedList* ll_b)
{
  if (ll_a->length == 0) {
    ll_a->node = ll_b->node;
    ll_a->length = ll_b->length;
  } else {
    struct LinkedListNode* last = LinkedList_last(ll_a);
    last->next = ll_b->node;
    ll_a->length += ll_b->length;
  }

  ll_b->node =
    NULL; // Clear node pointer to prevent freeing all the nodes in ll_b
  free(ll_b);

  return ll_a;
}

struct LinkedListNode*
LinkedList_remove(struct LinkedList* ll, unsigned int idx)
{
  if (ll->length <= idx) {
    return NULL;
  }

  if (idx == 0) {
    struct LinkedListNode* node = ll->node;
    ll->node = node->next;
    ll->length -= 1;
    return node;
  }

  struct LinkedListNode* preceding_node = LinkedList_get(ll, idx - 1);
  struct LinkedListNode* node = preceding_node->next;

  preceding_node->next = node->next;
  node->next = NULL;
  ll->length -= 1;

  return node;
}

struct LinkedListNode*
LinkedList_pop(struct LinkedList* ll)
{
  if (ll->length == 0) {
    return NULL;
  } else if (ll->length == 1) {
    struct LinkedListNode* node = ll->node;
    ll->node = NULL;
    ll->length = 0;
    return node;
  }

  struct LinkedListNode* penultimate_node = LinkedList_get(ll, ll->length - 2);

  struct LinkedListNode* node = penultimate_node->next;
  penultimate_node->next = NULL;
  ll->length -= 1;

  return node;
}

struct LinkedListIterator*
LinkedListIterator_new(struct LinkedList* ll)
{
  struct LinkedListIterator* iterator =
    malloc(sizeof(struct LinkedListIterator));
  iterator->next = ll->node;

  return iterator;
}

void
LinkedListIterator_free(struct LinkedListIterator* iterator)
{
  free(iterator);
}

struct LinkedListNode*
LinkedListIterator_next(struct LinkedListIterator* iterator)
{
  if (iterator->next == NULL) {
    return NULL;
  }

  struct LinkedListNode* node = iterator->next;
  iterator->next = node->next;

  return node;
}
