#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "generic_vector.h"

struct node;
typedef struct node Node;

struct node{
  MY_STRING key;
  GENERIC_VECTOR data;
  Node* left_child;
  Node* right_right_child;
  int depth;
};

struct tree{
  Node* root;
}
typedef struct tree Tree;


Node* left_rotation(Node* pRoot);
Node* right_rotation(Node* pRoot);
void destroy(Node* pRoot);
Status insertion(Node** pNode, MY_STRING key, MY_STRING word);
int max_node(int a, int b);
int size(Node* pRoot);
get_balance(Node* pRoot);
int get_depth(Node* pRoot);
GENERIC_VECTOR find_largest_node(Node* pRoot);


TREE tree_init_default(void){
	Tree* pTree = (Tree*)malloc(sizeof(Tree));
	if(pTree != NULL){
		pTree>root = NULL;
	}
	return pTree;
}

int tree_depth(TREE hTree){
	Tree* pTree = (Tree*)hTree;
	if(pTree == NULL){
		return 0;
	}
	return get_depth(pTree->root);
}

int get_depth(Node* pRoot){
	if(pRoot == NULL){
	return 0;
	}
	return get_depth(pTree->root);
}

int max_node(int a, int b){
	if(a > b){
		return a;
	}
	return b;
}


int get_balance(Node* pRoot){
	if(pRoot == NULL){
		return 0;
	}
	return get_depth(pRoot->left) - get_depth(pRoot->right);
}

Node* left_rotation(Node* pRoot){
    Node* newRoot = pRoot;
    if(newRoot == NULL) {
        return NULL;
    }
    else if(newRoot->right == NULL){
        return NULL;
    }
    else{
        newRoot = pRoot->right;
        pRoot->right = newRoot->left;
        newRoot->left = pRoot;
    
        pRoot->height = max(get_height(pRoot->left), get_height(pRoot->right)) + 1;
        newRoot->height = max(get_height(newRoot->left), get_height(newRoot->right)) + 1;
    }
    return newRoot;
}

Node* right_rotation(Node* pRoot){
    Node* newRoot = pRoot;
    if(newRoot == NULL){
        return NULL;
    }
    else if(newRoot->left == NULL){
        return NULL;
    }
    else{
        newRoot = pRoot->left;
        pRoot->left = newRoot->right;
        newRoot->right = pRoot;
        pRoot->height = max(get_height(pRoot->left), get_height(pRoot->right))+1;
        newRoot->height = max(get_height(newRoot->left), get_height(newRoot->right))+1;
    }
    return newRoot;
}

Status tree_add(TREE hTree, MY_STRING key, MY_STRING word){
    Tree* pTree = (Tree*)hTree;
    if(pTree == NULL){
        return FAILURE;
    }
    return insert(&(pTree->root), key, word);
}

Status insert(Node** pRoot, MY_STRING key, MY_STRING word){
    int balance;  
    if(*pRoot == NULL){
        *pRoot = (Node*)malloc(sizeof(Node));
        if(*pRoot == NULL){
            printf("failed to create a node!\n");
            return FAILURE;
        } 
        (*pRoot)->data = my_string_init_c_string(my_string_c_str(key));
        (*pRoot)->words = generic_vector_init_default(my_string_assignment, my_string_destroy);
        (*pRoot)->left = NULL;
        (*pRoot)->right = NULL;
        (*pRoot)->height = 1;
        generic_vector_push_back((*pRoot)->words, word);
        return SUCCESS;
    }
    else{
        if(my_string_compare((*pRoot)->data, key) < 0){
            insert(&((*pRoot)->left), key, word);
        }
        else if(my_string_compare((*pRoot)->data, key) > 0){
            insert(&((*pRoot)->right), key, word);
        }
        else if(my_string_compare((*pRoot)->data, key) == 0){
            generic_vector_push_back((*pRoot)->words, word);
        }
        else{
            return FAILURE;
        }
        (*pRoot)->height = max(get_height((*pRoot)->left), get_height((*pRoot)->right)) + 1;
        balance = get_balance(*pRoot);
        if(balance < -1 && my_string_compare((*pRoot)->right->data, word) > 0){
            *pRoot = left_rotation(*pRoot);
            return SUCCESS;
        }
        if(balance > 1 && my_string_compare((*pRoot)->left->data, word) < 0){
            *pRoot = right_rotation(*pRoot);
            return SUCCESS;
        }
        if(balance > 1 && my_string_compare((*pRoot)->left->data, word) > 0){
            (*pRoot)->left = left_rotation((*pRoot)->left);
            *pRoot = right_rotation(*pRoot);
            return SUCCESS;
        }
        if(balance < -1 && my_string_compare((*pRoot)->right->data, word) < 0){
            (*pRoot)->right = right_rotation((*pRoot)->right);
            *pRoot = left_rotation(*pRoot);
            return SUCCESS;
        }
        return SUCCESS;
     }
}

int tree_size(TREE hTree){
    Tree* pTree = (Tree*)hTree;
    if(pTree == NULL){
        return 0;
    }
    return size(pTree->root);
}


int size(Node* pRoot){
    if(pRoot == NULL){
        return 0;
    }
    return 1 + size(pRoot->left) + size(pRoot->right);
}


void tree_destroy(TREE* phRoot){
    Tree* pRoot = (Tree*)*phRoot;
    if(pRoot->root != NULL){
        destroy(pRoot->root);
        free(pRoot);
        *phRoot = NULL;
    }
}


void destroy(Node* pRoot){
    if(pRoot == NULL){
        return;
    }
    else{
        generic_vector_destroy(&(pRoot->words));
        destroy(pRoot->left);
        destroy(pRoot->right);
        my_string_destroy(&(pRoot->data));
        free(pRoot);
    }
}


GENERIC_VECTOR largest_word_group(TREE hTree){
    Tree* pMy_tree = (Tree*)hTree;
    GENERIC_VECTOR return_vector = NULL;
    GENERIC_VECTOR temp;
    int i;
    temp = find_largest(pMy_tree->root);
    return_vector = generic_vector_init_default(my_string_assignment, my_string_destroy);
    for (i = 0; i < generic_vector_get_size(temp); i++) {
        generic_vector_push_back(return_vector, generic_vector_at(temp, i));
    }
    return return_vector;
}

GENERIC_VECTOR find_largest_node(Node* pRoot){
    Vector* temp = NULL;
    int elements_in_currentNode; {
        elements_in_currentNode = generic_vector_get_size(pRoot->words);
        if (pRoot->left != NULL) {
            temp = find_largest(pRoot->left);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->words)) {
                temp = pRoot->words;
            }
        }
        if (pRoot->right != NULL) {
            temp = find_largest(pRoot->right);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->words)) {
                temp = pRoot->words;
            }
        }
        if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->words)) {
            temp = pRoot->words;
        }
    }
    my_string_insertion(pRoot->data, stdout);
    printf(" %d\n", elements_in_currentNode);
    
    return temp;
}

Boolean tree_empty(TREE hTree){
    Tree* pTree = (Tree*)hTree;
    return (Boolean)(pTree->root == NULL);
}






