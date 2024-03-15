project('data-structures', 'c', default_options : ['c_std=c17'])

include = include_directories('include')

lib = library('data_structures', ['src/linked_list.c', 'src/vector.c', 'src/hash.c', 'src/set.c', 'src/sort.c'], include_directories : include)

munit = dependency('munit', fallback: ['munit', 'munit_dep'])

linked_list_test = executable('linked_list_test', 'tests/linked_list_test.c', link_with : lib, dependencies : munit, include_directories : include)
test('linked_list_test', linked_list_test)

vector_test = executable('vector_test', 'tests/vector_test.c', link_with : lib, dependencies : munit, include_directories : include)
test('vector_test', vector_test)

hash_test = executable('hash_test', 'tests/hash_test.c', link_with : lib, dependencies : munit, include_directories : include)
test('hash_test', hash_test)

set_test = executable('set_test', 'tests/set_test.c', link_with : lib, dependencies : munit, include_directories : include)
test('set_test', set_test)

sort_test = executable('sort_test', 'tests/sort_test.c', link_with : lib, dependencies : munit, include_directories : include)
test('sort_test', sort_test)
