#ifndef LOADER_H
#define LOADER_H

/**
 * @brief This function defines the map loader
 * 
 * @param argc 
 * 
 * @param argv the name of the file that need to be open
 * 
 * @return struct game_map* return the dynamically allocated structure representing the map 
 */
struct game_map *map_loader(int argc, char *argv[]);

#endif
