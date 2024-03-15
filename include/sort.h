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

#ifndef SORT_H
#define SORT_H

#include <stddef.h>

void
Sort_bubblesort(void** data, size_t length, int (*cmp)(void* a, void* b));

void
Sort_mergesort(void** data, size_t length, int (*cmp)(void* a, void* b));

void
Sort_heapsort(void** data, size_t length, int (*cmp)(void* a, void* b));

#endif /* SORT_H */
