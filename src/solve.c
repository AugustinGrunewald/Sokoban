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
#include "bst_map.h"


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
    char user_answer[5];
    printf("\n");
    printf("Please let me know if you want to use the solver WITH or WITHOUT BST :\n");
    printf("\n");
    printf("Enter YES (if you want the BST solver) or NO (in the other case).\n");
    scanf("%s", user_answer);
    printf("\n");

    //using the solver
    stats *result;
    if (strcmp(user_answer, "YES") == 0){
        printf("* Starting solving %s using the BST solver... \n", adress);
        result = solver_bst(loaded_map);
    }else{
        printf("* Starting solving %s using the classical solver... \n", adress);
        result = solver(loaded_map);
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