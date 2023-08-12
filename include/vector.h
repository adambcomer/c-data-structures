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

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

#define PTR_LEN sizeof(void*)

struct Vector
{
  void** data;
  size_t capacity;
  size_t length;
};

struct Vector*
Vector_new(size_t inital_capacity);

void
Vector_free(struct Vector* v);

void*
Vector_get(struct Vector* v, size_t idx);

void*
Vector_first(struct Vector* v);

void*
Vector_last(struct Vector* v);

void
Vector_append(struct Vector* v, void* item);

void
Vector_insert(struct Vector* v, void* item, size_t idx);

struct Vector*
Vector_concatenate(struct Vector* v_a, struct Vector* v_b);

void*
Vector_remove(struct Vector* v, size_t idx);

void*
Vector_pop(struct Vector* v);

struct VectorIterator
{
  struct Vector* vector;
  size_t idx;
};

struct VectorIterator*
VectorIterator_new(struct Vector* v);

void
VectorIterator_free(struct VectorIterator* iterator);

void*
VectorIterator_next(struct VectorIterator* iterator);

#endif /* VECTOR_H */