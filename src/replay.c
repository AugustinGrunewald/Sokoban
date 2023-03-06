/**
 * @file replay.c
 * 
 * @brief Program to replay a game from the command line. 
 * Example of usage: ./replay data/soko1.in 7 "NNNEEESSS"
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loader.h"
#include "sokoban.h"

int main(int argc, char *argv[]){
    //testing if the correct input has been given
    if (argc != 4) {
        fprintf(stderr, "You must provide the rigth input!\n");
        exit(EXIT_FAILURE);
    }

    //loaded the initial map, the plan and the number of movements wanted
    const char *loaded_adress = argv[1];
    const char *string_plan_length = argv[2];
    char *plan = argv[3];

    //transcoding the string representing the plan length into an int
    int plan_length = atoi(string_plan_length);
    
    //executing the replay
    game_map *original_map = map_loader(loaded_adress);
    game_map *result_map = replay(original_map, plan_length, plan);

    printf("* Starting replay with %s, a plan length of %d and a plan of %s ... \n", loaded_adress, plan_length, plan);
 
    //print the final map
    print_map(*result_map);

    //freeing the function
    free(original_map->map);
    free(original_map);

    return 0;
}