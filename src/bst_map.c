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
// void print_level(bst_int tree, int level) {
//     for (int i = 0; i < level - 1; i++) {
//         printf("   ");
//     }

//     if (is_empty(tree)) {
//         printf("%snil\n", level == 0 ? "" : " +-");
//         return;
//     }

//     printf("%s(%d)\n", level == 0 ? "" : " +-", tree->value);
//     print_level(tree->left, level + 1);
//     print_level(tree->right, level + 1);
// }

int max(int a, int b){
    if (a < b){
        return b;
    }else{
        return a;
    }
}

// functions from the signature

// void print_bst(bst_map tree) {
//     print_level(tree, 0);
// }

bst_map nil_tree(){
     return NULL;
}

bool is_empty_tree(bst_map tree){
    if (tree == NULL){
        return true;
    }else{
        return false;
    }
}

game_map *value(bst_map tree){
    return tree->p_map;
}

int size_tree(bst_map tree){

    if (is_empty_tree(tree) == true){
        return 0;
    }
    else{
        if (is_empty_tree(tree->left) == true){
        return 1 + size_tree(tree->right);
        }
        if (is_empty_tree(tree->right) == true){
            return 1 + size_tree(tree->left);
        }
        else{
            return 1 + size_tree(tree->left) + size_tree(tree->right);
        }
    }
}

int height_tree(bst_map tree){
    if (is_empty_tree(tree) == true){
        return 0;
    }
    else{
        return 1 + max(height_tree(tree->left), height_tree(tree->right));
    }
}

bst_map left_child(bst_map tree){
    return tree->left;
}

bst_map right_child(bst_map tree){
    return tree->right;
}

bst_map retrieve(bst_map tree, game_map *p_map){
    if (size_tree(tree) == 0){
        return NULL;
    }else{
        int map_length = p_map->map_size.height * p_map->map_size.width;
        if (strncmp(p_map->map, tree->p_map->map, map_length) == 0){
            return tree;
        }
        if (strncmp(p_map->map, tree->p_map->map, map_length) < 0){
            return retrieve(tree->left, p_map);
        }else{
            return retrieve(tree->right, p_map);
        }
    }
}

bool searching_bst(bst_map tree, game_map *p_map){
    if (size_tree(tree) == 0){
        return false;
    }else{
        int map_length = p_map->map_size.height * p_map->map_size.width;
        if (strncmp(p_map->map, tree->p_map->map, map_length) == 0){
            return true;
        }
        if (strncmp(p_map->map, tree->p_map->map, map_length) < 0){
            return retrieve(tree->left, p_map);
        }else{
            return retrieve(tree->right, p_map);
        }
    }
}

bst_map insert_tree(bst_map tree, game_map *p_map){
    int map_length = p_map->map_size.height * p_map->map_size.width;
    if(tree == NULL){
        bst_node_map* new_node = (bst_node_map*)malloc(sizeof(bst_node_map));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->p_map = p_map;

        return new_node;
    }
    if(strncmp(p_map->map, tree->p_map->map, map_length) < 0){
        tree->left = insert_tree(tree->left, p_map);
    }else if(strncmp(p_map->map, tree->p_map->map, map_length) > 0){
        tree->right = insert_tree(tree->right, p_map);
    }
    return tree;
}

bst_map delete_tree(bst_map tree, game_map *p_map){
    return nil_tree();
}

void in_order_dfs_infix(bst_map tree){

}

void deallocate_tree(bst_map tree){

}