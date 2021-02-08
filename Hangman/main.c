#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"
#include "associative_array.h"


int get_word_length(void);
int get_num_of_guesses(void);
char getGuess(void);
Boolean check_guess(MY_STRING past_guesses, char current_guess);
char play_again(void);
void clear_keyboard_buffer();
void evil_hangman_game(int word_length, int number_of_guesses);


int main (int argc, char* argv[]){
	int word_length;
   	int num_of_guesses;
	do{
		printf("What is the length of your word?\n");
		word_length = get_word_length();
		num_of_guesses = get_num_of_guesses();
		evil_hangman_game(word_length, num_of_guesses);
  	}
	while(play_again() == 'y');


	return 0;

}


int get_word_length(void){
	int word_length;
	scanf("%d", &word_length);
	clear_keyboard_buffer();
	if(word_length < 2 || word_length > 29 || word_length == 27 || word_length == 26 || word_length == 23 || word_length == 25){
		printf("Invalid word length. Please enter another word length:\n");
		get_word_length();
	}
	else{
		return get_word_length();
	}
}

int get_num_of_guesses(void){
	int num_of_guesses;
	printf("How many guesses do you want?\n");
	scanf("%d", &num_of_guesses);
	clear_keyboard_buffer();
	if(num_of_guesses < 0){
		printf("That is not valid input. Enter a positive integer.. it's not difficult.\n");
		num_of_guesses = get_num_of_guesses();
		}
		return num_of_guesses;
}

void evil_hangman_game(int word_length, int num_of_guesses){
	GENERIC_VECTOR current_word_group = generic_vector_init_default(my_string_assignment, my_string_destroy);
	MY_STRING hString = my_string_init_default();
	MY_STRING key = my_string_init_default();
	MY_STRING used_letters = my_string_init_default();
	MY_STRING new_key;
	GENERIC_VECTOR temp = NULL;

	int i = 0;
	int guesses_left = num_of_guesses;
	char current_guess;
	TREE word_nodes;
	FILE* fp;
	fp = fopen("dictionary.txt", "r");
	while(my_string_extraction(hString, fp)){
		if(my_string_get_size(hString) == word_length){
			generic_vector_push_back(current_word_group, hString);
		}
	}
	fclose(fp);
	my_string_destroy(&hString);
	for(i = 0; i < word_length; i++){
		my_string_push_back(key, '_');
	}
	while(guesses_left > 0){
		printf("You have %d guesses remaining.\n", generic_vector_get_size(current_word_group));
		printf("You have %d guesses left.\n", guesses_left);
		printf("Letter used: ");
		for(i = 0; i < my_string_get_size(used_letters ); i++){
		printf("%s", my_string_at(used_letters, i));
		}
		printf("\nword: ");
		my_string_insertion(key, stdout);
		printf("\n");
		do{
			current_guess = getGuess();
		}
		while(check_guess(used_letters, current_guess));
		printf("\n\n\n");
		my_string_push_back(used_letters, current_guess);
		word_nodes = tree_init_default();
		new_key = my_string_init_default();
		for(i = 0; i < generic_vector_get_size(current_word_group); i++){
			get_word_key_value(key, new_key, generic_vector_at(current_word_group, i), current_guess);
			tree_add(word_nodes, new_key, generic_vector_at(current_word_group, i));
			my_string_insertion(generic_vector_at(current_word_group, i), stdout);
			printf(": ");
			my_string_insertion(new_key, stdout);
			printf("\n");
		}
		printf("\n");
		temp = largest_word_group(word_groups);
		generic_vector_destroy(&current_word_group);
		tree_destroy(&word_groups);
		my_string_destroy(&new_key);
		current_word_group = generic_vector_init_default(my_string_assignment, my_string_destroy);
 		new_key = my_string_init_default();
		for(i = 0; i < generic_vector_get_size(temp); i ++){
			generic_vector_push_back(current_word_group, generic_vector_at(temp, i));
		}	
		generic_vector_destroy(&temp);
		get_word_key_value(key, new_key, generic_vector_at(current_word_group(current_word_group, 0), current_guesses));
		if(my_string_compare(key, new_key) == 0){
			printf("I'm sorry there was no %c's in this word.\n");
			guesses_left;
			}
			my_string_assignment(&key, new_key);
			my_string_destroy(&new_key);

			if(guesses_left <= 0){
				printf("Sorry! You have lost the game.\n");
				printf("The word was actually '%s'.\n\n", my_string_c_str(generic_vector_at(current_word_group, 0));
				break;
				}
				if(my_string_compare(generic_vector_at(current_word_group, 0), key) == 0){
					printf("Congratulations you won!\n");
					printf("The word was: %s \n\n", my_string_c_str(generic_vector_at(current_word_group, 0)));
					guesses_left = 0;
					}

			}
			generic_vector_destroy(&current_word_group);
			my_string_destroy(&used_letters);
			my_string_destroy(&key);
	}



char getGuess(void){
	char c;
	printf("Guess a character: ");
	scanf("%c", &c);
	clear_keyboard_buffer();
	
	if(isalpha(c)){
		if(isupper(c)){
			c = tolower(c);
		}
		return c;
	}
	else{
		printf("Enter a lowercase letter: \n");
		getGuess();
	}	
}


Boolean check_guess(MY_STRING past_guesses, char current_guess){
	My_string temp = (My_string*)past_guesses;
	int i;
	for(i = 0; i < temp->size; i++){
		if(temp->data[i] == current_guess){
			return TRUE;
		}
	}
	return FALSE;
}

char play_again(void){
	char play;
	printf("Would you like to play again?(y/n)\n");
	scanf("%c", &play);
	clear_keyboard_buffer();
	return play;
}

void clear_keyboard_buffer(){
	char c;
	scanf("%c", &c);
	while (c != '\n'){
		scanf("%c", &c);
	}
}


/*
	GENERIC_VECTOR hVector[30] = {NULL};
	MY_STRING hString = NULL;
	FILE* fp = NULL;
	int i;
	hString = my_string_init_default();
	if(hString == NULL){
		printf("Failed to save string.\n");
		exit(1);
		}
		for(i = 0; i < 30; i++){
			hVector[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
			if(hVector[i] == NULL){
				printf("Not created.\n");
				exit(1);
			}
		}
		fp = fopen("dictionary.txt", "r");
		if(fp == NULL){
			printf("Did not open file.\n");
			exit(1);
			} 
			while(my_string_extraction(hString, fp) == SUCCESS){
				if(my_string_get_size(hString) < 30){
					generic_vector_push_back(hVector[my_string_get_size(hString)], hString);
				}
			}
			for(i = 0; i < 30; i++){
			  printf("The number of words in the dictionary with %d charcters is: %d\n ", i , generic_vector_get_size(hVector[i]));
			}
 			for(i = 0; i < 30; i++){
				generic_vector_destroy(&(hVector[i]));
			}
			fclose(fp);
			my_string_destroy(&hString);

*/

