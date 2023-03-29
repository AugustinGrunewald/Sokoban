#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "linked_list_map.h"
#include "sokoban.h"
#include "loader.h"
#include "bst_map.h"


int max(int a, int b){
    if (a < b){
        return b;
    }else{
        return a;
    }
}

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

bool searching_bst(bst_map tree, game_map *p_map){
    bool result = false;
    if (is_empty_tree(tree) == true){
        return result;
    }else{
        int map_length = p_map->map_size.height * p_map->map_size.width;
        if (p_map->player_pos.height == tree->p_map->player_pos.height && p_map->player_pos.width == tree->p_map->player_pos.width){
            if (strncmp(p_map->map, tree->p_map->map, map_length) == 0){
                result = true;
                return result;
            }
        }
        if (strncmp(p_map->map, tree->p_map->map, map_length) < 0){
            return searching_bst(tree->left, p_map);
        }else{
            return searching_bst(tree->right, p_map);
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

void deallocate_tree(bst_map tree){
    if (is_empty_tree(tree) == false){
        deallocate_tree(tree->left);
        deallocate_tree(tree->right);
        free(tree);
    }
}