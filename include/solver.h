#ifndef SOLVER_H
#define SOLVER_H

#include <stdbool.h>
#include "sokoban.h"
#include "loader.h"
#include "linked_list_map.h"
#include "queue_map.h"

typedef struct stats stats;

struct stats{
    /** A boolean statting if there is a wining plan or not.*/
    bool win;

    /** A string representing the solution plan.*/
    char *solution_plan;

    /** An int representing the length of the plan. */
    int plan_length;

    /** An int giving the number of explored nodes.*/
    int nmb_explored_nodes;

    /** A double representing the time of used by the solver */
    double time_spent;
};


/**
 * 
 * @brief Function testing if the given map is a wining solution.
 * 
 * @param map the given map.
 * 
 * @return true if the map is a wining one.
 * @return false if the map isn't a wining one.
 */
bool wining_test(game_map map);


/**
 * 
 * @brief The function to solve a sokoban game.
 * 
 * @param initial_map A pointer to the initial map that you want to solve.
 * 
 * @return A pointer to the structure stat containing the solution plan and the other usefull parameters describe in the structure above.
 */
stats *solver(game_map *initial_map);


/**
 * 
 * @brief The function checking if a map is already in the linked list.
 * 
 * @param p_map a pointer to the map.
 * 
 * @param list a linked list in which you're searching the map.
 * 
 * @return true if the map is already in the list.
 * @return false if not.
*/
bool searching_linked_list(game_map *p_map, linked_list_map list);


/**
 * 
 * @brief The function returning the number of moove needed to win.
 * 
 * @param queue The queue in which you're searching.
 * 
 * @return an int representing the size researched.
 */
int plan_length(queue_map queue);

#endif
