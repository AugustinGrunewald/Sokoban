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
 * @brief the structure returned by the dequeue function to get the removed cell map, the updated queue and the pointers to the first and last cell.
 * 
 */
struct dequeuing_tool {
    queue_map queue;
    cell_map *p_map;
};


/**
 * @brief Creating an empty queue.
 * 
 * @return queue_map empty.
 */
queue_map nil_queue();


/**
 * @brief trying a new version of the enqueue function that should be simplier
 *
 * @param queue the queue used in the function.
 * 
 * @param p_first_last_pointers a pointer to the first last pointers structure used for the queue
 * 
 * @param p_map the map you want to enqueue.
 * 
 * @param direction the direction used to get the new map (N,S,E,W).
 * 
 * @param depth the depth at which youplace the new map.
 * 
 * @param p_mother a pointer to the mother cell of the new one.
 * 
 * @return the queue with the new map that has been enqueue.
 */
queue_map enqueue_bis(queue_map queue, first_last_pointers *p_first_last_pointers, game_map *p_map, char direction, int depth, cell_map *p_mother);


/**
 * @brief Dequeue a game map a the head of the queue.
 * 
 * @param queue the queue in which you want to dequeue the map.
 * 
 * @param first_last_pointers the structure giving two pointers to the first and last cell.
 * 
 * @return dequeuing_tool the structure giving the removed cell map, the updated queue and the two pointers to the first and last cell. 
 */
dequeuing_tool dequeue_bis(queue_map queue, first_last_pointers *p_first_last_pointers);


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
 * @brief Function that should free all the queue.
 * 
 * @param queue 
 */
void deallocate_queue(queue_map queue);

#endif
