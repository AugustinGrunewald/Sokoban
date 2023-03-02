#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loader.h"
#include "sokoban.h"


game_map *map_loader(const char *adress) {
    // initializing of the dynamically allocated structure representing the map  
    game_map *p_loaded_map = (game_map *) malloc(sizeof(game_map));
    // initializing of the first part of the dynamically allocated structure representing the map  
    //couple *map_size = (couple *) malloc(sizeof(couple));

    // open file. The filename is the first argument on the command
    // line, hence stored in argv[1]
    FILE *p_file = NULL;

    p_file = fopen(adress, "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", adress);
        exit(EXIT_FAILURE);
    }

    // read dimensions on first line and adding them in the structure
    int width         = 0;
    int height        = 0;
    int fscanf_result = 0;

    fscanf_result = fscanf(p_file, "%d %d\n", &width, &height);

    if (fscanf_result != 2) {
        fprintf(stderr, "First line is not syntactically correct!\n");
        exit(EXIT_FAILURE);
    }

    p_loaded_map->map_size.height = height;
    p_loaded_map->map_size.width = width;
    
    // reading of the rest of the map, and research of the player position

    // initializing of a pointer to a copy of the character of the map
    char *p_char_memory = (char *) malloc(height*width*sizeof(char)); 
    int marker = 0;
    char player[] = {'@'};

    // read following lines
    // line_buffer contains a line and is a correct string
    // width + 2 is needed to get the carriage return symbol
    char line_buffer[width + 2];

    for (int ind_line = 0; ind_line < height; ind_line++) {
        fgets(line_buffer, width + 2, p_file);

        for (int ind_row = 0; ind_row < width; ind_row++) {
            p_char_memory[ind_line * width + ind_row] = line_buffer[ind_row];
            
            if (marker == 0) {
                if (p_char_memory[ind_line * width + ind_row] == player[0]){
                    marker = 1;
                    p_loaded_map->player_pos.width = ind_row + 1;
                    p_loaded_map->player_pos.height = ind_line + 1;
                }
            }
        }
    }

    p_loaded_map->map = p_char_memory;

    fclose(p_file);

    return p_loaded_map;
}
