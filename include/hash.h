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

#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdint.h>

#define FNV_OFFSET 14695981039346656037u;
#define FNV_PRIME 1099511628211u;

/*
 * 64 bit FNV-1a hash function.
 *
 * Reference:
 * https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 */
uint64_t
fnv_1a_hash(char* data, size_t data_len);

#endif /* HASH_H */