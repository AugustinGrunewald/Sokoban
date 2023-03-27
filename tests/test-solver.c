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

// #include <SDL2/SDL.h>

// #include "gui.h"
#include "solver.h"
#include "queue_map.h"
#include "linked_list_map.h"
#include "sokoban.h"
#include "loader.h"



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



void building_solution(const char *adress){
    //loading the map
    game_map *loaded_map = map_loader(adress);

    //testing the solver
    stats *result;
    result = solver(loaded_map);

    // printf("deefer %c\n", plan[0]);
    if (result->win == true){
        printf("  | |  WIN \n");
        // printf("  | |  Wining plan: %s\n", result->solution_plan);
        printf("  | |  Wining plan: ");
        for(int i = 0; i < result->plan_length; i++){
            printf("%c", result->solution_plan[i]);
        }
        printf("\n");
        printf("  | |  Number of explored nodes: %d \n", result->nmb_explored_nodes);
        printf("  | |  Time spent by the solver: %f \n", result->time_spent);
        printf("\n");
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
    // replay_solver("./data/soko_dumb.in");

    // printf("  |  Testing ./data/soko_dumb_1.in ... \n");
    // building_solution("./data/soko_dumb_1.in");  

    // printf("  |  Testing ./data/soko_dumb_2.in ... \n");
    // building_solution("./data/soko_dumb_2.in");

    // printf("  |  Testing ./data/soko81.in ... \n");
    // building_solution("./data/soko81.in");

    // printf("  |  Testing ./data/soko1_1.in ... \n");
    // building_solution("./data/soko1_1.in");

    printf("  +-> OK!\n");
    printf("\n");

    return 0;
}