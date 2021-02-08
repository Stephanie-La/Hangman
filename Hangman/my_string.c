 #include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

struct my_string
{
  int size;
  int capacity;
  char* data;
};

typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
  My_string* pString = (My_string*)malloc(sizeof(My_string));
  if(pString != NULL)
    {
      pString -> size = 0;
      pString -> capacity = 7;
      pString -> data =(char*)malloc(sizeof(char)*pString->capacity);
      if(pString-> data == NULL)
      {
	free(pString);
	return NULL;
      }
    }
    return (MY_STRING)pString;
}

void my_string_destroy(Item* pItem)
{
  My_string* pString = (My_string*)*pItem;
  free(pString-> data);
  free(pString);
  pString = NULL;
  *pItem = NULL;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
  My_string* pString = (My_string*)malloc(sizeof(My_string));

  int i = 0, j;
  if(pString != NULL)
    {
      while(c_string[i] != '\0')
	{
	  i++;
	}
      pString->size = i;
      pString->capacity = i+1;
      pString->data= (char*)malloc(sizeof(char*)*pString->capacity);
      if(pString->data == NULL)
	{
	  free(pString);
	  return NULL;
	}
      else
	{
      	for(j = 0; j < pString->size; j++)
	  {
	    pString->data[j] = c_string[j];
	  }
	}
    }
  return pString;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
  My_string* pString = (My_string*) hMy_string;
  return pString->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
  My_string* pString = (My_string*) hMy_string;
  return pString->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
  My_string* pLeft_string = (My_string*)hLeft_string;
  My_string* pRight_string = (My_string*)hRight_string;

  int i = 0;
  while(( i  < pLeft_string->size) && ( i  < pRight_string->size))
      {
	if(pLeft_string->data[i] != pRight_string->data[i])
	  {
	    return pLeft_string->data[i] - pRight_string->data[i];
	  }
	i++;
      }
  return pLeft_string->size - pRight_string->size;
}


Status my_string_extraction(MY_STRING hMy_string, FILE *fp)
{
	int i = 0;
	My_string* pString = (My_string*)hMy_string;
	char c = fgetc(fp);


  	while(c == ' ' || c == '\n'){
		c = fgetc(fp);
	}
	while(c != ' ' &&  c != '\n' && c != EOF){
		if(i + 1 > pString->capacity){
			pString->capacity *= 2;;//if not enough, double the space by doubling capacity
			pString->data = (char*)realloc(pString->data,sizeof(char)* pString->capacity);
			
			if(pString ->data == NULL){
	      			free(pString->data);
	      			return FAILURE;
			}
		}
		pString->data[i] = c;
		c = fgetc(fp);
		i++;
    	}
	pString->size = i;
	if(c == EOF){
		return FAILURE;
	}
	ungetc(' ',fp);

	return SUCCESS;

}


Status my_string_insertion(MY_STRING hMy_string, FILE* fp){
	My_string* pString = (My_string*)hMy_string;
	int i;
	for (i = 0; i < pString->size; i++){
		fprintf(fp, "%c", pString->data[i]);
	}
	return SUCCESS;
}


Status my_string_push_back(MY_STRING hMy_string, char item){
  My_string* pString = (My_string*)hMy_string;
  char *pTemp;
  int i;
  if(pString->size >= pString->capacity){
   pTemp = (char*)malloc(sizeof(char)*2 *pString->capacity);
    if(pTemp == NULL){
      return FAILURE;
    }
    for(i = 0; i < pString->size; i++){
      pTemp[i] = pString->data[i];
      }
    free(pString->data);
    pString->data= pTemp;
    pString->capacity *= 2;
  }
  pString->data[pString->size] = item;
  pString->size++;
  return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string){
  My_string* pString = (My_string*)hMy_string;
  if(pString->size <= 0){
    return FAILURE;
  }
  pString->data[pString->size -1] = '\0';
  pString->size--;
  return SUCCESS;
}



char* my_string_at(MY_STRING hMy_string, int index){
  My_string* pString = (My_string*)hMy_string;
  if(index < 0 || index >= pString->size){
    return NULL;
  }
  return &(pString->data[index]);
}



char* my_string_c_str(MY_STRING hMy_string){
  My_string* pString  = (My_string*)hMy_string;
  char* pTemp;
  int i;
  if(pString->size + 1 > pString->capacity){
    pTemp = (char*)malloc(sizeof(char)*2 * pString->capacity);
      if(pTemp == NULL){
	free(pTemp);
	return NULL;
      }
      for (i = 0; i < pString->capacity; i++){
	   pTemp[i] = pString->data[i];
            }
      free(pString->data);
      pString->data = NULL;
      pString->data = pTemp;
      pTemp = NULL;
      pString->capacity *= 2;
  }
  pString->data[pString->size] = '\0';
      return pString->data;
}



Status my_string_concat(MY_STRING hResult, MY_STRING hAppend){
  My_string* pResult = (My_string*)hResult;
  My_string* pAppend = (My_string*)hAppend;
  int i;

  for(i = 0; i < pAppend->size; i++){
    if(my_string_push_back(pResult, *my_string_at(pAppend, i))== FAILURE){
      return FAILURE;
      }
  }
  return SUCCESS;
} 
       
Boolean my_string_empty(MY_STRING hMy_string){
  My_string* pString = (My_string*)hMy_string;
  if(pString->size == 0){
    return TRUE;
  }
  return FALSE;
}

void my_string_assignment(Item* pLeft, Item Right){

    	My_string *pMy_Right = (My_string*) Right;
    	int i;

    if (*pLeft == NULL)
    {
	*pLeft = my_string_init_default();
    }

    for (i = 0; i <pMy_Right->size; i++)
    {
	my_string_push_back(*pLeft, pMy_Right->data[i]);
    }

}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess){
	int i;
	My_string* pCurrent_word_family = (My_string*)current_word_family;
	My_string* pNew_key  = (My_string*)new_key;
	My_string* pWord = (My_string*)word;

	guess = tolower(guess);

	my_string_assignment(&new_key, current_word_family);
	
	for(i = 0; i < pWord->size; i++){
		if(pWord->data[i] == guess){
			pNew_key->data[i] = guess;	
		}
	}
	return SUCCESS;
}
