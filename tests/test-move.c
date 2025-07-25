/**
 * @file test-move.c
 * 
 * @brief Tests to check if the move functions are working
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "loader.h"
#include "sokoban.h"


/**
 * @brief A function to applied a movement to a map and test if the correct map is obtained. 
 * 
 * @param adress_original_file The map on which you apply the movement (character contained in the adress of the second map). 
 * 
 * @param adress_result_file The correct map that you should get after using the move function.
 */

void test_move(const char *adress_original_file, const char *adress_result_file){
    //loading the differents maps used for the test
    game_map *original_map = map_loader(adress_original_file);
    game_map *result_map = map_loader(adress_result_file);

    //int to find the character giving the direction in the string adress and using the move funtcion to build the next map
    int direction_position = strlen(adress_result_file) - 4;
    game_map *result_map_with_move_function = move(original_map, adress_result_file[direction_position]);

    printf("  | | Testing the move with %s and the direction %c ... \n", adress_original_file, adress_result_file[direction_position]);

    bool test_result = comparaison_two_maps(*result_map, *result_map_with_move_function);
    assert(test_result == true);
    printf("  | | | Success \n");

    //freeing the allocations
    free(result_map_with_move_function->map);
    free(result_map_with_move_function);
    free(result_map->map);
    free(result_map);
    free(original_map->map);
    free(original_map);
}



/**
 * @brief The main of this file that test the move function. It tests all the map mentionned in the Project pdf explanation.
 * 
 * @return Nothing. 
 */

int main(void){
    printf("* Starting moving tests ...\n");
    printf("\n");

    //simple player movements
    printf("  |  Starting tests : simple player movements ... \n");
    test_move("./data/soko_move_1.in", "./data/soko_move_1_N.in");
    test_move("./data/soko_move_1.in", "./data/soko_move_1_S.in");
    test_move("./data/soko_move_1.in", "./data/soko_move_1_E.in");
    test_move("./data/soko_move_1.in", "./data/soko_move_1_W.in");
    printf("\n");

    //player movement on dest.
    printf("  |  Starting tests : player movement on dest. ... \n");
    test_move("./data/soko_move_2.in", "./data/soko_move_2_N.in");
    test_move("./data/soko_move_2.in", "./data/soko_move_2_S.in");
    test_move("./data/soko_move_2.in", "./data/soko_move_2_E.in");
    test_move("./data/soko_move_2.in", "./data/soko_move_2_W.in");
    printf("\n");

    //move box to east
    printf("  |  Starting tests : move box to east ... \n");  
    test_move("./data/soko_move_3_1.in", "./data/soko_move_3_1_E.in");
    test_move("./data/soko_move_3_2.in", "./data/soko_move_3_2_E.in");
    test_move("./data/soko_move_3_3.in", "./data/soko_move_3_3_E.in");
    test_move("./data/soko_move_3_4.in", "./data/soko_move_3_4_E.in");
    printf("\n");

    //move box to west
    printf("  |  Starting tests : move box to west ... \n");  
    test_move("./data/soko_move_4_1.in", "./data/soko_move_4_1_W.in");
    test_move("./data/soko_move_4_2.in", "./data/soko_move_4_2_W.in");
    test_move("./data/soko_move_4_3.in", "./data/soko_move_4_3_W.in");
    test_move("./data/soko_move_4_4.in", "./data/soko_move_4_4_W.in");
    printf("\n");

    //move box to north
    printf("  |  Starting tests : move box to north ... \n");  
    test_move("./data/soko_move_5_1.in", "./data/soko_move_5_1_N.in");
    test_move("./data/soko_move_5_2.in", "./data/soko_move_5_2_N.in");
    test_move("./data/soko_move_5_3.in", "./data/soko_move_5_3_N.in");
    test_move("./data/soko_move_5_4.in", "./data/soko_move_5_4_N.in");
    printf("\n");

    //move box to south
    printf("  |  Starting tests : move box to south ... \n");  
    test_move("./data/soko_move_6_1.in", "./data/soko_move_6_1_S.in");
    test_move("./data/soko_move_6_2.in", "./data/soko_move_6_2_S.in");
    test_move("./data/soko_move_6_3.in", "./data/soko_move_6_3_S.in");
    test_move("./data/soko_move_6_4.in", "./data/soko_move_6_4_S.in");
    printf("\n");

    //does nothing
    printf("  |  Starting tests : does nothing ... \n");  
    test_move("./data/soko_move_W_E.in", "./data/soko_move_W_E.in");
    test_move("./data/soko_move_W_W.in", "./data/soko_move_W_W.in");
    test_move("./data/soko_move_W_N.in", "./data/soko_move_W_N.in");
    test_move("./data/soko_move_W_S.in", "./data/soko_move_W_S.in");
   
    test_move("./data/soko_move_B_W_E.in", "./data/soko_move_B_W_E.in");
    test_move("./data/soko_move_B_W_W.in", "./data/soko_move_B_W_W.in");
    test_move("./data/soko_move_B_W_N.in", "./data/soko_move_B_W_N.in");
    test_move("./data/soko_move_B_W_S.in", "./data/soko_move_B_W_S.in"); 
    
    test_move("./data/soko_move_B_B_E.in", "./data/soko_move_B_B_E.in");
    test_move("./data/soko_move_B_B_W.in", "./data/soko_move_B_B_W.in");
    test_move("./data/soko_move_B_B_N.in", "./data/soko_move_B_B_N.in");
    test_move("./data/soko_move_B_B_S.in", "./data/soko_move_B_B_S.in");
    printf("\n");

    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}