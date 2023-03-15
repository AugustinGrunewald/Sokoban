#ifndef LINKED_LIST_MAP_H
#define LINKED_LIST_MAP_H

#include <stdbool.h>
#include "sokoban.h"
#include "loader.h"


typedef struct cell_map  cell_map;
typedef cell_map *queue_map;

struct cell_map {
    game_map *p_map;
    cell_map *p_next;
    cell_map *p_mother;
    char direction;
    int depth;
};

/**
 * @brief Creating an empty linked list.
 * 
 * @return linked_list_map empty.
 */
queue_map nil();


/**
 * @brief Adding a game map to the linked list.
 * 
 * @param element an element to add to the linked list.
 * 
 * @param list the list in which you add the new element.
 * 
 * @param direction the character giving the direction used to create the new map (N,S,E,W).
 * 
 * @param depth giving the depth of the cell in the tree.
 * 
 * @param p_mother a pointer to the mother cell of the new one.
 * 
 * @return queue_map the new linked list with the game map as new first cell. 
 */
queue_map cons(game_map *p_map, queue_map list, char direction, int depth, cell_map *p_mother);


/**
 * @brief Giving the size of your linked list (number of cells).
 * 
 * @param list the list for which you want to know the size.
 * 
 * @return int representing the size of the linked list.
 */
int size(queue_map list);


/**
 * @brief Testing if the list is empty.
 * 
 * @param list the list that is tested.
 * 
 * @return true if the list is empty.
 * @return false if the list isn't empty.
 */
bool is_empty(queue_map list);


/**
 * @brief Print the map of the linked list in the console.
 * 
 * @param list 
 */
void print_list(queue_map list);


/**
 * @brief Get the game map of index "indice" of the linked list. 
 * 
 * @param list the list you use.
 * 
 * @param indice the indice of the element you want to get.
 * 
 * @return game_map* the wanted game map in the list.
 */
game_map *get_element(queue_map list, int indice);


/**
 * @brief Insert a certain game map at a certain indice in the linked list.
 * 
 * @param list the list you use.
 * 
 * @param indice the indice at which you want to insert the game map.
 *  
 * @param p_map the game map you want to insert.
 * 
 * @param direction the character giving the direction used to create the new map (N,S,E,W).
 * 
 * @param depth giving the depth of the cell in the tree.
 * 
 * @param p_mother a pointer to the mother cell of the new one.
 * 
 * @return queue_map the new list with the insertion of a new cell containing all the given informations.
 */
queue_map insert_element(queue_map list, int indice, game_map *p_map, char direction, int depth, cell_map *p_mother);


/**
 * @brief Remove the cell of a certain indice in the linked list.
 * 
 * @param list the list you use.
 * 
 * @param indice the indice of the cell you want to remove.
 * 
 * @return linked_list_map the new list without the cell you wanted. 
 */
queue_map remove_element(queue_map list_remove_element, int indice);


/**
 * @brief Function that should free all the linked list.
 * 
 * @param list 
 */
void deallocate_list(queue_map list);

#endif
