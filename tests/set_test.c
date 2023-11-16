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

#include "hash.h"
#include <stddef.h>
#include <string.h>
#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit.h"
#include "set.h"

static MunitResult
test_Set_new()
{
  // Test new
  struct Set* s = Set_new(128);

  munit_assert_size(s->capacity, ==, 128);
  munit_assert_size(s->load, ==, 0);

  for (size_t i = 0; i < s->capacity; i++) {
    munit_assert_ptr(s->table[i].key, ==, NULL);
  }

  // Teardown
  Set_free(s);

  return MUNIT_OK;
}

static MunitResult
test_Set_put()
{
  // Setup
  struct Set* s = Set_new(3);

  munit_assert_size(s->capacity, ==, 3);
  munit_assert_size(s->load, ==, 0);

  // Test put
  Set_put(s, "a", 1);

  munit_assert_size(s->capacity, ==, 3);
  munit_assert_size(s->load, ==, 1);

  munit_assert_ptr_null(s->table[0].key);

  munit_assert_ptr_not_null(s->table[1].key);
  munit_assert_memory_equal(1, s->table[1].key, "a");
  munit_assert_size(s->table[1].key_len, ==, 1);

  munit_assert_ptr_null(s->table[2].key);

  Set_put(s, "b", 1);

  munit_assert_size(s->capacity, ==, 3);
  munit_assert_size(s->load, ==, 2);

  munit_assert_ptr_null(s->table[0].key);

  munit_assert_ptr_not_null(s->table[1].key);
  munit_assert_memory_equal(1, s->table[1].key, "a");
  munit_assert_size(s->table[1].key_len, ==, 1);

  munit_assert_ptr_not_null(s->table[2].key);
  munit_assert_memory_equal(1, s->table[2].key, "b");
  munit_assert_size(s->table[2].key_len, ==, 1);

  Set_put(s, "c", 1);

  munit_assert_size(s->capacity, ==, 3);
  munit_assert_size(s->load, ==, 3);

  munit_assert_ptr_not_null(s->table[0].key);
  munit_assert_memory_equal(1, s->table[0].key, "c");
  munit_assert_size(s->table[0].key_len, ==, 1);

  munit_assert_ptr_not_null(s->table[1].key);
  munit_assert_memory_equal(1, s->table[1].key, "a");
  munit_assert_size(s->table[1].key_len, ==, 1);

  munit_assert_ptr_not_null(s->table[2].key);
  munit_assert_memory_equal(1, s->table[2].key, "b");
  munit_assert_size(s->table[2].key_len, ==, 1);

  Set_put(s, "d", 1);

  munit_assert_size(s->capacity, ==, 6);
  munit_assert_size(s->load, ==, 4);

  munit_assert_ptr_not_null(s->table[0].key);
  munit_assert_memory_equal(1, s->table[0].key, "c");
  munit_assert_size(s->table[0].key_len, ==, 1);

  munit_assert_ptr_not_null(s->table[1].key);
  munit_assert_memory_equal(1, s->table[1].key, "b");
  munit_assert_size(s->table[1].key_len, ==, 1);

  munit_assert_ptr_not_null(s->table[2].key);
  munit_assert_memory_equal(1, s->table[2].key, "d");
  munit_assert_size(s->table[2].key_len, ==, 1);

  munit_assert_ptr_null(s->table[3].key);

  munit_assert_ptr_not_null(s->table[4].key);
  munit_assert_memory_equal(1, s->table[4].key, "a");
  munit_assert_size(s->table[4].key_len, ==, 1);

  munit_assert_ptr_null(s->table[3].key);

  // Teardown
  Set_free(s);

  return MUNIT_OK;
}

static MunitResult
test_Set_has()
{
  // Setup
  struct Set* s = Set_new(8);

  Set_put(s, "a", 1);
  Set_put(s, "b", 1);
  Set_put(s, "c", 1);

  munit_assert_size(s->load, ==, 3);

  // Test has
  int res_1 = Set_has(s, "a", 1);
  munit_assert_int(res_1, ==, 1);

  int res_2 = Set_has(s, "b", 1);
  munit_assert_int(res_2, ==, 1);

  int res_3 = Set_has(s, "c", 1);
  munit_assert_int(res_3, ==, 1);

  int res_4 = Set_has(s, "d", 1);
  munit_assert_int(res_4, ==, 0);

  // Teardown
  Set_free(s);

  return MUNIT_OK;
}

static MunitResult
test_Set_delete()
{
  // Setup
  struct Set* s = Set_new(4);

  Set_put(s, "a", 1);
  Set_put(s, "b", 1);
  Set_put(s, "c", 1);

  munit_assert_size(s->load, ==, 3);

  // Test delete
  Set_delete(s, "c", 1);

  munit_assert_size(s->load, ==, 2);

  munit_assert_ptr(s->table[0].key, !=, NULL);
  munit_assert_memory_equal(1, s->table[0].key, "a");
  munit_assert_size(s->table[0].key_len, ==, 1);

  munit_assert_ptr(s->table[1].key, !=, NULL);
  munit_assert_memory_equal(1, s->table[1].key, "b");
  munit_assert_size(s->table[1].key_len, ==, 1);

  munit_assert_ptr(s->table[2].key, ==, NULL);

  munit_assert_ptr(s->table[3].key, ==, NULL);

  Set_delete(s, "b", 1);

  munit_assert_size(s->load, ==, 1);

  munit_assert_ptr(s->table[0].key, !=, NULL);
  munit_assert_memory_equal(1, s->table[0].key, "a");
  munit_assert_size(s->table[0].key_len, ==, 1);

  munit_assert_ptr(s->table[1].key, ==, NULL);

  munit_assert_ptr(s->table[2].key, ==, NULL);

  munit_assert_ptr(s->table[3].key, ==, NULL);

  Set_delete(s, "a", 1);

  munit_assert_size(s->load, ==, 0);

  munit_assert_ptr(s->table[0].key, ==, NULL);

  munit_assert_ptr(s->table[1].key, ==, NULL);

  munit_assert_ptr(s->table[2].key, ==, NULL);

  munit_assert_ptr(s->table[3].key, ==, NULL);

  // Teardown
  Set_free(s);

  return MUNIT_OK;
}

MunitResult
test_Set_union()
{
  // Setup
  struct Set* s1 = Set_new(8);

  Set_put(s1, "a", 1);
  Set_put(s1, "b", 1);
  Set_put(s1, "c", 1);

  munit_assert_size(s1->load, ==, 3);

  struct Set* s2 = Set_new(8);

  Set_put(s2, "c", 1);
  Set_put(s2, "d", 1);
  Set_put(s2, "e", 1);

  munit_assert_size(s2->load, ==, 3);

  // Test union
  struct Set* res_set = Set_union(s1, s2);

  munit_assert_size(res_set->load, ==, 5);

  int has_1 = Set_has(res_set, "a", 1);
  munit_assert_int(has_1, ==, 1);

  int has_2 = Set_has(res_set, "b", 1);
  munit_assert_int(has_2, ==, 1);

  int has_3 = Set_has(res_set, "c", 1);
  munit_assert_int(has_3, ==, 1);

  int has_4 = Set_has(res_set, "d", 1);
  munit_assert_int(has_4, ==, 1);

  int has_5 = Set_has(res_set, "e", 1);
  munit_assert_int(has_5, ==, 1);

  // Teardown
  Set_free(s1);

  Set_free(s2);

  Set_free(res_set);

  return MUNIT_OK;
}

MunitResult
test_Set_intersection()
{
  // Setup
  struct Set* s1 = Set_new(8);

  Set_put(s1, "a", 1);
  Set_put(s1, "b", 1);
  Set_put(s1, "c", 1);

  munit_assert_size(s1->load, ==, 3);

  struct Set* s2 = Set_new(8);

  Set_put(s2, "c", 1);
  Set_put(s2, "d", 1);
  Set_put(s2, "e", 1);

  munit_assert_size(s2->load, ==, 3);

  // Test intersection
  struct Set* res_set = Set_intersection(s1, s2);

  munit_assert_size(res_set->load, ==, 1);

  int has_1 = Set_has(res_set, "c", 1);
  munit_assert_int(has_1, ==, 1);

  // Teardown
  Set_free(s1);

  Set_free(s2);

  Set_free(res_set);

  return MUNIT_OK;
}

MunitResult
test_Set_iterator()
{
  // Setup
  struct Set* s = Set_new(8);

  Set_put(s, "a", 1);
  Set_put(s, "b", 1);
  Set_put(s, "c", 1);

  munit_assert_size(s->load, ==, 3);

  // Test iterator
  struct SetIterator* iterator = SetIterator_new(s);

  struct SetItem* next = SetIterator_next(iterator);

  munit_assert_not_null(next);
  munit_assert_size(next->key_len, ==, 1);
  munit_assert_memory_equal(1, next->key, "c");

  next = SetIterator_next(iterator);

  munit_assert_not_null(next);
  munit_assert_size(next->key_len, ==, 1);
  munit_assert_memory_equal(1, next->key, "a");

  next = SetIterator_next(iterator);

  munit_assert_not_null(next);
  munit_assert_size(next->key_len, ==, 1);
  munit_assert_memory_equal(1, next->key, "b");

  next = SetIterator_next(iterator);

  munit_assert_null(next);

  // Teardown
  SetIterator_free(iterator);

  Set_free(s);

  return MUNIT_OK;
}

// clang-format off
static MunitTest test_suite_tests[] = {
  {"/new", test_Set_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/put", test_Set_put, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/has", test_Set_has, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/delete", test_Set_delete, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/union", test_Set_union, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/intersection", test_Set_intersection, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {"/iterator", test_Set_iterator, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite = {"/Set", test_suite_tests,  NULL, 1, MUNIT_SUITE_OPTION_NONE};
// clang-format on

int
main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  return munit_suite_main(&test_suite, NULL, argc, argv);
}
