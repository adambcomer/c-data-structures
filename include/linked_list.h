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

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

struct LinkedListNode
{
  struct LinkedListNode* next;
  void* data;
};

struct LinkedListNode*
LinkedListNode_new();

void
LinkedListNode_free(struct LinkedListNode* node);

struct LinkedList
{
  struct LinkedListNode* node;
  size_t length;
};

struct LinkedList*
LinkedList_new();

void
LinkedList_free(struct LinkedList* ll);

struct LinkedListNode*
LinkedList_get(struct LinkedList* ll, size_t idx);

struct LinkedListNode*
LinkedList_first(struct LinkedList* ll);

struct LinkedListNode*
LinkedList_last(struct LinkedList* ll);

void
LinkedList_append(struct LinkedList* ll, struct LinkedListNode* node);

void
LinkedList_insert(struct LinkedList* ll,
                  struct LinkedListNode* node,
                  size_t idx);

struct LinkedList*
LinkedList_concatenate(struct LinkedList* ll_a, struct LinkedList* ll_b);

struct LinkedListNode*
LinkedList_remove(struct LinkedList* ll, size_t idx);

struct LinkedListNode*
LinkedList_pop(struct LinkedList* ll);

struct LinkedListIterator
{
  struct LinkedListNode* next;
};

struct LinkedListIterator*
LinkedListIterator_new(struct LinkedList* ll);

void
LinkedListIterator_free(struct LinkedListIterator* node);

struct LinkedListNode*
LinkedListIterator_next(struct LinkedListIterator* iterator);

#endif /* LINKED_LIST_H */