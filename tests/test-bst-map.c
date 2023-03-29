/**
 * @file test-bst-map.c
 *
 * @brief Tests to check if the main function for the bst are working. 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <assert.h>


#include "sokoban.h"
#include "loader.h"
#include "bst_map.h"


/**
 * @brief A function that should test the different functions related to the bst (insert, nil, deallocate, ...).
 * 
 * @param adress_1 Adress number 1.
 * 
 * @param adress_2 Adress number 2.
 * 
 * @param adress_3 Adress number 3.
 * 
 * @param adress_4 Adress number 4.
 * 
 * @param adress_5 Adress number 5.
 */

void building_test_bst_map (const char *adress_1, const char *adress_2, const char *adress_3, const char *adress_4, const char *adress_5){
    //loading the different maps
    game_map *loaded_map_1 = map_loader(adress_1);
    game_map *loaded_map_2 = map_loader(adress_2);
    game_map *loaded_map_3 = map_loader(adress_3);
    game_map *loaded_map_4 = map_loader(adress_4);
    game_map *loaded_map_5 = map_loader(adress_5);

    //testing the nil function
    bst_map tree = nil_tree();
    assert(is_empty_tree(tree) == true);
    printf("  |  Creating an empty tree ... \n");
    printf("  | |  Success \n");
    printf("\n");

    //adding the maps in the tree and checking if the insert function works
    printf("  |  Adding the five maps in the tree and checking if they're in it ... \n");
    tree = insert_tree(tree, loaded_map_1);
    tree = insert_tree(tree, loaded_map_2);
    tree = insert_tree(tree, loaded_map_3);
    tree = insert_tree(tree, loaded_map_4);
    tree = insert_tree(tree, loaded_map_5);

    //checking if the search function works well
    printf("  | |  Searching map 1  ... \n");
    bool searching_result_1 = searching_bst(tree, loaded_map_1);
    assert(searching_result_1 == true);
    printf("  | |  Map 1 ... Success \n");

    printf("  | |  Searching map 2  ... \n");
    bool searching_result_2 = searching_bst(tree, loaded_map_2);
    assert(searching_result_2 == true);
    printf("  | |  Map 2 ... Success \n");

    printf("  | |  Searching map 3  ... \n");
    bool searching_result_3 = searching_bst(tree, loaded_map_3);
    assert(searching_result_3 == true);
    printf("  | |  Map 3 ... Success \n");

    printf("  | |  Searching map 4  ... \n");
    bool searching_result_4 = searching_bst(tree, loaded_map_4);
    assert(searching_result_4 == true);
    printf("  | |  Map 4 ... Success \n");

    printf("  | |  Searching map 5  ... \n");
    bool searching_result_5 = searching_bst(tree, loaded_map_5);
    assert(searching_result_5 == true);
    printf("  | |  Map 5 ... Success \n");

    printf("\n");

    //dealocating the tree
    deallocate_tree(tree);
    printf("  |  Deallocating the tree ... \n");
    printf("  | |  Success \n");
    printf("\n");

    // freeing the loaded maps
    free(loaded_map_1->map);
    free(loaded_map_1);
    free(loaded_map_2->map);
    free(loaded_map_2);
    free(loaded_map_3->map);
    free(loaded_map_3);
    free(loaded_map_4->map);
    free(loaded_map_4);
    free(loaded_map_5->map);
    free(loaded_map_5);
}



/**
 * @brief The main of this file that should test if the bst functions are working.
 * 
 * @return Nothing. 
 */

int main(void){
    printf("* Starting BST tests...\n");

    //testing the BST on several points with different maps
    building_test_bst_map("./data/soko_move_1.in", "./data/soko_move_1_N.in", "./data/soko_move_1_S.in", "./data/soko_move_1_E.in", "./data/soko_move_1_W.in");

    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}