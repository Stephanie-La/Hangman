#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
  MY_STRING hMy_string = NULL;
  // MY_STRING pLeft_string = NULL;
  // MY_STRING pRight_string = NULL;
   FILE* fp;
  hMy_string = my_string_init_default();
  /*
  if(hMy_string == NULL)
    {
      printf("my_string_init_default failed for hMy_string.\n");
      exit(1);
    }
   pLeft_string = my_string_init_c_string("abc");
   if(pLeft_string == NULL)
     {
	printf("my_string_init_c_string for pLeft failed\n");
        exit(1);
     }
   pRight_string = my_string_init_c_string("ab");
   if(pRight_string == NULL)
     {
       printf(" my_string_init_c_string for pRight failed\n");
       exit(1);
     }
   */

  fp = fopen("simple.txt", "r");
  
  while(my_string_extraction(hMy_string, fp))
    {
      my_string_insertion(hMy_string, stdout);
      printf("\n");
      if(fgetc(fp) == ' ')
	{
	  printf("Found a space after the string\n");
	}
    }
   
   my_string_destroy(&hMy_string);
   fclose(fp);
  
   // my_string_get_size(pLeft_string);
   //  my_string_get_capacity(pLeft_string);
  
     //  printf("String compare: %d\n", my_string_compare(pLeft_string, pLeft_string));
    //   printf("String compare: %d\n", my_string_compare(pRight_string, pLeft_string));
    //   printf("String compare: %d\n", my_string_compare(pLeft_string, pRight_string));
       
    //  my_string_destroy(&hMy_string);
    // my_string_destroy(&pLeft_string);
    //my_string_destroy(&pRight_string);
		      
  return 0;
}
