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

#define MUNIT_ENABLE_ASSERT_ALIASES

#include "linked_list.h"
#include "munit.h"

static MunitResult
test_LinkedList_new()
{
  struct LinkedList* ll = LinkedList_new();

  munit_assert_uint(ll->length, ==, 0);
  munit_assert_ptr(ll->node, ==, NULL);

  LinkedList_free(ll);

  return MUNIT_OK;
}

static MunitResult
test_LinkedListNode_new()
{
  struct LinkedListNode* node = LinkedListNode_new();

  munit_assert_ptr(node->next, ==, NULL);
  munit_assert_ptr(node->data, ==, NULL);

  LinkedListNode_free(node);

  return MUNIT_OK;
}

static MunitResult
test_LinkedList_append()
{
  struct LinkedList* ll = LinkedList_new();

  munit_assert_uint(ll->length, ==, 0);
  munit_assert_ptr(ll->node, ==, NULL);

  struct LinkedListNode* new_node_1 = LinkedListNode_new();
  LinkedList_append(ll, new_node_1);

  munit_assert_uint(ll->length, ==, 1);
  munit_assert_ptr(ll->node, ==, new_node_1);

  munit_assert_ptr(new_node_1->next, ==, NULL);
  munit_assert_ptr(new_node_1->data, ==, NULL);

  struct LinkedListNode* new_node_2 = LinkedListNode_new();
  LinkedList_append(ll, new_node_2);

  munit_assert_uint(ll->length, ==, 2);
  munit_assert_ptr(ll->node, ==, new_node_1);

  munit_assert_ptr(new_node_1->next, ==, new_node_2);
  munit_assert_ptr(new_node_1->data, ==, NULL);

  munit_assert_ptr(new_node_2->next, ==, NULL);
  munit_assert_ptr(new_node_2->data, ==, NULL);

  struct LinkedListNode* new_node_3 = LinkedListNode_new();
  LinkedList_append(ll, new_node_3);

  munit_assert_uint(ll->length, ==, 3);
  munit_assert_ptr(ll->node, ==, new_node_1);

  munit_assert_ptr(new_node_1->next, ==, new_node_2);
  munit_assert_ptr(new_node_1->data, ==, NULL);

  munit_assert_ptr(new_node_2->next, ==, new_node_3);
  munit_assert_ptr(new_node_2->data, ==, NULL);

  munit_assert_ptr(new_node_3->next, ==, NULL);
  munit_assert_ptr(new_node_3->data, ==, NULL);

  LinkedList_free(ll);

  return MUNIT_OK;
}

static MunitResult
test_LinkedList_insert()
{
  struct LinkedList* ll = LinkedList_new();

  munit_assert_uint(ll->length, ==, 0);
  munit_assert_ptr(ll->node, ==, NULL);

  // Insert at start
  struct LinkedListNode* new_node_1 = LinkedListNode_new();
  LinkedList_insert(ll, new_node_1, 0);

  munit_assert_uint(ll->length, ==, 1);
  munit_assert_ptr(ll->node, ==, new_node_1);

  munit_assert_ptr(new_node_1->next, ==, NULL);
  munit_assert_ptr(new_node_1->data, ==, NULL);

  // Insert at start
  struct LinkedListNode* new_node_2 = LinkedListNode_new();
  LinkedList_insert(ll, new_node_2, 0);

  munit_assert_uint(ll->length, ==, 2);
  munit_assert_ptr(ll->node, ==, new_node_2);

  munit_assert_ptr(new_node_1->next, ==, NULL);
  munit_assert_ptr(new_node_1->data, ==, NULL);

  munit_assert_ptr(new_node_2->next, ==, new_node_1);
  munit_assert_ptr(new_node_2->data, ==, NULL);

  // Insert at middle
  struct LinkedListNode* new_node_3 = LinkedListNode_new();
  LinkedList_insert(ll, new_node_3, 1);

  munit_assert_uint(ll->length, ==, 3);
  munit_assert_ptr(ll->node, ==, new_node_2);

  munit_assert_ptr(new_node_1->next, ==, NULL);
  munit_assert_ptr(new_node_1->data, ==, NULL);

  munit_assert_ptr(new_node_2->next, ==, new_node_3);
  munit_assert_ptr(new_node_2->data, ==, NULL);

  munit_assert_ptr(new_node_3->next, ==, new_node_1);
  munit_assert_ptr(new_node_3->data, ==, NULL);

  // Insert at end
  struct LinkedListNode* new_node_4 = LinkedListNode_new();
  LinkedList_insert(ll, new_node_4, 3);

  munit_assert_uint(ll->length, ==, 4);
  munit_assert_ptr(ll->node, ==, new_node_2);

  munit_assert_ptr(new_node_1->next, ==, new_node_4);
  munit_assert_ptr(new_node_1->data, ==, NULL);

  munit_assert_ptr(new_node_2->next, ==, new_node_3);
  munit_assert_ptr(new_node_2->data, ==, NULL);

  munit_assert_ptr(new_node_3->next, ==, new_node_1);
  munit_assert_ptr(new_node_3->data, ==, NULL);

  munit_assert_ptr(new_node_4->next, ==, NULL);
  munit_assert_ptr(new_node_4->data, ==, NULL);

  LinkedList_free(ll);

  return MUNIT_OK;
}

static MunitResult
test_LinkedList_first()
{
  struct LinkedList* ll = LinkedList_new();

  munit_assert_uint(ll->length, ==, 0);
  munit_assert_ptr(ll->node, ==, NULL);

  struct LinkedListNode* first = LinkedList_first(ll);

  munit_assert_ptr(first, ==, NULL);

  struct LinkedListNode* new_node_1 = LinkedListNode_new();
  LinkedList_append(ll, new_node_1);

  first = LinkedList_first(ll);

  munit_assert_ptr(first, ==, new_node_1);

  struct LinkedListNode* new_node_2 = LinkedListNode_new();
  LinkedList_append(ll, new_node_2);

  first = LinkedList_first(ll);

  munit_assert_ptr(first, ==, new_node_1);

  LinkedList_free(ll);

  return MUNIT_OK;
}

static MunitResult
test_LinkedList_last()
{
  struct LinkedList* ll = LinkedList_new();

  munit_assert_uint(ll->length, ==, 0);
  munit_assert_ptr(ll->node, ==, NULL);

  struct LinkedListNode* last = LinkedList_last(ll);

  munit_assert_ptr(last, ==, NULL);

  struct LinkedListNode* new_node_1 = LinkedListNode_new();
  LinkedList_append(ll, new_node_1);

  last = LinkedList_last(ll);

  munit_assert_ptr(last, ==, new_node_1);

  struct LinkedListNode* new_node_2 = LinkedListNode_new();
  LinkedList_append(ll, new_node_2);

  last = LinkedList_last(ll);

  munit_assert_ptr(last, ==, new_node_2);

  LinkedList_free(ll);

  return MUNIT_OK;
}

static MunitResult
test_LinkedList_get()
{
  struct LinkedList* ll = LinkedList_new();

  struct LinkedListNode* new_node_1 = LinkedListNode_new();
  LinkedList_append(ll, new_node_1);

  struct LinkedListNode* new_node_2 = LinkedListNode_new();
  LinkedList_append(ll, new_node_2);

  struct LinkedListNode* new_node_3 = LinkedListNode_new();
  LinkedList_append(ll, new_node_3);

  munit_assert_uint(ll->length, ==, 3);
  munit_assert_ptr(ll->node, ==, new_node_1);

  struct LinkedListNode* get_node_1 = LinkedList_get(ll, 0);

  munit_assert_ptr(get_node_1, ==, new_node_1);

  struct LinkedListNode* get_node_2 = LinkedList_get(ll, 1);

  munit_assert_ptr(get_node_2, ==, new_node_2);

  struct LinkedListNode* get_node_3 = LinkedList_get(ll, 2);

  munit_assert_ptr(get_node_3, ==, new_node_3);

  LinkedList_free(ll);

  return MUNIT_OK;
}

static MunitResult
test_LinkedList_concatenate()
{
  struct LinkedList* ll_1 = LinkedList_new();

  struct LinkedListNode* new_node_1_1 = LinkedListNode_new();
  LinkedList_append(ll_1, new_node_1_1);

  struct LinkedListNode* new_node_1_2 = LinkedListNode_new();
  LinkedList_append(ll_1, new_node_1_2);

  struct LinkedListNode* new_node_1_3 = LinkedListNode_new();
  LinkedList_append(ll_1, new_node_1_3);

  munit_assert_uint(ll_1->length, ==, 3);
  munit_assert_ptr(ll_1->node, ==, new_node_1_1);

  struct LinkedList* ll_2 = LinkedList_new();

  struct LinkedListNode* new_node_2_1 = LinkedListNode_new();
  LinkedList_append(ll_2, new_node_2_1);

  struct LinkedListNode* new_node_2_2 = LinkedListNode_new();
  LinkedList_append(ll_2, new_node_2_2);

  struct LinkedListNode* new_node_2_3 = LinkedListNode_new();
  LinkedList_append(ll_2, new_node_2_3);

  munit_assert_uint(ll_2->length, ==, 3);
  munit_assert_ptr(ll_2->node, ==, new_node_2_1);

  LinkedList_concatenate(ll_1, ll_2);

  munit_assert_uint(ll_1->length, ==, 6);
  munit_assert_ptr(ll_1->node, ==, new_node_1_1);

  munit_assert_ptr(new_node_1_1->next, ==, new_node_1_2);

  munit_assert_ptr(new_node_1_2->next, ==, new_node_1_3);

  munit_assert_ptr(new_node_1_3->next, ==, new_node_2_1);

  munit_assert_ptr(new_node_2_1->next, ==, new_node_2_2);

  munit_assert_ptr(new_node_2_2->next, ==, new_node_2_3);

  munit_assert_ptr(new_node_2_3->next, ==, NULL);

  LinkedList_free(ll_1);

  return MUNIT_OK;
}

static MunitResult
test_LinkedList_remove()
{
  struct LinkedList* ll = LinkedList_new();

  struct LinkedListNode* new_node_1 = LinkedListNode_new();
  LinkedList_append(ll, new_node_1);

  struct LinkedListNode* new_node_2 = LinkedListNode_new();
  LinkedList_append(ll, new_node_2);

  struct LinkedListNode* new_node_3 = LinkedListNode_new();
  LinkedList_append(ll, new_node_3);

  munit_assert_uint(ll->length, ==, 3);
  munit_assert_ptr(ll->node, ==, new_node_1);

  // Remove from middle
  struct LinkedListNode* removed = LinkedList_remove(ll, 1);

  munit_assert_ptr(removed, ==, new_node_2);
  munit_assert_ptr(removed->next, ==, NULL);

  munit_assert_ptr(new_node_1->next, ==, new_node_3);

  munit_assert_uint(ll->length, ==, 2);

  LinkedListNode_free(removed);

  // Remove from last
  removed = LinkedList_remove(ll, 1);

  munit_assert_ptr(removed, ==, new_node_3);
  munit_assert_ptr(removed->next, ==, NULL);

  munit_assert_ptr(new_node_1->next, ==, NULL);

  munit_assert_uint(ll->length, ==, 1);

  LinkedListNode_free(removed);

  // Removed from start
  removed = LinkedList_remove(ll, 0);

  munit_assert_ptr(removed, ==, new_node_1);
  munit_assert_ptr(removed->next, ==, NULL);

  munit_assert_ptr(ll->node, ==, NULL);
  munit_assert_uint(ll->length, ==, 0);

  LinkedListNode_free(removed);

  LinkedList_free(ll);

  return MUNIT_OK;
}

static MunitResult
test_LinkedList_pop()
{
  struct LinkedList* ll = LinkedList_new();

  struct LinkedListNode* new_node_1 = LinkedListNode_new();
  LinkedList_append(ll, new_node_1);

  struct LinkedListNode* new_node_2 = LinkedListNode_new();
  LinkedList_append(ll, new_node_2);

  struct LinkedListNode* new_node_3 = LinkedListNode_new();
  LinkedList_append(ll, new_node_3);

  munit_assert_uint(ll->length, ==, 3);
  munit_assert_ptr(ll->node, ==, new_node_1);

  struct LinkedListNode* popped = LinkedList_pop(ll);

  munit_assert_ptr(popped, ==, new_node_3);
  munit_assert_ptr(popped->next, ==, NULL);

  munit_assert_ptr(new_node_2->next, ==, NULL);

  munit_assert_uint(ll->length, ==, 2);

  LinkedListNode_free(popped);

  popped = LinkedList_pop(ll);

  munit_assert_ptr(popped, ==, new_node_2);
  munit_assert_ptr(popped->next, ==, NULL);

  munit_assert_ptr(new_node_1->next, ==, NULL);

  munit_assert_uint(ll->length, ==, 1);

  LinkedListNode_free(popped);

  popped = LinkedList_pop(ll);

  munit_assert_ptr(popped, ==, new_node_1);
  munit_assert_ptr(popped->next, ==, NULL);

  munit_assert_ptr(ll->node, ==, NULL);
  munit_assert_uint(ll->length, ==, 0);

  LinkedListNode_free(popped);

  LinkedList_free(ll);

  return MUNIT_OK;
}

static MunitResult
test_LinkedList_iterator()
{
  struct LinkedList* ll = LinkedList_new();

  struct LinkedListNode* new_node_1 = LinkedListNode_new();
  LinkedList_append(ll, new_node_1);

  struct LinkedListNode* new_node_2 = LinkedListNode_new();
  LinkedList_append(ll, new_node_2);

  struct LinkedListNode* new_node_3 = LinkedListNode_new();
  LinkedList_append(ll, new_node_3);

  munit_assert_uint(ll->length, ==, 3);
  munit_assert_ptr(ll->node, ==, new_node_1);

  struct LinkedListIterator* iterator = LinkedListIterator_new(ll);

  struct LinkedListNode* next = LinkedListIterator_next(iterator);

  munit_assert_ptr(next, ==, new_node_1);

  next = LinkedListIterator_next(iterator);

  munit_assert_ptr(next, ==, new_node_2);

  next = LinkedListIterator_next(iterator);

  munit_assert_ptr(next, ==, new_node_3);

  next = LinkedListIterator_next(iterator);

  munit_assert_ptr(next, ==, NULL);

  LinkedList_free(ll);

  return MUNIT_OK;
}

// clang-format off
static MunitTest test_suite_tests[] = {
  {"/new", test_LinkedList_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/node_new", test_LinkedListNode_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/append", test_LinkedList_append, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/insert", test_LinkedList_insert, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/first", test_LinkedList_first, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/last", test_LinkedList_last, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/get", test_LinkedList_get, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/concatenate", test_LinkedList_concatenate, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/remove", test_LinkedList_remove, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/pop", test_LinkedList_pop, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/iterator", test_LinkedList_iterator, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite = {"/LinkedList", test_suite_tests,  NULL, 1, MUNIT_SUITE_OPTION_NONE};
// clang-format on

int
main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
