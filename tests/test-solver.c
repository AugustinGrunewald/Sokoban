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
    stats *result;
    result = solver(loaded_map);
    const char *plan = result->solution_plan;

    if (result->win == true){
        printf("  | |  WIN \n");
        printf("  | |  Wining plan: ");
        for(int i = 0; i < sizeof(plan); i++){
            printf("%c", plan[i]);
        }
        printf("\n");
        printf("\n");
    }else{
        printf("  | |  LOOSE \n");
        printf("\n");
    }

    //freeing the loaded maps and all the related stuff
    // free(loaded_map->map);
    // free(loaded_map);
    free(result);
}


int main(void){
    printf("* Starting solver tests...\n");

    printf("  |  Testing ./data/soko_dumb.in ... \n");
    building_solution("./data/soko_dumb.in");
    // building_solution("./data/soko_dumb_1.in");
    // building_solution("./data/soko_dumb_2.in");
    // building_solution("./data/soko_dumb_3.in");
    // building_solution("./data/soko1_1.in");

    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}