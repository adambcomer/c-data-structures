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

#include "sort.h"
#include <stdlib.h>
#include <string.h>

void
Sort_bubblesort(void** data, size_t length, int (*cmp)(void* a, void* b))
{
  for (size_t i = 0; i < length; i++) {
    for (size_t j = i + 1; j < length; j++) {
      if (cmp(data[i], data[j]) == 1) {
        void* temp = data[i];
        data[i] = data[j];
        data[j] = temp;
      }
    }
  }
}

void
_mergesort_merge(void** data,
                 size_t start,
                 size_t mid,
                 size_t end,
                 int (*cmp)(void* a, void* b))
{
  void** new_data = malloc((end - start) * sizeof(void*));

  size_t low_idx = start;
  size_t high_idx = mid;

  size_t idx = 0;
  while (low_idx < mid && high_idx < end) {
    if (cmp(data[high_idx], data[low_idx]) == 1) {
      new_data[idx] = data[low_idx];
      low_idx += 1;
    } else {
      new_data[idx] = data[high_idx];
      high_idx += 1;
    }
    idx += 1;
  }

  while (low_idx < mid) {
    new_data[idx] = data[low_idx];
    low_idx += 1;
    idx += 1;
  }
  while (high_idx < end) {
    new_data[idx] = data[high_idx];
    high_idx += 1;
    idx += 1;
  }

  memcpy(&data[start], new_data, (end - start) * sizeof(void*));
  free(new_data);
}

void
_mergesort_divide(void** data,
                  size_t start,
                  size_t end,
                  int (*cmp)(void* a, void* b))
{
  if ((end - start) < 2) {
    return;
  }

  size_t mid = ((end - start) / 2) + start;
  _mergesort_divide(data, start, mid, cmp);
  _mergesort_divide(data, mid, end, cmp);

  _mergesort_merge(data, start, mid, end, cmp);
}

void
Sort_mergesort(void** data, size_t length, int (*cmp)(void* a, void* b))
{
  _mergesort_divide(data, 0, length, cmp);
}

void
_heapsort_heapify(void** data,
                  size_t length,
                  size_t idx,
                  int (*cmp)(void* a, void* b))
{
  size_t l = idx * 2 + 1;
  size_t r = (idx + 1) * 2;

  size_t largest = idx;

  if (l < length && cmp(data[l], data[idx]) == 1) {
    largest = l;
  }
  if (r < length && cmp(data[r], data[idx]) == 1) {
    largest = r;
  }

  if (largest != idx) {
    void* temp = data[idx];
    data[idx] = data[largest];
    data[largest] = temp;

    _heapsort_heapify(data, length, largest, cmp);
  }
}

void
Sort_heapsort(void** data, size_t length, int (*cmp)(void* a, void* b))
{
  for (size_t i = 0; i < length; i++) {
    _heapsort_heapify(data, length, length - i - 1, cmp);
  }

  for (size_t i = length - 1; i > 0; i--) {
    void* largest = data[0];
    data[0] = data[i];
    data[i] = largest;

    _heapsort_heapify(data, i, 0, cmp);
  }
}
