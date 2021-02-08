#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "unit_test.h"
#include <string.h>

Status test_init_default_returns_nonNULL(char* buffer, int length){
  MY_STRING hString = NULL;
  hString = my_string_init_default();
  if(hString == NULL){
    my_string_destroy(&hString);
    strncpy(buffer, "test_init_default_returns_nonNULL\n"
	     "my_string_init_default returns NULL", length);
    return FALSE;
    }
    else{
      my_string_destroy(&hString);
      strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
    }
  return SUCCESS;
}

  Status test_get_size_on_init_default_returns_0(char* buffer, int length){
 MY_STRING hString = NULL;
 Status status;
 hString = my_string_init_default();
 if(my_string_get_size(hString) != 0){
   status = FAILURE;
   printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
   strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	   "Did not receive 0 from get_size after init_default\n", length);
         }
         else {
	   status = SUCCESS;
	   strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
		   , length);
	 }
          my_string_destroy(&hString);
           return status;
  }

Status sla_test_get_size_on_init_c_str_returns_0(char* buffer, int length){
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("I had a great day.\n");
	if (my_string_get_size(hString) != 0) {
		status = SUCCESS;
		strncpy(buffer, "sla_test_get_size_on_init_c_str_returns_non0\n"
			, length);
	}
	else {
		status = FAILURE;
		printf("Expected a size of non 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "sla_test_get_size_on_init_c_str_returns_non_0\n"
			"Did not receive a non 0 from sla_test_get_size_on_init_c_str_returns_non0\n", length);
	}
	my_string_destroy(&hString);
	return status;
 }

Status sla_test_destroy(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();

	my_string_destroy(&hString);

	if (hString != NULL) {
		status = FAILURE;
		printf("Expected to destroy string but got %s\n", my_string_c_str(hString));
		strncpy(buffer, "sla_test_destroy\n"
			"Did not receive a destroy from sla_test_destroy\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_destroy\n", length);
	}
	return status;
}

Status sla_test_push_back(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();

	int i;
	for (i = 0; i < 10; i++) {
		my_string_push_back(hString, 'a');
	}
	if (my_string_get_size(hString) >= 11 || my_string_get_size <= 0) {
		status = FAILURE;
		printf("Expected to push string, but got %s\n", my_string_c_str(hString));
		strncpy(buffer, "sla_test_push_back\n"
			"Did not receive a letter from sla_test_push_back\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_push_back\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status sla_test_pop_back(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("I had a great day.\n");
	int i;
	int size = my_string_get_size(hString);
	
	for (i = 0; i < size; i++) {
		my_string_pop_back(hString);
	}

	if ((my_string_get_size)(hString) < 0 || (my_string_get_size(hString) > 0)) {
		status = FAILURE;
		printf("Expected to pop string but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "sla_test_pop_back\n"
			"Did not pop from asla_test_pop_back\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_pop_back\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status sla_test_check_size(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("I had a great day.\n");
	int size = my_string_get_size(hString);

	if (my_string_get_size(hString) < 0 || (my_string_get_size(hString) > size)) {
		status = FAILURE;
		printf("Expected to get %d, but got %d\n", size, my_string_get_size(hString));
		strncpy(buffer, "sla_test_check_size\n"
			"Did not get correct size using sla_test_check_size\n", length);
		}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_check_size\n"
			, length);
	}
	my_string_destroy(&hString);
	return status;
}

Status sla_test_check_capacity(char* buffer, int length) {
	MY_STRING hString = NULL;
    Status status;
    hString = my_string_init_c_string("I had a great day.\n");
    
    int capacity = my_string_get_capacity(hString);
    
    if ((my_string_get_capacity(hString) < 0) || (my_string_get_capacity(hString) > capacity)) {
        status = FAILURE;
        printf("Expected to get %d, but got %d\n", capacity, my_string_get_capacity(hString));
        strncpy(buffer, "sla_test_check_capacity\n"
                "Did not get capacity from sla_test_check_capacity\n", length);
    }
    else{
        status = SUCCESS;
        strncpy(buffer, "sla_test_check_capacity\n"
                , length);
    }  
    my_string_destroy(&hString);
    return status;
}

Status sla_test_concat(char* buffer, int length) {
	MY_STRING hResult = NULL;
	MY_STRING hAppend = NULL;
	Status status;

	hResult = my_string_init_c_string("I had");
	hAppend = my_string_init_c_string("a great day");

	int result_size = my_string_get_size(hResult);
	int append_size = my_string_get_size(hAppend);
	int size = result_size + append_size;
	
	my_string_concat(hResult, hAppend);

	if (my_string_get_size(hResult) >= size + 2) {
		status = FAILURE;
		printf("Expected to get %d, but got %d\n", size, my_string_get_size(hResult));
		strncpy(buffer, "sla_test_concat\n"
			"Did not get size from sla_test_concat\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_concat\n", length);
	}
	my_string_destroy(&hResult);
	my_string_destroy(&hAppend);
	return status;
}

Status sla_test_size_out_of_bounds(char* buffer, int length) {
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("Happy birthday\n");

	char* at = my_string_at(hString, 15);

	if (at != NULL) {
		status = FAILURE;
		printf("Expected to get nothing, but got %s\n", at);
		strncpy(buffer, "sla_test_size_out_of_bounds\n"
			"Did not get result from sla_test_size_out_of_bounds\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_size_out_of_bounds\n", length);
	}
	my_string_destroy(&hString);
	return status; 
}

Status sla_test_compare_lexicographically(char* buffer, int length) {
	MY_STRING hRight = NULL;
	MY_STRING hLeft = NULL;
	Status status;
	hRight = my_string_init_c_string("dog");
	hLeft = my_string_init_c_string("dog");

	int lexico = my_string_compare(hLeft, hRight);

	if (lexico < 0 || lexico > 0) {
		status = FAILURE;
		printf("Expected to get 0, but got %d\n", lexico);
		strncpy(buffer, "sla_test_compare_lexicographically\n"
			"Did not get result from sla_test_compare_lexicographically\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_compare_lexicographically\n", length);
	}
	my_string_destroy(&hRight); 
	my_string_destroy(&hLeft);
	return status;
}

Status sla_test_concat_lengths(char* buffer, int length) {
	MY_STRING hResult = NULL;
	MY_STRING hAppend = NULL;
	Status status;

	hResult = my_string_init_c_string("Equal Length");
	hAppend = my_string_init_c_string("Equal Length");

	int result_size = my_string_get_size(hResult);
	int append_size = my_string_get_size(hAppend);
	int size = result_size + append_size;

	my_string_concat(hResult, hAppend);

	if (my_string_get_size(hResult) >= size + 2) {
		status = FAILURE;
		printf("Expected to get %d, but got %d\n", size, my_string_get_size(hResult));
		strncpy(buffer, "sla_test_concat_lengths\n"
			"Did not get size from sla_test_concat_lengths\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_concat_lengths\n"
			, length);
	}

	my_string_destroy(&hResult);
	my_string_destroy(&hAppend);

	return status;
}

Status sla_test_compare_length_a_z_returns_0(char* buffer, int length) {
	MY_STRING hRight = NULL;
	MY_STRING hLeft = NULL;
	Status status;
	hRight = my_string_init_c_string("a b c d e f g h i j k l m n o p q r s t u v w x y z");
	hLeft = my_string_init_c_string("a b c d e f g h i j k l m n o p q r s t u v w x y z");

	int lexic = my_string_compare(hLeft, hRight);

	if (lexic < 0 || lexic > 0) {
		status = FAILURE;
		printf("Expected to get 0, but got %d\n", lexic);
		strncpy(buffer, "sla_test_compare_length_a_z_returns_0\n"
			"Did not get result from sla_testsla-_compare_length_a_z_returns_0\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_compare_length_a_z_returns_0\n", length);
	}

	my_string_destroy(&hRight);
	my_string_destroy(&hLeft);

	return status;
}

Status sla_test_compare_equal_length_z_a(char* buffer, int length) {
	MY_STRING hRight = NULL;
	MY_STRING hLeft = NULL;
	Status status;
	hRight = my_string_init_c_string("z y x w v u t s r q p o n m l k j i h g f e d c b a");
	hLeft = my_string_init_c_string("z y x w v u t s r q p o n m l k j i h g f e d c b a");

	int lexic = my_string_compare(hLeft, hRight);

	if (lexic < 0 || lexic > 0) {
		status = FAILURE;
		printf("Expected to get 0, but got %d\n", lexic);
		strncpy(buffer, "sla_test_compare_equal_length_z_a\n"
			"Did not get result using sla_test_compare_equal_length_z_a\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_compare_equal_length_z_a\n", length);
	}
	my_string_destroy(&hRight);
	my_string_destroy(&hLeft);
	return status;
}

Status sla_test_compare_length_A_Z(char* buffer, int length) {
	MY_STRING hRight = NULL;
	MY_STRING hLeft = NULL;
	Status status;
	hRight = my_string_init_c_string("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
	hLeft = my_string_init_c_string("A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");

	int lexic = my_string_compare(hLeft, hRight);

	if (lexic < 0 || lexic > 0) {
		status = FAILURE;
		printf("Expected to get 0, but got %d\n", lexic);
		strncpy(buffer, "sla_test_compare_length_A_Z\n"
			"Did not get result from sla_test_compare_length_A_Z\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_compare_length_A_Z\n"
			, length);
	}
	my_string_destroy(&hRight);
	my_string_destroy(&hLeft);
	return status;
}

Status sla_test_compare_length_Z_A(char* buffer, int length) {
	MY_STRING hRight = NULL;
	MY_STRING hLeft = NULL;
	Status status;
	hRight = my_string_init_c_string("Z Y X W V U T S R Q P O N M L K J I H G F E D C B A");
	hLeft = my_string_init_c_string("Z Y X W V U T S R Q P O N M L K J I H G F E D C B A");

	int lexic = my_string_compare(hLeft, hRight);

	if (lexic < 0 || lexic > 0) {
		status = FAILURE;
		printf("Expected to get 0, but got %d\n", lexic);
		strncpy(buffer, "sla_test_compare_length_Z_A\n"
			"Did not get result from sla_test_compare_length_Z_A\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_compare_length_Z_A\n", length);
	}
	my_string_destroy(&hRight);
	my_string_destroy(&hLeft);
	return status;
}

Status sla_test_compare_unequal_length(char* buffer, int length) {
	MY_STRING hRight = NULL;
	MY_STRING hLeft = NULL;
	Status status;
	hRight = my_string_init_c_string("difference");
	hLeft = my_string_init_c_string("ddifference");

	int lexic = my_string_compare(hLeft, hRight);

	if (lexic == 0) {
		status = FAILURE;
		printf("Expected to get %d, but got 0\n", lexic);
		strncpy(buffer, "sla_test_compare_unequal_length\n"
			"Did not get result from sla_test_compare_unequal_length\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_compare_unequal_length\n", length);
	}

	my_string_destroy(&hRight);
	my_string_destroy(&hLeft);

	return status;
}

Status sla_test_compare_unequal_sides_left_1_short(char* buffer, int length) {
	MY_STRING hRight_string = NULL;
	MY_STRING hLeft_string = NULL;
	Status status;
	hRight_string = my_string_init_c_string("unequal with longer right string");
	hLeft_string = my_string_init_c_string("unequal with left shorter");

	int lexic;
	lexic = my_string_compare(hLeft_string, hRight_string);

	if (lexic >= 0) {
		status = FAILURE;
		printf("Expected to get negative number, but got %d\n", lexic);
		strncpy(buffer, "sla_test_compare_unequal_sides_left_1_short\n"
			"Did not get result from sla_test_compare_unequal_sides_left_1_short\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_compare_unequal_sides_left_1_short\n", length);
	}
	my_string_destroy(&hRight_string);
	my_string_destroy(&hLeft_string);
	return status;
}

Status sla_test_compare_unequal_sides_right_1_short(char* buffer, int length) {
	MY_STRING hRight = NULL;
	MY_STRING hLeft = NULL;
	Status status;
	hRight = my_string_init_c_string("unequal with right being longer");
	hLeft = my_string_init_c_string("unequal with left short");

	int lexic = my_string_compare(hLeft, hRight);

	if (lexic >= 0) {
		status = FAILURE;
		printf("Expected to get a negative number, but got %d\n", lexic);
		strncpy(buffer, "sla_test_compare_unequal_sides_right_1_short\n"
			"Did not get correct result using the function sla_test_compare_unequal_sides_right_1_short\n", length);
	}
	else {
		status = SUCCESS;
		strncpy(buffer, "sla_test_compare_unequal_sides_right_1_short\n", length);
	}
	my_string_destroy(&hRight);
	my_string_destroy(&hLeft);
	return status;
}

Status sla_test_extraction_check_create_file(char* buffer, int length) {
	FILE *file;
	Status status;

	file = fopen("extraction_test.txt", "w");

	if (file != NULL){
		fprintf(file, "Auto-generated test file for function.\n");
		fclose(file);

		status = SUCCESS;
		strncpy(buffer, "sla_test_extraction_create file\n", length);
	}
	else {
		printf("Unable to write file to file system\n");
			strncpy(buffer, "sla_test_extraction_createFile", length);
			status = FAILURE;
		}
	return status;
}

Status sla_test_extraction_check_read_file(char* buffer, int length) {
	FILE *file;
	Status status;		
	MY_STRING hString1 = my_string_init_default();
	MY_STRING hString2 = my_string_init_c_string("aa");

	file = fopen("dictionary.txt", "r");
	if (file != NULL)
		{
			my_string_extraction(hString1, file); 
		
			if (my_string_compare(hString1, hString2) == 0){
				status = SUCCESS;
				strncpy(buffer, "sla_test_extraction_check_read_file\n", length);
			}
			else{
				printf("Expected 0 but got %d\n", my_string_compare(hString1, hString2));
				strncpy(buffer, "sla_test_extraction_check_read_file", length);
				status = FAILURE;
			}

		fclose(file);
	}
	else{
	//	printf("Unable to read file: dictionary.txt\n");
		strncpy(buffer, "sla_test_extraction_check_read_file", length);
		status = FAILURE;
	}
	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status sla_test_extraction_check_delete_file(char* buffer, int length) {
	int result;
	Status status;
	result = remove("extraction_test.txt");
	
	if (result == 0){
			status = SUCCESS;
			strncpy(buffer, "sla_test_extraction_check_delete_file\n", length);
			}
			else{
			printf("Unable to delete file: extraction_test.txt\n");
			strncpy(buffer, "sla_test_extraction_check_delete_file", length);
			status = FAILURE;
		}
		return status;
}

Status sla_test_compare_unequal_lengths_with_words(char* buffer, int length)
{
	int difference = -1;
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	hString1 = my_string_init_c_string("simple");
	hString2 = my_string_init_c_string("simples");

	if (my_string_compare(hString1, hString2) != difference){
		status = FAILURE;
		printf("Expected %d but got %d\n", difference, my_string_compare(hString1, hString2));
		strncpy(buffer, "sla_test_compare_unequal_lengths_with_words", length);
	}
	else{
		status = SUCCESS;
		strncpy(buffer, "sla_test_compare_unequal_lengths_with_words\n", length);
	}
	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}

Status sla_test_compare_unequal_lengths_with_words_reverse(char* buffer, int length)
{
	int difference = 25;
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	hString1 = my_string_init_c_string("zoo");
	hString2 = my_string_init_c_string("adventure");

	if (my_string_compare(hString1, hString2) != difference) {
		status = FAILURE;
		printf("Expected %d but got %d\n", difference, my_string_compare(hString1, hString2));
		strncpy(buffer, "sla_test_compare_unequal_lengths_with_words_reverse", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "sla_test_compare_unequal_lengths_with_words_reverse\n", length);
	}
	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	return status;
}
Status sla_test_my_string_returns_blank_string(char* buffer, int length) {

	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("");

	if (my_string_empty(hString)) {
		status = SUCCESS;
		strncpy(buffer, "sla_test_my_string_returns_blank_string\n"
			, length);
	}
	else {
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "sla_test_my_string_returns_blank_string\n"
			"Did not receive a non 0 from sla_test_my_string_returns_blank_string\n", length);
	}
	my_string_destroy(&hString);
	return status;
}
      
