#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"


Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);

Status sla_test_get_size_on_init_c_str_returns_0(char* buffer, int length);
Status sla_test_destroy(char* buffer, int length);

Status sla_test_push_back(char* buffer, int length);
Status sla_test_pop_back(char* buffer, int length);

Status sla_test_check_size(char* buffer,int length);
Status sla_test_check_capacity(char* buffer, int length);

Status sla_test_concat(char* buffer, int length);
Status sla_test_size_out_of_bounds(char* buffer, int length);

Status sla_test_compare_lexicographically(char* buffer, int length);
Status sla_test_concat_lengths(char* buffer, int length);

Status sla_test_compare_length_a_z_returns_0(char* bufer, int length);
Status sla_test_compare_equal_length_z_a(char* buffer, int length);

Status sla_test_compare_length_A_Z(char* buffer, int length);
Status sla_test_compare_length_Z_A(char* buffer, int length);

Status sla_test_compare_unequal_length(char* buffer, int length);
Status sla_test_compare_unequal_sides_left_1_short(char* buffer, int lemgth);

Status sla_test_compare_unequal_sides_right_1_short(char* buffer, int length);
Status sla_test_extraction_check_create_file(char* buffer, int length);

Status sla_test_extraction_check_read_file(char* buffer, int length);
Status sla_test_extraction_check_delete_file(char* buffer, int length);

Status sla_test_compare_unequal_lengths_with_words(char* buffer, int length);
Status sla_test_compare_unequal_lengths_with_words_reverse(char* buffer, int length);

Status sla_test_my_string_returns_blank_string(char* buffer, int length);






#endif
