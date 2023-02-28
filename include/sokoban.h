#ifndef SOKOBAN_H
#define SOKOBAN_H

/**
 * @brief Print the given map in the console.
 *
 * The width and height of the window are specified in number of cells.
 * `ICON_SIZE` is a constant determining the size in pixel of an icon.
 *
 * @param map  a string representing the map of the game
 *
 * @param width  the width of the map (number of cells)
 *
 * @param height the height of the map (number of cells)
 */
void print_map(char *map, int width, int height);

#endif
