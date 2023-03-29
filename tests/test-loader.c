/**
 * @file test-loader.c
 * 
 * @brief Tests to check if the loader is working
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "loader.h"
#include "sokoban.h"

void testing_loader(const char *adress) {
    printf("  | Testing the loader with %s ...  \n", adress);

    game_map *loaded_map = map_loader(adress);
    print_map(*loaded_map);
    free(loaded_map->map);
    free(loaded_map);

    printf("OK!\n");
    printf("\n");
}

int main(void){
    printf("* Starting loader tests...\n");

    // testing the loader on several examples
    testing_loader("./data/soko1.in");
    testing_loader("./data/soko_dumb_1.in");
    testing_loader("./data/soko_move_6_4.in");

    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}