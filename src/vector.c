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

#include "include/vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Vector*
Vector_new(size_t inital_capacity)
{
  assert(inital_capacity > 0);

  struct Vector* v = malloc(sizeof(struct Vector));
  v->data = malloc(inital_capacity * PTR_LEN);
  v->capacity = inital_capacity;
  v->length = 0;

  return v;
}

void
Vector_free(struct Vector* v)
{
  free(v->data);
  free(v);
}

void*
Vector_get(struct Vector* v, size_t idx)
{
  assert(idx < v->length);

  return v->data[idx];
}

void*
Vector_first(struct Vector* v)
{
  if (v->length == 0) {
    return NULL;
  }

  return *v->data;
}

void*
Vector_last(struct Vector* v)
{
  if (v->length == 0) {
    return NULL;
  }

  return v->data[v->length - 1];
}

void
Vector_append(struct Vector* v, void* item)
{
  if (v->length == v->capacity) {
    void** old_data = v->data;
    v->data = malloc(v->capacity * PTR_LEN * 2);

    // Copy old data into new data
    memcpy(v->data, old_data, v->capacity * PTR_LEN);

    free(old_data);
    v->capacity *= 2;
  }

  v->data[v->length] = item;

  v->length += 1;
}

void
Vector_insert(struct Vector* v, void* item, size_t idx)
{
  assert(idx <= v->length);

  if (v->length == v->capacity) {
    void** old_data = v->data;
    v->data = malloc(v->capacity * PTR_LEN * 2);

    // Copy items [0, idx)
    memcpy(v->data, old_data, idx * PTR_LEN);
    // Copy item into idx
    v->data[idx] = item;
    // Copy items [idx + 1..v.length)
    memcpy(&v->data[idx + 1], &old_data[idx], PTR_LEN * (v->length - idx));

    free(old_data);
    v->capacity *= 2;
  } else {
    // Copy items [idx, v.length) into [idx + 1, v.length)
    memmove(&v->data[idx + 1], &v->data[idx], (v->length - idx) * PTR_LEN);
    // Copy item into idx
    v->data[idx] = item;
  }

  v->length += 1;
}

struct Vector*
Vector_concatenate(struct Vector* v_a, struct Vector* v_b)
{
  void** old_data = v_a->data;
  v_a->data = malloc(PTR_LEN * (v_a->length + v_b->length) * 2);

  // Copy items from v_a into new buffer
  memcpy(v_a->data, old_data, PTR_LEN * v_a->length);
  // Copy items from v_b into new buffer
  memcpy(&v_a->data[v_a->length], v_b->data, PTR_LEN * v_b->length);

  v_a->capacity = (v_a->length + v_b->length) * 2;
  v_a->length = v_a->length + v_b->length;

  free(old_data);
  Vector_free(v_b);

  return v_a;
}

void*
Vector_remove(struct Vector* v, size_t idx)
{
  assert(idx < v->length);

  void* item = v->data[idx];
  memmove(&v->data[idx], &v->data[idx + 1], PTR_LEN);
  v->length -= 1;

  return item;
}

void*
Vector_pop(struct Vector* v)
{
  void* item = v->data[v->length - 1];
  v->length -= 1;

  return item;
}

struct VectorIterator*
VectorIterator_new(struct Vector* v)
{
  struct VectorIterator* iterator = malloc(sizeof(struct VectorIterator));
  iterator->vector = v;
  iterator->idx = 0;

  return iterator;
}

void
VectorIterator_free(struct VectorIterator* iterator)
{
  free(iterator);
}

void*
VectorIterator_next(struct VectorIterator* iterator)
{
  if (iterator->idx >= iterator->vector->length) {
    return NULL;
  }

  void* item = Vector_get(iterator->vector, iterator->idx);
  iterator->idx += 1;

  return item;
}