#ifndef BST_MAP_H
#define BST_MAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "sokoban.h"
#include "loader.h"
#include "linked_list_map.h"
#include "queue_map.h"



/**
 * @brief An alias to the structure representing the nodes of
 *        the tree.
 */
typedef struct bst_node_map bst_node_map;


/**
 * @brief A binary tree is just a pointer to the root node
 *        of the tree.
 */
typedef bst_node_map *bst_map;


/**
 * @brief The structure representing the nodes of the BST.
 */
struct bst_node_map {
    /** The left subtree of the node */
    bst_map left;

    /** The map */
    game_map *p_map;

    /** The right subtree of the node */
    bst_map right;
};


/**
 * @brief Return the maximum of the couple a,b.
 * 
 * @param a an int.
 * 
 * @param b an other int.
 *  
 * @return the maximum of a and b. 
 */
int max(int a, int b);


/**
 * @brief Create a nil binary search tree.
 *
 * @return an empty binary search tree
 */
bst_map nil_tree();


/**
 * @brief Is the binary search tree empty?
 *
 * @param tree  a the tree you want to check the emptiness
 *
 * @return `true` if `tree` is empty, `false` else
 */
bool is_empty_tree(bst_map tree);


/**
 * @brief Gives true or false if the tree has the wanted map or not.
 *
 * @param tree   a pointer to the tree
 * @param value  the value of the root of the subtree to search
 *
 * @return true if the map is in the tree.
 * @return false if not.
 */
bool searching_bst(bst_map tree, game_map *p_map);


/**
 * @brief Insert a value in the tree.
 *
 * @param tree   the tree in which the value is to be inserted
 * @param value  the value to be inserted
 *
 * @return a tree in which there is a node containing `value`.
 *         This node is correctly placed with respect to the
 *         binary search tree property. If the node was already in
 *         the tree, no new node is inserted and `tree` is returned.
 */
bst_map insert_tree(bst_map tree, game_map *p_map);


/**
 * @brief Deallocate a binary search tree.
 *
 * @param tree  the tree to be deallocated
 *
 * @post After the call, all memory regions used for the nodes
 *       are deallocated
 */
void deallocate_tree(bst_map tree);

#endif