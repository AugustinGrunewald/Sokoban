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
        printf("  | |  Wining plan: %s", plan);
        // for(int i = 0; i < sizeof(plan); i++){
        //     printf("%c", plan[i]);
        // }
        // printf("\n");
        printf("  | |  Number of explored nodes: %d \n", result->nmb_explored_nodes);
        printf("  | |  Time spent by the solver: %f \n", result->time_spent);
        printf("\n");

        replay_solver(loaded_map, result->plan_length, result->solution_plan);
    }else{
        printf("  | |  LOOSE \n");
        printf("  | |  Number of explored nodes: %d \n", result->nmb_explored_nodes);
        printf("  | |  Time spent by the solver: %f \n", result->time_spent);
        printf("\n");
    }

    //freeing the result structure
    free(result);
}


int main(void){
    printf("* Starting solver tests...\n");

    printf("  |  Testing ./data/soko_dumb.in ... \n");
    building_solution("./data/soko_dumb.in");

    // printf("  |  Testing ./data/soko_dumb_1.in ... \n");
    // building_solution("./data/soko_dumb_1.in");  

    // printf("  |  Testing ./data/soko_dumb_2.in ... \n");
    // building_solution("./data/soko_dumb_2.in");

    // printf("  |  Testing ./data/soko_dumb_3.in ... \n");
    // building_solution("./data/soko_dumb_3.in");

    // printf("  |  Testing ./data/soko1_1.in ... \n");
    // building_solution("./data/soko1_1.in");

    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}