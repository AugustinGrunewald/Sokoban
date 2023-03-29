/**
 * @file linked_list_map.h
 * 
 * @brief The include file for the linked list.
 */

#ifndef LINKED_LIST_MAP_H
#define LINKED_LIST_MAP_H

#include <stdbool.h>
#include "sokoban.h"
#include "loader.h"


/** Renaming the cell map structure. */
typedef struct cell_map  cell_map;

/** Defining the linked list structure. */
typedef cell_map *linked_list_map;

/**
 * @brief the structure used to build the linked list.
 * 
 */
struct cell_map {
    /** The structure containing the game map */
    game_map *p_map;

    /** The pointer to the next cell of the list */
    cell_map *p_next;
};

/**
 * @brief Creating an empty linked list.
 * 
 * @return linked_list_map empty.
 */
linked_list_map nil();


/**
 * @brief Adding a game map to the linked list.
 * 
 * @param p_map a pointer to the game map to add to the linked list.
 * 
 * @param list the list in which you add the new element.
 * 
 * @return linked_list_map the new linked list with the 
 *         game map as new first cell. 
 */
linked_list_map cons(game_map *p_map, linked_list_map list);


/**
 * @brief Testing if the list is empty.
 * 
 * @param list the list that is tested.
 * 
 * @return true if the list is empty.
 * @return false if the list isn't empty.
 */
bool is_empty(linked_list_map list);


/**
 * @brief Get the game map of index "indice" of the linked list. 
 * 
 * @param list the list you use.
 * 
 * @param indice the indice of the map you want to get.
 * 
 * @return game_map* the wanted game map in the list.
 */
game_map *get_element(linked_list_map list, int indice);


/**
 * @brief Insert a certain game map at a certain indice in the linked list.
 * 
 * @param list the list you use.
 * 
 * @param indice the indice at which you want to insert the game map.
 *  
 * @param p_map the game map you want to insert.
 * 
 * @return linked_list_map the new list with the insertion of a new cell containing all the given informations.
 */
linked_list_map insert_element(linked_list_map list, int indice, game_map *p_map);


/**
 * @brief Remove the cell of a certain indice in the linked list.
 * 
 * @param list_remove_element the list you use.
 * 
 * @param indice the indice of the cell you want to remove.
 * 
 * @return linked_list_map the new list without the cell you wanted. 
 */
linked_list_map remove_element(linked_list_map list_remove_element, int indice);


/**
 * @brief Function that should free all the linked list.
 * 
 * @param list 
 */
void deallocate_list(linked_list_map list);


/**
 * @brief Function that should free all the linked list used in the solver.
 * 
 * @param list 
 */
void deallocate_list_solver(linked_list_map list);

#endif
