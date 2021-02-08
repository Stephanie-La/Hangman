#ifndef TREE_H
#define TREE_H

#include "my_string.h"
#include "generic_vector.h"

typedef void* TREE;

TREE tree_init_default(void);

int tree_depth(TREE hTree);

Status add_tree(TREE hTree, MY_STRING key, MY_STRING word);

int tree_size(TREE hTree);

GENERIC_VECTOR largest_word_group(TREE hTree);

Boolean tree_empty(TREE hTree);

void tree_destroy(TREE* phRoot);


#endif
