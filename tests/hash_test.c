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

#include "hash.h"
#include "munit.h"
#include <string.h>

static MunitResult
test_fnv_1a_hash()
{
  char* data_1 = "test";

  uint64_t res_1 = fnv_1a_hash(data_1, strlen(data_1));

  munit_assert_uint64(res_1, ==, 18007334074686647077u);

  // Random 16 bytes test
  char* data_2 = "\x26\x17\x2b\xbc\x97\xe7\x1f\x89\xcb\x79\x8a\xa4\xa5\xd8\xd7"
                 "\xae";

  uint64_t res_2 = fnv_1a_hash(data_2, 16);

  munit_assert_uint64(res_2, ==, 3851942014862232125u);

  char* data_3 = "my\nmulti\nline\nstring";

  uint64_t res_3 = fnv_1a_hash(data_3, strlen(data_3));

  munit_assert_uint64(res_3, ==, 7644173466961780319u);

  char* data_4 = "null\0terminated";

  uint64_t res_4 = fnv_1a_hash(data_4, 15);

  munit_assert_uint64(res_4, ==, 5570858491698162917u);

  // UTF-8 test
  char* data_5 = "你好";

  uint64_t res_5 = fnv_1a_hash(data_5, strlen(data_5));

  munit_assert_uint64(res_5, ==, 14847642749964321443u);

  return MUNIT_OK;
}

// clang-format off
static MunitTest test_suite_tests[] = {
  {"/fnv_1a", test_fnv_1a_hash, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
  {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
};

static const MunitSuite test_suite = {"/Hash", test_suite_tests,  NULL, 1, MUNIT_SUITE_OPTION_NONE};
// clang-format on

int
main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
  return munit_suite_main(&test_suite, NULL, argc, argv);
}