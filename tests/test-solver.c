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

void building_solution(const char *adress){
    //loading the map
    game_map *loaded_map = map_loader(adress);

    //testing the solver
    printf("  |  Testing %s ... \n", adress);
    stats *result;
    result = solver(loaded_map);

    if (result->win == true){
        printf("  | |  WIN \n");
        printf("  | |  Wining plan: %s \n", result->solution_plan);
    }else{
        printf("  | |  LOOSE \n");
    }

    //freeing the loaded maps and all the related stuff
    free(loaded_map->map);
    free(loaded_map);
    free(result);
}


int main(void){
    printf("* Starting solver tests...\n");

    building_solution("./data/soko_dumb.in");
    building_solution("./data/soko_dumb_1.in");
    building_solution("./data/soko_dumb_2.in");
    building_solution("./data/soko_dumb_3.in");

    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}