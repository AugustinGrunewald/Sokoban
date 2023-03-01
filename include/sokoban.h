#ifndef SOKOBAN_H
#define SOKOBAN_H

/**
 * @brief The structure representing the position of the player
 * 
 */
struct coord {
    /** the ordinate of the point (height on the map)*/
    int coord_height;

    /** the abscissa of the point (width on the map)*/
    int coord_width;
};


/**
 * @brief The structure representing the game map
 * 
 */
struct game_map {
    /** The height of the map*/
    int height;
    /** The width of the map*/
    int width;

    /** The position of the player*/
    struct coord player_pos;

    /** The map*/
    char *map; 
};


/**
 * @brief Print the map in the console.
 * 
 * @param used_map The structure representing the map.
 */
void print_map(struct game_map used_map);


#endif
