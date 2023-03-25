#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "linked_list_map.h"
#include "sokoban.h"
#include "loader.h"
#include "bst_map.h"


// auxiliary functions
void print_level(bst_int tree, int level) {
    for (int i = 0; i < level - 1; i++) {
        printf("   ");
    }

    if (is_empty(tree)) {
        printf("%snil\n", level == 0 ? "" : " +-");
        return;
    }

    printf("%s(%d)\n", level == 0 ? "" : " +-", tree->value);
    print_level(tree->left, level + 1);
    print_level(tree->right, level + 1);
}

int max(int a, int b){
    if (a < b){
        return b;
    }else{
        return a;
    }
}

// functions from the signature
void print_bst(bst_int tree) {
    print_level(tree, 0);
}

bst_int nil(){
     return NULL;
}

bool is_empty(bst_int tree){
    if (tree == NULL){
        return true;
    }else{
        return false;
    }
}

int value(bst_int tree){
    return tree->value;
}

int size(bst_int tree){

    if (is_empty(tree) == true){
        return 0;
    }
    else{
        if (is_empty(tree->left) == true){
        return 1 + size(tree->right);
        }
        if (is_empty(tree->right) == true){
            return 1 + size(tree->left);
        }
        else{
            return 1 + size(tree->left) + size(tree->right);
        }
    }
}

int height(bst_int tree){
    if (is_empty(tree) == true){
        return 0;
    }
    else{
        return 1 + max(height(tree->left), height(tree->right));
    }
}

bst_int left_child(bst_int tree){
    return tree->left;
}

bst_int right_child(bst_int tree){
    return tree->right;
}

bst_int retrieve(bst_int tree, int value){
    if (size(tree) == 0){
        return NULL;
    }else{
        if (value == tree->value){
            return tree;
        }
        if (value < tree->value){
            return retrieve(tree->left, value);
        }else{
            return retrieve(tree->right, value);
        }
    }
}

bst_int insert(bst_int tree, int value){
    if(tree == NULL){
        bst_node_int* new_node = (bst_node_int*)malloc(sizeof(bst_node_int));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->value = value;

        return new_node;
    }
    if(value < tree->value){
        tree->left = insert(tree->left, value);
    }else if(value > tree->value){
        tree->right = insert(tree->right, value);
    }
    return tree;
}

bst_int delete(bst_int tree, int value){
    return NULL;
}

void in_order_dfs_infix(bst_int tree){

}

void deallocate_bst(bst_int tree){

}