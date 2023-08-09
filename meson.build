project('data-structures', 'c', default_options : ['c_std=c17'])

include = include_directories('include')

lib = library('data_structures', 'src/linked_list.c', include_directories : include)

munit = dependency('munit', fallback: ['munit', 'munit_dep'])

linked_list_test = executable('linked_list_test', 'tests/linked_list_test.c', link_with : lib, dependencies : munit)
test('linked_list_test', linked_list_test)
