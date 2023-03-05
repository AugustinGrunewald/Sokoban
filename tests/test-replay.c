/**
 * @file test-replay.c
 * 
 * @brief Test if the replays works.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sokoban.h"
#include "loader.h"


int main(void){
    printf("* Starting replay tests...\n");
    printf("\n");

    //simple player movements
    printf("  |  Starting tests : simple player movements ... \n");
    test_move("./data/soko_move_1.in", "./data/soko_move_1_N.in");
    test_move("./data/soko_move_1.in", "./data/soko_move_1_S.in");
    test_move("./data/soko_move_1.in", "./data/soko_move_1_E.in");
    test_move("./data/soko_move_1.in", "./data/soko_move_1_W.in");
    printf("\n");

    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}