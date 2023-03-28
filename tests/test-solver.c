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

//trying to make a function using sdl to show the solving process

// #include <SDL2/SDL.h>
// #include "gui.h"

// void replay_solver(const char *adress){
//     game_map *current_step_map = map_loader(adress);
//     int height = current_step_map->map_size.height;
//     int width = current_step_map->map_size.width;
//     stats *result;
//     result = solver(current_step_map);


//     // game_map *next_step_map = (game_map *) malloc(sizeof(game_map));
//     char *direction_string = result->solution_plan;
//     int length_direction_string = result->plan_length;
//     // char copy_direction_string[length_direction_string];
//     // sprintf(copy_direction_string, direction_string);

//     char *level = current_step_map->map;

//     // initialize GUI window
//     GUI_init("Sokoban", width, height);

//     // display first map
//     GUI_show(width, height, level); 

//     printf("direc %c\n", result->solution_plan[1]);
//     game_map *next_step_map = move(current_step_map, direction_string[0]);
//     current_step_map = next_step_map;
//     level = current_step_map->map;

//     //display map after first movement
//     GUI_show(width, height, level); 

//     for(int direction_step = 1; direction_step < length_direction_string; direction_step++){
//         char current_direction = direction_string[direction_step];

//         game_map *next_step_map_bis = move(current_step_map, current_direction);
//         level = next_step_map_bis->map;

//         // free(current_step_map->map);
//         // free(current_step_map);

//         current_step_map = next_step_map_bis;  

//         //display level
//         GUI_show(width, height, level); 
//     }

//     // closing the window
//     GUI_close();

//     printf("\n");
//     printf("THIS COMPUTER IS TOO STRONG ...\n");
//     printf("HE ALWAYS WIN :o \n");
//     printf("\n");
// }



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