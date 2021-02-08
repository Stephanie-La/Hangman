#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[]){
  Status (*tests[])(char*, int) = {
    test_init_default_returns_nonNULL,
    test_get_size_on_init_default_returns_0,
    sla_test_get_size_on_init_c_str_returns_0,
    sla_test_destroy,
    sla_test_push_back,
    sla_test_pop_back,
    sla_test_check_size,
    sla_test_check_capacity,
    sla_test_concat,
    sla_test_size_out_of_bounds,
    sla_test_compare_lexicographically,
    sla_test_concat_lengths,
    sla_test_compare_length_a_z_returns_0,
    sla_test_compare_equal_length_z_a,
    sla_test_compare_length_A_Z,
    sla_test_compare_length_Z_A,
    sla_test_compare_unequal_length,
    sla_test_compare_unequal_sides_left_1_short,
    sla_test_compare_unequal_sides_right_1_short,
    sla_test_extraction_check_create_file,
    sla_test_extraction_check_read_file,
    sla_test_extraction_check_delete_file,
    sla_test_compare_unequal_lengths_with_words,
    sla_test_compare_unequal_lengths_with_words_reverse,
    sla_test_my_string_returns_blank_string,
      };
    int number_of_functions = sizeof(tests)/sizeof(tests[0]);
    int i;
    char buffer[500];
    int success_count = 0;
    int failure_count = 0;
    for(i = 0; i < number_of_functions; i++){
      if(tests[i](buffer,500) == FAILURE){
	printf("FAILED: Test %d failed miserably\n", i);
	printf("\t%s\n", buffer);
	failure_count++;
      }
      else{
	//printf("PASS: test %d passed\n", i);
	//printf("\t%s\n", buffer);
	success_count++;
      }
    }
    printf("Total number of tests: %d\n", number_of_functions);
    printf("%d/%d Pass, %d/%d Failure\n", success_count,
    number_of_functions, failure_count, number_of_functions);
    return 0;
}
