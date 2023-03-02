#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loader.h"
#include "sokoban.h"


struct game_map *map_loader(const char *adress) {
    // initializing of the dynamically allocated structure representing the map
    struct game_map *loaded_map = (struct game_map *) malloc(sizeof(struct game_map));
    
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

    loaded_map->height = height;
    loaded_map->width = width;


    char char_memory[height * width + 2]; 
    // read following lines
    // line_buffer contains a line and is a correct string
    // width + 2 is needed to get the carriage return symbol
    char line_buffer[width + 2];

    for (int i = 0; i < height; i++) {
        fgets(line_buffer, width + 2, p_file);

        for (int j = 0; j < width; j++) {
            char_memory[i * width + j] = line_buffer[j];
        }
    }

    loaded_map->map = char_memory;

    fclose(p_file);

    return loaded_map;
}

// int main() {
//     return 0;
// }