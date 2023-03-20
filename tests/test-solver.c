/**
 * @file test-solver.c
 *
 * @brief Tests to check if the solver is working.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "solver.h"
#include "queue_map.h"
#include "linked_list_map.h"
#include "sokoban.h"
#include "loader.h"

int main(void){
    printf("* Starting solver tests...\n");

    const char adress[] = "./data/soko_dumb_1.in";

    //loading a map
    game_map *loaded_map = map_loader(adress);
    stats *result;

    //testing the solver
    printf("  |  Testing ./data/soko_dumb_1.in ... \n");
    result = solver(loaded_map);

    if (result->win == true){
        printf("  | |  WIN \n");
    }else{
        printf("  | |  LOOSE \n");
    }

    printf("  +-> OK!\n");
    printf("\n");

    //freeing the loaded maps and all the related stuff
    free(loaded_map->map);
    free(loaded_map);

    return 0;
}