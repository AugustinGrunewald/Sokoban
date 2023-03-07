/**
 * @file play.c
 *
 * @brief Program to interactively play Sokoban
 * 
 * Example of usage: ./play data/soko1.in 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#include "gui.h"
#include "loader.h"
#include "sokoban.h"

int main(int argc, char *argv[]) {
    //testing if the correct input has been given
    if (argc != 2) {
        fprintf(stderr, "You must provide the rigth input (filename)!\n");
        exit(EXIT_FAILURE);
    }

    //loading the map
    const char *loaded_adress = argv[1];
    game_map *current_step_map = map_loader(loaded_adress);
    game_map *next_step_map = (game_map *) malloc(sizeof(game_map));

    //initializing the main parameters of the map
    int height = current_step_map->map_size.height;
    int width = current_step_map->map_size.width;
    char *level = current_step_map->map;
    bool stop = false;

    // initialize GUI window
    GUI_init("Sokoban", width, height);

    // display level
    GUI_show(width, height, level);

    char available_direction[] = "NSWE";

    // main loop
    while(true) {

        switch (GUI_get_key()) {
        case SDLK_UP:
            
            next_step_map = move(current_step_map, available_direction[0]);
            level = next_step_map->map;
            GUI_show(width, height, level);

            break;

        case SDLK_DOWN:

            next_step_map = move(current_step_map, available_direction[1]);
            level = next_step_map->map;
            GUI_show(width, height, level);

            *current_step_map = *next_step_map;
            break;

        case SDLK_LEFT:

            next_step_map = move(current_step_map, available_direction[2]);
            level = next_step_map->map;
            GUI_show(width, height, level);

            *current_step_map = *next_step_map;
            break;

        case SDLK_RIGHT:

            next_step_map = move(current_step_map, available_direction[3]);
            level = next_step_map->map;
            GUI_show(width, height, level);

            
            *current_step_map = *next_step_map;
            break;

        case 'q':
            stop = true;
            break;

        case -1:
            stop = true;
            break;
        }

        if (stop) {
            break;
        }

        *current_step_map = *next_step_map;

    }

    GUI_close();

    return EXIT_SUCCESS;
}