#ifndef LOADER_H
#define LOADER_H

#include "sokoban.h"

/**
 * @brief This function defines the map loader
 * 
 * @param adress the adress of the file that need to be open
 * 
 * @return struct game_map* return the dynamically allocated structure representing the map
 */
game_map *map_loader(const char *adress);


void testing_loader(const char *adress);

#endif
