/**
 * @file queue_map.h
 *
 * @brief The include file for queue map.
 */

#ifndef QUEUE_MAP_H
#define QUEUE_MAP_H

#include <stdbool.h>
#include "sokoban.h"
#include "loader.h"


/**
 * @brief renaming the cell map queue structure
 * 
 */
typedef struct cell_map_queue  cell_map_queue;

/**
 * @brief renaming the first last pointers structure.
 * 
 */
typedef struct first_last_pointers first_last_pointers;

/**
 * @brief renaming the dequeuing tool structure.
 * 
 */
typedef struct dequeuing_tool dequeuing_tool;

/**
 * @brief creating the structure of queue (pointer to a cell).
 * 
 */
typedef cell_map_queue *queue_map;


/**
 * @brief the structure used to build the queue.
 * 
 */
struct cell_map_queue {
    /** The map */
    game_map *p_map;

    /** The pointer to the next cell */
    cell_map_queue *p_next;

    /** the pointer to the mother cell */
    cell_map_queue *p_mother;

    /** The direction used to build this cell */
    char direction;
};


/**
 * @brief the structure used to obtain a queue with a complexity 
 *        of O(1) for both enqueue and dequeue.
 * 
 */
struct first_last_pointers {
    /** A pointer to the first cell of the queue. */
    cell_map_queue *p_first;

    /** A pointer to the last cell of the queue. */
    cell_map_queue *p_last;
};

/**
 * @brief the structure returned by the dequeue function to get the removed cell map, 
 *        the updated queue and the pointers to the first and last cell.
 * 
 */
struct dequeuing_tool {
    /** The returned queue. */
    queue_map queue;

    /** The map that is dequeued. */
    cell_map_queue *p_map;
};


/**
 * @brief Creating an empty queue.
 * 
 * @return queue_map empty.
 */
queue_map nil_queue();


/**
 * @brief New version of the enqueue that should had a new cell at the tail of the queue.
 *
 * @param queue the queue used in the function.
 * 
 * @param p_first_last_pointers a pointer to the first last pointers structure used for the queue
 * 
 * @param p_map the map you want to enqueue.
 * 
 * @param direction the direction used to get the new map (N,S,E,W).
 * 
 * @param p_mother a pointer to the mother cell of the new one.
 * 
 * @return the queue with the new map that has been enqueue.
 */
queue_map enqueue_bis(queue_map queue, first_last_pointers *p_first_last_pointers, game_map *p_map, char direction, cell_map_queue *p_mother);


/**
 * @brief Dequeue a game map a the head of the queue.
 * 
 * @param queue the queue in which you want to dequeue the map.
 * 
 * @param p_first_last_pointers the structure giving two pointers to the first and last cell.
 * 
 * @return dequeuing_tool the structure giving the removed cell map, 
 *         the updated queue and the two pointers to the first and last cell. 
 */
dequeuing_tool dequeue_bis(queue_map queue, first_last_pointers *p_first_last_pointers);


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
 * @brief Function that should free all the queue used in the solver.
 * 
 * @param queue 
 */
void deallocate_queue_solver(queue_map queue);

#endif
