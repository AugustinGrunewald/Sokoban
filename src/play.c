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

    //initializing the main parameters of the map
    int height = current_step_map->map_size.height;
    int width = current_step_map->map_size.width;
    char **initial_map = map_to_matrix_transcoder(current_step_map, height, width);
    bool stop = false;

    // initialize GUI window
    GUI_init("Sokoban", width, height);

    // display level
    GUI_show(width, height, initial_map);

    // main loop
    while(true) {

        switch (GUI_get_key()) {
        case SDLK_UP:
            char direction = {'N'};

            game_map *next_step_map = move(current_step_map, direction);
            char **level = map_to_matrix_transcoder(next_step_map, height, width);
            GUI_show(width, height, level);

            *current_step_map = *next_step_map;
            break;

        case SDLK_DOWN:
            char direction = {'S'};

            game_map *next_step_map = move(current_step_map, direction);
            char **level = map_to_matrix_transcoder(next_step_map, height, width);
            GUI_show(width, height, level);

            *current_step_map = *next_step_map;
            break;

        case SDLK_LEFT:
            char direction = {'W'};

            game_map *next_step_map = move(current_step_map, direction);
            char **level = map_to_matrix_transcoder(next_step_map, height, width);
            GUI_show(width, height, level);

            *current_step_map = *next_step_map;
            break;

        case SDLK_RIGHT:
            char direction = {'E'};

            game_map *next_step_map = move(current_step_map, direction);
            char **level = map_to_matrix_transcoder(next_step_map, height, width);
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
    }

    GUI_close();

    return EXIT_SUCCESS;
}