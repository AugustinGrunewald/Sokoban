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


void test_move(const char *adress_original_file, const char *adress_result_file){
    //loading the differents maps used for the test
    game_map *original_map = map_loader(adress_original_file);
    game_map *result_map = map_loader(adress_result_file);

    int direction_position = strlen(adress_result_file) - 4;
    game_map *result_map_with_move_function = move(original_map, adress_result_file[direction_position]);

    printf("  | | testing the move with %s and the direction %c ... \n", adress_original_file, adress_result_file[direction_position]);

    bool test_result = comparaison_two_maps(*result_map, *result_map_with_move_function);
    assert(test_result == true);
    printf("  | | | Success \n");


    //if condition : avoid double free issues with files that got the same names, when available move
    if (comparaison_two_adresses(adress_original_file, adress_result_file) == false){
        free(result_map_with_move_function->map);
        free(result_map_with_move_function);
    }

    free(result_map->map);
    free(result_map);
    free(original_map->map);
    free(original_map);
}

int main(void){
    printf("* Starting moving tests...\n");
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