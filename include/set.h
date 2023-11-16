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

#ifndef SET_H
#define SET_H

#include <stddef.h>

struct SetItem
{
  char* key;
  size_t key_len;
};

struct Set
{
  size_t capacity;
  size_t load;
  struct SetItem* table;
};

struct Set*
Set_new(size_t inital_capacity);

void
Set_free(struct Set* s);

int
Set_has(struct Set* s, char* key, size_t key_len);

void
Set_put(struct Set* s, char* key, size_t key_len);

void
Set_delete(struct Set* s, char* key, size_t key_len);

struct Set*
Set_union(struct Set* s_a, struct Set* s_b);

struct Set*
Set_intersection(struct Set* s_a, struct Set* s_b);

struct SetIterator
{
  struct Set* set;
  size_t idx;
};

struct SetIterator*
SetIterator_new(struct Set* s);

void
SetIterator_free(struct SetIterator* iterator);

struct SetItem*
SetIterator_next(struct SetIterator* s);

#endif /* SET_H */
