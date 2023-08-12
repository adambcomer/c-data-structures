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

#include <stdio.h>
#define MUNIT_ENABLE_ASSERT_ALIASES

#include "include/vector.h"
#include "subprojects/munit/munit.h"

static MunitResult
test_Vector_new()
{
  struct Vector* v = Vector_new(128);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 0);

  Vector_free(v);

  return MUNIT_OK;
}

static MunitResult
test_Vector_append()
{
  struct Vector* v = Vector_new(2);

  munit_assert_size(v->capacity, ==, 2);
  munit_assert_size(v->length, ==, 0);

  int value_1 = 1;
  Vector_append(v, &value_1);

  munit_assert_size(v->capacity, ==, 2);
  munit_assert_size(v->length, ==, 1);

  munit_assert_ptr(v->data[0], ==, &value_1);

  int value_2 = 2;
  Vector_append(v, &value_2);

  munit_assert_size(v->capacity, ==, 2);
  munit_assert_size(v->length, ==, 2);

  munit_assert_ptr(v->data[0], ==, &value_1);
  munit_assert_ptr(v->data[1], ==, &value_2);

  int value_3 = 3;
  Vector_append(v, &value_3);

  munit_assert_size(v->capacity, ==, 4);
  munit_assert_size(v->length, ==, 3);

  munit_assert_ptr(v->data[0], ==, &value_1);
  munit_assert_ptr(v->data[1], ==, &value_2);
  munit_assert_ptr(v->data[2], ==, &value_3);

  Vector_free(v);

  return MUNIT_OK;
}

static MunitResult
test_Vector_insert()
{
  struct Vector* v = Vector_new(2);

  munit_assert_size(v->capacity, ==, 2);
  munit_assert_size(v->length, ==, 0);

  // Insert at start
  int value_1 = 1;
  Vector_insert(v, &value_1, 0);

  munit_assert_size(v->capacity, ==, 2);
  munit_assert_size(v->length, ==, 1);

  munit_assert_ptr(v->data[0], ==, &value_1);

  // Insert at start
  int value_2 = 2;
  Vector_insert(v, &value_2, 0);

  munit_assert_size(v->capacity, ==, 2);
  munit_assert_size(v->length, ==, 2);

  munit_assert_ptr(v->data[0], ==, &value_2);
  munit_assert_ptr(v->data[1], ==, &value_1);

  // Insert at middle
  int value_3 = 3;
  Vector_insert(v, &value_3, 1);

  munit_assert_size(v->capacity, ==, 4);
  munit_assert_size(v->length, ==, 3);

  munit_assert_ptr(v->data[0], ==, &value_2);
  munit_assert_ptr(v->data[1], ==, &value_3);
  munit_assert_ptr(v->data[2], ==, &value_1);

  // Insert at middle
  int value_4 = 4;
  Vector_insert(v, &value_4, 2);

  munit_assert_size(v->capacity, ==, 4);
  munit_assert_size(v->length, ==, 4);

  munit_assert_ptr(v->data[0], ==, &value_2);
  munit_assert_ptr(v->data[1], ==, &value_3);
  munit_assert_ptr(v->data[2], ==, &value_4);
  munit_assert_ptr(v->data[3], ==, &value_1);

  // Insert at end
  int value_5 = 5;
  Vector_insert(v, &value_5, 4);

  munit_assert_size(v->capacity, ==, 8);
  munit_assert_size(v->length, ==, 5);

  munit_assert_ptr(v->data[0], ==, &value_2);
  munit_assert_ptr(v->data[1], ==, &value_3);
  munit_assert_ptr(v->data[2], ==, &value_4);
  munit_assert_ptr(v->data[3], ==, &value_1);
  munit_assert_ptr(v->data[4], ==, &value_5);

  Vector_free(v);

  return MUNIT_OK;
}

static MunitResult
test_Vector_first()
{
  struct Vector* v = Vector_new(128);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 0);

  void* first_0 = Vector_first(v);

  munit_assert_ptr(first_0, ==, NULL);

  int value_1 = 1;
  Vector_append(v, &value_1);

  void* first_1 = Vector_first(v);

  munit_assert_ptr(first_1, ==, &value_1);

  int value_2 = 2;
  Vector_append(v, &value_2);

  void* first_2 = Vector_first(v);

  munit_assert_ptr(first_2, ==, &value_1);

  Vector_free(v);

  return MUNIT_OK;
}

static MunitResult
test_Vector_last()
{
  struct Vector* v = Vector_new(128);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 0);

  void* last_0 = Vector_last(v);

  munit_assert_ptr(last_0, ==, NULL);

  int value_1 = 1;
  Vector_append(v, &value_1);

  void* last_1 = Vector_last(v);

  munit_assert_ptr(last_1, ==, &value_1);

  int value_2 = 2;
  Vector_append(v, &value_2);

  void* last_2 = Vector_last(v);

  munit_assert_ptr(last_2, ==, &value_2);

  int value_3 = 3;
  Vector_append(v, &value_3);

  void* last_3 = Vector_last(v);

  munit_assert_ptr(last_3, ==, &value_3);

  Vector_free(v);

  return MUNIT_OK;
}

static MunitResult
test_Vector_get()
{
  struct Vector* v = Vector_new(128);

  int value_1 = 1;
  Vector_append(v, &value_1);

  int value_2 = 2;
  Vector_append(v, &value_2);

  int value_3 = 3;
  Vector_append(v, &value_3);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 3);

  void* get_value_1 = Vector_get(v, 0);

  munit_assert_ptr(get_value_1, ==, &value_1);

  void* get_value_2 = Vector_get(v, 1);

  munit_assert_ptr(get_value_2, ==, &value_2);

  void* get_value_3 = Vector_get(v, 2);

  munit_assert_ptr(get_value_3, ==, &value_3);

  Vector_free(v);

  return MUNIT_OK;
}

static MunitResult
test_Vector_concatenate()
{
  struct Vector* v_1 = Vector_new(128);

  int value_1 = 1;
  Vector_append(v_1, &value_1);

  int value_2 = 2;
  Vector_append(v_1, &value_2);

  int value_3 = 3;
  Vector_append(v_1, &value_3);

  munit_assert_size(v_1->capacity, ==, 128);
  munit_assert_size(v_1->length, ==, 3);

  struct Vector* v_2 = Vector_new(128);

  int value_4 = 4;
  Vector_append(v_2, &value_4);

  int value_5 = 5;
  Vector_append(v_2, &value_5);

  int value_6 = 6;
  Vector_append(v_2, &value_6);

  munit_assert_size(v_2->capacity, ==, 128);
  munit_assert_size(v_2->length, ==, 3);

  Vector_concatenate(v_1, v_2);

  munit_assert_size(v_1->capacity, ==, 12);
  munit_assert_size(v_1->length, ==, 6);

  munit_assert_ptr(v_1->data[0], ==, &value_1);
  munit_assert_ptr(v_1->data[1], ==, &value_2);
  munit_assert_ptr(v_1->data[2], ==, &value_3);
  munit_assert_ptr(v_1->data[3], ==, &value_4);
  munit_assert_ptr(v_1->data[4], ==, &value_5);
  munit_assert_ptr(v_1->data[5], ==, &value_6);

  Vector_free(v_1);

  return MUNIT_OK;
}

static MunitResult
test_Vector_remove()
{
  struct Vector* v = Vector_new(128);

  int value_1 = 1;
  Vector_append(v, &value_1);

  int value_2 = 2;
  Vector_append(v, &value_2);

  int value_3 = 3;
  Vector_append(v, &value_3);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 3);

  // Remove from middle
  void* removed_1 = Vector_remove(v, 1);

  munit_assert_ptr(removed_1, ==, &value_2);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 2);

  munit_assert_ptr(v->data[0], ==, &value_1);
  munit_assert_ptr(v->data[1], ==, &value_3);

  // Remove from end
  void* removed_2 = Vector_remove(v, 1);

  munit_assert_ptr(removed_2, ==, &value_3);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 1);

  munit_assert_ptr(v->data[0], ==, &value_1);

  // Remove from start
  void* removed_3 = Vector_remove(v, 0);

  munit_assert_ptr(removed_3, ==, &value_1);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 0);

  Vector_free(v);

  return MUNIT_OK;
}

static MunitResult
test_Vector_pop()
{
  struct Vector* v = Vector_new(128);

  int value_1 = 1;
  Vector_append(v, &value_1);

  int value_2 = 2;
  Vector_append(v, &value_2);

  int value_3 = 3;
  Vector_append(v, &value_3);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 3);

  void* pop_1 = Vector_pop(v);

  munit_assert_ptr(pop_1, ==, &value_3);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 2);

  munit_assert_ptr(v->data[0], ==, &value_1);
  munit_assert_ptr(v->data[1], ==, &value_2);

  void* pop_2 = Vector_pop(v);

  munit_assert_ptr(pop_2, ==, &value_2);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 1);

  munit_assert_ptr(v->data[0], ==, &value_1);

  void* pop_3 = Vector_pop(v);

  munit_assert_ptr(pop_3, ==, &value_1);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 0);

  Vector_free(v);

  return MUNIT_OK;
}

static MunitResult
test_Vector_iterator()
{
  struct Vector* v = Vector_new(128);

  int value_1 = 1;
  Vector_append(v, &value_1);

  int value_2 = 2;
  Vector_append(v, &value_2);

  int value_3 = 3;
  Vector_append(v, &value_3);

  munit_assert_size(v->capacity, ==, 128);
  munit_assert_size(v->length, ==, 3);

  struct VectorIterator* iterator = VectorIterator_new(v);

  void* next_1 = VectorIterator_next(iterator);

  munit_assert_ptr(next_1, ==, &value_1);

  void* next_2 = VectorIterator_next(iterator);

  munit_assert_ptr(next_2, ==, &value_2);

  void* next_3 = VectorIterator_next(iterator);

  munit_assert_ptr(next_3, ==, &value_3);

  void* next_4 = VectorIterator_next(iterator);

  munit_assert_ptr(next_4, ==, NULL);

  VectorIterator_free(iterator);
  Vector_free(v);

  return MUNIT_OK;
}

// clang-format off
static MunitTest test_suite_tests[] = {
  {"/new", test_Vector_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/append", test_Vector_append, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/insert", test_Vector_insert, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/first", test_Vector_first, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/last", test_Vector_last, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/get", test_Vector_get, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/concatenate", test_Vector_concatenate, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/remove", test_Vector_remove, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/pop", test_Vector_pop, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/iterator", test_Vector_iterator, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite = {"/Vector", test_suite_tests,  NULL, 1, MUNIT_SUITE_OPTION_NONE};
// clang-format on

int
main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  return munit_suite_main(&test_suite, NULL, argc, argv);
}