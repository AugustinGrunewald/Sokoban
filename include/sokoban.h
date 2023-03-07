#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <stdbool.h>

typedef struct game_map game_map;
typedef struct couple couple;
typedef struct double_couple double_couple;
typedef struct move_tool move_tool;


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


struct double_couple {
    /** a couple representing the first available movement*/
    couple first_level;

    /** a couple representing the second available movement*/
    couple second_level;
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


struct move_tool {
    /** A boolean showing if the movement is possible*/
    bool movement_possible;

    /** A map*/
    char *map;
};


/**
 * @brief Print the map in the console.
 * 
 * @param used_map The structure representing the map.
 */
void print_map(game_map used_map);


/**
 * @brief Moving the player on the map.
 * 
 * @param p_initial_map A pointer to the structure representing the map.
 * 
 * @param direction The direction of the wanted movement (N, S, E, W). 
 * 
 * @return game_map* 
 */
game_map *move(game_map *p_initial_map, char direction);


/**
 * @brief Testing if a movement is possible.
 * 
 * @param p_initial_map A pointer to the structure representing the map. 
 * 
 * @param direction The direction of the wanted movement (N, S, E, W).
 * 
 * @return move_tool
 */
move_tool *valid_movement(game_map *p_initial_map, char direction);


/**
 * @brief Tool to associate a height and a width to the given direction.  
 * 
 * @param direction_associated_int direction (N-0, S-1, E-2, W-3).
 * 
 * @return double_couple 
 */
double_couple tool_direction(int direction_associated_int);


/**
 * @brief Testing if two maps are the same.
 * 
 * @param first_map The first map.
 * 
 * @param second_map The second map.
 *  
 * @return true 
 * @return false 
 */
bool comparaison_two_maps(game_map first_map, game_map second_map);
    

/**
 * @brief Testing if two adresses are the same.
 * 
 * @param adress_1 The first adress.
 * 
 * @param adress_2 The second adress.
 * 
 * @return true 
 * @return false 
 */
bool comparaison_two_adresses(const char *adress_1, const char *adress_2);


/**
 * @brief Given movements actions, it should return the final map after executing all the movements.
 * 
 * @param loaded_map A pointer to the structure representing the initial map.
 * 
 * @param length_direction_string An int representing the number of movements you want to execute in the plan.
 * 
 * @param direction_string A string representing the plan.
 *  
 * @return game_map* 
 */
game_map *replay(game_map *loaded_map, int length_direction_string, char *direction_string);


#endif