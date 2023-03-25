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

#include "solver.h"
#include "queue_map.h"
#include "linked_list_map.h"
#include "sokoban.h"
#include "loader.h"

int main(int argc, char *argv[]){
    //testing if the correct input has been given
    if (argc != 2) {
        fprintf(stderr, "You must provide the rigth input!\n");
        exit(EXIT_FAILURE);
    }

    //loaded the initial map
    const char *adress = argv[1];
    game_map *loaded_map = map_loader(adress);

    printf("* Starting solving %s ... \n", adress);

    //using the solver
    stats *result;
    result = solver(loaded_map);

    // printf("deefer %c\n", plan[0]);
    if (result->win == true){
        printf("  |  WIN \n");
        printf("  |  Wining plan: %s\n", result->solution_plan);
        // for(int i = 0; i < sizeof(plan); i++){
        //     printf("%c", plan[i]);
        // }
        // printf("\n");
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
    free(result);
    return 0;
}