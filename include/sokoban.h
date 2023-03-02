#ifndef SOKOBAN_H
#define SOKOBAN_H

typedef struct game_map game_map;
typedef struct couple couple;


/**
 * @brief The structure representing the position of the player
 * 
 */
struct couple {
    /** an int representing the height*/
    int height;

    /** an int representing the width*/
    int width;
};


/**
 * @brief The structure representing the game map
 * 
 */
struct game_map {
    /** The size of the map*/
    couple map_size;

    /** The position of the player*/
    couple player_pos;

    /** The map*/
    char *map; 
};


/**
 * @brief Print the map in the console.
 * 
 * @param used_map The structure representing the map.
 */
void print_map(game_map used_map);


#endif
