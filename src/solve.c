/**
 * @file solve.c
 * 
 * @brief Program to solve a game from the command line. 
 * Example of usage: ./solve data/soko1.in 
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "gui.h"
#include "solver.h"
#include "queue_map.h"
#include "linked_list_map.h"
#include "sokoban.h"
#include "loader.h"
#include "bst_map.h"


/**
 * @brief A function to show using SDL the solving process (only playing the wining map).
 * 
 * @param result The stats structure that contains all the informations returned by the solver.
 * 
 * @param adress The adress of the map that is solved.
 */

void replay_solving_process(stats *result, const char *adress){
    //initializing the map and the main parameters associated
    game_map *current_step_map = map_loader(adress);
    game_map *next_step_map = (game_map *) malloc(sizeof(game_map));

    int height = current_step_map->map_size.height;
    int width = current_step_map->map_size.width;
    char *level = current_step_map->map;

    bool stop = false;


    // initialize GUI window
    GUI_init("Sokoban", width, height);

    // display level and waiting 30ms
    GUI_show(width, height, level);
    GUI_pause(100);

    int ind = 0;
    //main loop
    while (true){
        //to get out the loop after the last movement
        if (ind == result->plan_length){
            stop = true;
        }

        switch (result->solution_plan[ind]){
            case NORD:
                next_step_map = move(current_step_map, NORD);
                level = next_step_map->map;
                GUI_show(width, height, level);
                GUI_pause(100);
                
                *current_step_map = *next_step_map;
                break;

            case SOUTH:
                next_step_map = move(current_step_map, SOUTH);
                level = next_step_map->map;
                GUI_show(width, height, level);
                GUI_pause(100);
                
                *current_step_map = *next_step_map;
                break;

            case EAST:
                next_step_map = move(current_step_map, EAST);
                level = next_step_map->map;
                GUI_show(width, height, level);
                GUI_pause(100);
                
                *current_step_map = *next_step_map;
                break;

            case WEST:
                next_step_map = move(current_step_map, WEST);
                level = next_step_map->map;
                GUI_show(width, height, level);
                GUI_pause(100);
                
                *current_step_map = *next_step_map;
                break;
        }

        //incrementing the indice
        ind++;
        
        //quiting the while loop
        if (stop){
            break;
        }
        
        *current_step_map = *next_step_map;
    }

    GUI_close();
}



/**
 * @brief The main of this file that should solve a game. 
 *        Executing this code you will be asked if you want to solve using the BST or not and if you want to replay using SDL the winning solution.
 * 
 * @return Nothing. 
 */

int main(int argc, char *argv[]){
    //testing if the correct input has been given
    if (argc != 2) {
        fprintf(stderr, "You must provide the rigth input!\n");
        exit(EXIT_FAILURE);
    }

    //loaded the initial map
    const char *adress = argv[1];
    game_map *loaded_map = map_loader(adress);

    //asking for bst or not
    char user_answer_1[5];
    char user_answer_2[5];
    printf("\n");
    printf("Please let me know if you want to use the solver WITH or WITHOUT BST :\n");
    printf("\n");
    printf("Enter YES (if you want the BST solver) or NO (in the other case).\n");
    scanf("%s", user_answer_1);
    printf("\n");
    printf("\n");
    printf("Please let me know if you want to see a replay of the solving process :\n");
    printf("\n");
    printf("Enter YES or NO.\n");
    scanf("%s", user_answer_2);
    printf("\n");  

    //using the solver
    stats *result;
    if (strcmp(user_answer_1, "YES") == 0){
        printf("* Starting solving %s using the BST solver... \n", adress);
        result = solver_bst(loaded_map);
    }else{
        printf("* Starting solving %s using the classical solver... \n", adress);
        result = solver(loaded_map);
    }

    //showing the replay if necessary
    if (strcmp(user_answer_2, "YES") == 0 && result->win == true){
        replay_solving_process(result, adress);
    }

    if (result->win == true){
        printf("  |  WIN \n");
        printf("  |  Wining plan: %s\n", result->solution_plan);
        printf("  |  Number of explored nodes: %d \n", result->nmb_explored_nodes);
        printf("  |  Time spent by the solver: %f \n", result->time_spent);
        printf("\n");
    }else{
        printf("  |  LOOSE \n");
        printf("  |  Number of explored nodes: %d \n", result->nmb_explored_nodes);
        printf("  |  Time spent by the solver: %f \n", result->time_spent);
        printf("\n");
    }

    //freeing the result structure
    free(result->solution_plan);
    free(result);
    return 0;
}