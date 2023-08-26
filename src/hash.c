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
#include <assert.h>

uint64_t
fnv_1a_hash(char* data, size_t data_len)
{
  assert(data_len > 0);

  uint64_t hash = FNV_OFFSET;
  for (size_t i = 0; i < data_len; i++) {
    hash ^= data[i];
    hash *= FNV_PRIME;
  }

  return hash;
}