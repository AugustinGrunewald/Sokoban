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
#include "bst_map.h"


/**
 * @brief A function that build the solver solution and compares it with the given solution (see Project pdf)
 * 
 * @param adress The adress of the map you want to solve.
 * 
 * @param plan The plan that correspond to the official plan solution that should be compared with the plan building by the solver.
 */

void building_solution(const char *adress, char *plan){
    //loading the map
    game_map *loaded_map = map_loader(adress);
    game_map *loaded_map_bst = map_loader(adress);

    //testing the solver
    stats *result;
    stats *result_bst;
    result = solver(loaded_map);
    result_bst = solver_bst(loaded_map_bst);

    if (result_bst->win == true){
        printf("  | |  WIN \n");
        printf("  | |  Wining plan: %s\n", result->solution_plan);
        // checking if the solution plan is the one given in test-solver.csv
        assert(strncmp(plan, result->solution_plan, result->plan_length) == 0);
        printf("  | |  Plan corresponding to the given one ...  YES \n");
        printf("  | |  Number of explored nodes: %d \n", result->nmb_explored_nodes);
        printf("  | |  Time spent by the solver: %f \n", result->time_spent);
        printf("  | |  Time spent by the bst solver: %f \n", result_bst->time_spent);
        printf("\n");
    }else{
        printf("  | |  LOOSE \n");
        printf("  | |  Number of explored nodes: %d \n", result->nmb_explored_nodes);
        printf("  | |  Time spent by the solver: %f \n", result->time_spent);
        printf("  | |  Time spent by the bst solver: %f \n", result_bst->time_spent);
        printf("\n");
    }

    //freeing the result structure
    free(result->solution_plan);
    free(result);
    free(result_bst->solution_plan);
    free(result_bst);
}


/**
 * @brief The main of this file that solves different maps.
 * 
 * @return Nothing. 
 */

int main(void){
    printf("* Starting solver tests...\n");

    printf("  |  Testing ./data/soko_dumber.in ... \n");
    building_solution("./data/soko_dumber.in", "EE");

    printf("  |  Testing ./data/soko_dumb.in ... \n");
    building_solution("./data/soko_dumb.in", "SSSEENN");

    printf("  |  Testing ./data/soko_dumb_imp.in ... \n");
    building_solution("./data/soko_dumb_imp.in", "0");  

    printf("  |  Testing ./data/soko81.in ... \n");
    building_solution("./data/soko81.in", "ENNENSSNWWNENNEESWNWSSWSEWWWNEE");

    printf("  |  Testing ./data/soko99.in ... \n");
    building_solution("./data/soko99.in", "WWNNNENEESSWWNEWWSWSSEEENNWNNEESWNWS");

    printf("  |  Testing ./data/soko1.in ... \n");
    building_solution("./data/soko1.in", "NNWWSWWNEESWSWWWNNEESSESSWWNSEENNNENENESSSWSWENEESWWNENNWWSWWNEWWWSSESSEENNWNENEENESSSWSWENENNWWWWWWSSESSEENNWESEENEESWWWENENNWWWWSSENWNEEENESSNWWWWWWSSESSEENEEEENWSWWWNNWNEEENESSSESWW");

    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}