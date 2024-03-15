
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
#include <stdlib.h>
#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit.h"
#include "sort.h"
#include "vector.h"

int
cmp(void* a, void* b)
{
  int a_i = *(int*)a;
  int b_i = *(int*)b;

  if (a_i == b_i) {
    return 0;
  } else if (a_i > b_i) {
    return 1;
  } else {
    return -1;
  }
}

MunitResult
test_Sort_bubblesort()
{
  // Setup
  struct Vector* v = Vector_new(8);

  int value_1 = 5;
  Vector_append(v, &value_1);

  int value_2 = 2;
  Vector_append(v, &value_2);

  int value_3 = 9;
  Vector_append(v, &value_3);

  int value_4 = 4;
  Vector_append(v, &value_4);

  int value_5 = 2;
  Vector_append(v, &value_5);

  munit_assert_size(v->length, ==, 5);

  // Test
  Sort_bubblesort(v->data, v->length, cmp);

  munit_assert_int(*(int*)v->data[0], ==, 2);
  munit_assert_int(*(int*)v->data[1], ==, 2);
  munit_assert_int(*(int*)v->data[2], ==, 4);
  munit_assert_int(*(int*)v->data[3], ==, 5);
  munit_assert_int(*(int*)v->data[4], ==, 9);

  // Teardown
  Vector_free(v);

  return MUNIT_OK;
}

MunitResult
test_Sort_mergesort()
{
  // Setup
  struct Vector* v = Vector_new(8);

  int value_1 = 5;
  Vector_append(v, &value_1);

  int value_2 = 2;
  Vector_append(v, &value_2);

  int value_3 = 9;
  Vector_append(v, &value_3);

  int value_4 = 4;
  Vector_append(v, &value_4);

  int value_5 = 2;
  Vector_append(v, &value_5);

  munit_assert_size(v->length, ==, 5);

  // Test
  Sort_mergesort(v->data, v->length, cmp);

  munit_assert_int(*(int*)v->data[0], ==, 2);
  munit_assert_int(*(int*)v->data[1], ==, 2);
  munit_assert_int(*(int*)v->data[2], ==, 4);
  munit_assert_int(*(int*)v->data[3], ==, 5);
  munit_assert_int(*(int*)v->data[4], ==, 9);

  // Teardown
  Vector_free(v);

  return MUNIT_OK;
}

MunitResult
test_Sort_heapsort()
{
  // Setup
  struct Vector* v = Vector_new(8);

  int value_1 = 5;
  Vector_append(v, &value_1);

  int value_2 = 2;
  Vector_append(v, &value_2);

  int value_3 = 9;
  Vector_append(v, &value_3);

  int value_4 = 4;
  Vector_append(v, &value_4);

  int value_5 = 2;
  Vector_append(v, &value_5);

  munit_assert_size(v->length, ==, 5);

  // Test
  Sort_heapsort(v->data, v->length, cmp);

  munit_assert_int(*(int*)v->data[0], ==, 2);
  munit_assert_int(*(int*)v->data[1], ==, 2);
  munit_assert_int(*(int*)v->data[2], ==, 4);
  munit_assert_int(*(int*)v->data[3], ==, 5);
  munit_assert_int(*(int*)v->data[4], ==, 9);

  // Teardown
  Vector_free(v);

  return MUNIT_OK;
}

// clang-format off
static MunitTest test_suite_tests[] = {
  {"/bubblesort", test_Sort_bubblesort, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/mergesort", test_Sort_mergesort, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/heapsort", test_Sort_heapsort, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite = {"/Sort", test_suite_tests,  NULL, 1, MUNIT_SUITE_OPTION_NONE};
// clang-format on

int
main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
