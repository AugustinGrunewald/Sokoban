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
    // testing if the correct input has been given
    if (argc > 3) {
        fprintf(stderr, "You must provide the rigth input!\n");
        exit(EXIT_FAILURE);
    }

    //loaded the initial map, the plan and the number of movements wanted
    const char *loaded_adress = argv[1];
    char *string_representing_length = argv[2];
    char *plan = argv[3];

    printf("* Starting replay with ... \n");

    //print the final map

    return 0;
}