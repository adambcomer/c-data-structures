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

#include "set.h"
#include "hash.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct Set*
Set_new(size_t inital_capacity)
{
  struct Set* s = malloc(sizeof(struct Set));

  s->table = calloc(inital_capacity, sizeof(struct SetItem));

  s->capacity = inital_capacity;
  s->load = 0;

  return s;
}

void
Set_free(struct Set* s)
{
  for (size_t i = 0; i < s->capacity; i++) {
    if (s->table[i].key != NULL) {
      free(s->table[i].key);
    }
  }

  free(s);
}

static int
_key_cmp(const char* key_a,
         size_t key_a_len,
         const char* key_b,
         size_t key_b_len)
{
  size_t min_len = key_a_len < key_b_len ? key_a_len : key_b_len;

  int cmp = memcmp(key_a, key_b, min_len);
  if (cmp != 0 || key_a_len == key_b_len) {
    return cmp;
  }

  return key_a_len < key_b_len ? -1 : 1;
}

int
Set_has(struct Set* s, char* key, size_t key_len)
{
  assert(key_len > 0);

  size_t idx = fnv_1a_hash(key, key_len) % s->capacity;

  for (size_t i = 0; i < s->capacity; i++) {
    struct SetItem* item = &s->table[(idx + i) % s->capacity];
    if (item->key == NULL) {
      return 0;
    } else if (_key_cmp(item->key, item->key_len, key, key_len) == 0) {
      return 1;
    }
  }

  return 0;
}

static void
_Set_expand(struct Set* s)
{
  struct SetItem* old_table = s->table;
  size_t old_capacity = s->capacity;
  s->table = calloc(s->capacity * 2, sizeof(struct SetItem));
  s->capacity *= 2;
  s->load = 0;

  for (size_t i = 0; i < old_capacity; i++) {
    struct SetItem* old_item = &old_table[i];
    if (old_table[i].key != NULL) {
      size_t idx = fnv_1a_hash(old_item->key, old_item->key_len) % s->capacity;

      for (size_t j = 0; j < s->capacity; j++) {
        struct SetItem* item = &s->table[(idx + j) % s->capacity];
        if (item->key == NULL) {
          item->key = old_item->key;
          item->key_len = old_item->key_len;
          s->load += 1;
          break;
        }
      }
    }
  }
}

void
Set_put(struct Set* s, char* key, size_t key_len)
{
  assert(key_len != 0);

  if ((float)s->load / s->capacity > 0.75) {
    _Set_expand(s);
  }

  size_t idx = fnv_1a_hash(key, key_len) % s->capacity;

  for (size_t i = 0; i < s->capacity; i++) {
    struct SetItem* item = &s->table[(idx + i) % s->capacity];
    if (item->key == NULL) {
      char* key_copy = malloc(key_len);
      memcpy(key_copy, key, key_len);

      item->key = key_copy;
      item->key_len = key_len;

      s->load += 1;
      return;
    } else if (_key_cmp(item->key, item->key_len, key, key_len) == 0) {
      return;
    }
  }
}

void
Set_delete(struct Set* s, char* key, size_t key_len)
{
  assert(key_len != 0);

  size_t hash_idx = fnv_1a_hash(key, key_len) % s->capacity;

  int has_item = 0;
  size_t delete_idx;
  for (size_t i = 0; i < s->capacity; i++) {
    struct SetItem* item = &s->table[(hash_idx + i) % s->capacity];
    if (item->key == NULL) {
      return;
    } else if (_key_cmp(item->key, item->key_len, key, key_len) == 0) {
      free(item->key);
      item->key = NULL;

      s->load -= 1;

      delete_idx = (hash_idx + i) % s->capacity;
      has_item = 0;
      break;
    }
  }
  if (!has_item)
    return;

  size_t replace_idx = delete_idx;
  for (size_t i = 0; i < s->capacity - (replace_idx - hash_idx); i++) {
    struct SetItem* item = &s->table[(delete_idx + i) % s->capacity];
    if (item->key == NULL) {
      return;
    } else if (fnv_1a_hash(item->key, item->key_len) % s->capacity <=
               hash_idx) {
      s->table[replace_idx].key = item->key;
      s->table[replace_idx].key_len = item->key_len;

      item->key = NULL;

      replace_idx = (delete_idx + i) % s->capacity;
    }
  }
}

struct Set*
Set_union(struct Set* s_a, struct Set* s_b)
{
  struct Set* union_s = Set_new(s_a->capacity + s_b->capacity);

  for (size_t i = 0; i < s_a->capacity; i++) {
    if (s_a->table[i].key != NULL) {
      Set_put(union_s, s_a->table[i].key, s_a->table[i].key_len);
    }
  }
  for (size_t i = 0; i < s_b->capacity; i++) {
    if (s_b->table[i].key != NULL) {
      Set_put(union_s, s_b->table[i].key, s_b->table[i].key_len);
    }
  }

  return union_s;
}

struct Set*
Set_intersection(struct Set* s_a, struct Set* s_b)
{
  struct Set* intersection_s = Set_new(s_a->capacity + s_b->capacity);

  for (size_t i = 0; i < s_a->capacity; i++) {
    if (s_a->table[i].key != NULL &&
        Set_has(s_b, s_a->table[i].key, s_a->table[i].key_len)) {
      Set_put(intersection_s, s_a->table[i].key, s_a->table[i].key_len);
    }
  }

  return intersection_s;
}

struct SetIterator*
SetIterator_new(struct Set* s)
{
  struct SetIterator* iterator = malloc(sizeof(struct SetIterator));

  iterator->set = s;
  iterator->idx = 0;

  return iterator;
}

void
SetIterator_free(struct SetIterator* iterator)
{
  free(iterator);
}

struct SetItem*
SetIterator_next(struct SetIterator* iterator)
{

  for (size_t i = iterator->idx; i < iterator->set->capacity; i++) {
    iterator->idx += 1;
    if (iterator->set->table[i].key != NULL) {
      return &iterator->set->table[i];
    }
  }

  return NULL;
}
