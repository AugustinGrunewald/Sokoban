#ifndef LINKED_LIST_MAP_H
#define LINKED_LIST_MAP_H

#include <stdbool.h>
#include "sokoban.h"
#include "loader.h"


typedef struct cell_map  cell_map;
typedef struct first_last_pointers first_last_pointers;
typedef struct enqueuing_tool enqueuing_tool;
typedef struct dequeuing_tool dequeuing_tool;
typedef cell_map *queue_map;


/**
 * @brief the structure used to build the queue.
 * 
 */
struct cell_map {
    game_map *p_map;
    cell_map *p_next;
    cell_map *p_mother;
    char direction;
    int depth;
};


/**
 * @brief the structure used to obtain a queue with a complexity of O(1) for both enqueue and dequeue.
 * 
 */
struct first_last_pointers {
    cell_map *p_first;
    cell_map *p_last;
};


/**
 * @brief the structure returned by the enqueue function to get the new queue and the pointers to the first and last cell.
 * 
 */
struct enqueuing_tool {
    queue_map queue;
    first_last_pointers *first_last_pointers;
};


/**
 * @brief the structure returned by the dequeue function to get the removed map, the updated queue and the pointers to the first and last cell.
 * 
 */
struct dequeuing_tool {
    queue_map queue;
    game_map *p_map;
    first_last_pointers *first_last_pointers;
};


/**
 * @brief Creating an empty queue.
 * 
 * @return queue_map empty.
 */
queue_map nil_queue();


/**
 * @brief Adding a game map to the queue.
 * 
 * @param element an element to add to the queue.
 * 
 * @param queue the queue in which you add the new element.
 * 
 * @param direction the character giving the direction used to create the new map (N,S,E,W).
 * 
 * @param depth giving the depth of the cell in the tree.
 * 
 * @param p_mother a pointer to the mother cell of the new one.
 * 
 * @return queue_map the new queue with the game map as new first cell. 
 */
queue_map cons_queue(game_map *p_map, queue_map queue, char direction, int depth, cell_map *p_mother);


/**
 * @brief Enqueue a game map at the tail of the queue. 
 *  
 * @param queue_tool the structure containing the queue and the first last pointers. 
 * 
 * @param p_map the map you want to enqueue.
 * 
 * @param direction the direction used to get to the new map (N,S,E,W).
 * 
 * @param depth the depth of this new map in the tree. 
 * 
 * @param p_mother a pointer to the mother cell of the new one.
 * 
 * @return *enqueuing_tool a pointer to the structure giving the new queue and the two pointers to the first and last cell.  
 */
enqueuing_tool *enqueue(enqueuing_tool *queue_tool, game_map *p_map, char direction, int depth, cell_map *p_mother);


/**
 * @brief Dequeue a game map a the head of the queue.
 * 
 * @param first_last_pointers the structure giving two pointers to the first and last cell.
 * 
 * @param queue the queue in which you want to dequeue the map.
 * 
 * @return dequeuing_tool the structure giving the removed game map, the updated queue and the two pointers to the first and last cell. 
 */
dequeuing_tool dequeue(first_last_pointers *first_last_pointers, queue_map queue);


/**
 * @brief Giving the size of your queue (number of cells).
 * 
 * @param queue the queue for which you want to know the size.
 * 
 * @return int representing the size of the queue.
 */
int size_queue(queue_map queue);


/**
 * @brief Testing if the queue is empty.
 * 
 * @param queue the queue that is tested.
 * 
 * @return true if the queue is empty.
 * @return false if the queue isn't empty.
 */
bool is_empty_queue(queue_map queue);


/**
 * @brief Print the maps of the queue in the console.
 * 
 * @param queue 
 */
void print_queue(queue_map queue);


/**
 * @brief Get the game map of index "indice" of the queue. 
 * 
 * @param queue the queue you use.
 * 
 * @param indice the indice of the element you want to get.
 * 
 * @return game_map* the wanted game map in the queue.
 */
game_map *get_element_queue(queue_map queue, int indice);


/**
 * @brief Insert a certain game map at a certain indice in the queue.
 * 
 * @param queue the queue you use.
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
 * @return queue_map the new queue with the insertion of a new cell containing all the given informations.
 */
queue_map insert_element_queue(queue_map queue, int indice, game_map *p_map, char direction, int depth, cell_map *p_mother);


/**
 * @brief Remove the cell of a certain indice in the queue.
 * 
 * @param queue the queue you use.
 * 
 * @param indice the indice of the cell you want to remove.
 * 
 * @return queue_map the new list without the cell you wanted. 
 */
queue_map remove_element_queue(queue_map queue, int indice);


/**
 * @brief Function that should free all the queue.
 * 
 * @param queue 
 */
void deallocate_queue(queue_map queue);

#endif
