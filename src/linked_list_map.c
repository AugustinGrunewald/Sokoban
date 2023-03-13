#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linked_list_map.h"
#include "sokoban.h"
#include "loader.h"


linked_list_map nil(){
    return NULL;
}

linked_list_map cons(game_map *p_map, linked_list_map list){
    cell_map *p_new_list = (cell_map *) malloc(sizeof(cell_map));

    p_new_list->p_previous = NULL;
    p_new_list->p_map = p_map;
    p_new_list->p_next = list; 
    return p_new_list;
}

int size(linked_list_map list){
    int size = 0;
    cell_map *index = list;

    while (index != NULL) {
        index = index->p_next; 
        size++;
    }

    return size;
}

bool is_empty(linked_list_map list){
    if (list == NULL){
        return true;
    } else {
        return false;
    }
}

void print_list(linked_list_map list){
    cell_map *index = list;

    while (index != NULL){
        print_map(*(index->p_map));
        index = index->p_next;
    }
}

game_map *get_element(linked_list_map list, int indice){
    cell_map *current_cell = list;

    for (int ind = 0; ind < indice; ind++){
        current_cell = current_cell->p_next;
    }
    return current_cell->p_map;
}

linked_list_map insert_element(linked_list_map list, int indice, game_map *p_map){
    cell_map *current_cell = list;
    cell_map *old_cell = list;
    cell_map *new_cell = (cell_map *)malloc(sizeof(cell_map));

    //particular case : indice = 0
    if (indice == 0){
        free(new_cell);
        return cons(p_map, list);
    }
    else{
        for (int ind = 0; ind < indice; ind++){
            current_cell = current_cell->p_next;
        }
        for (int ind = 0; ind < indice - 1; ind++){
            old_cell = old_cell->p_next;
        }

        new_cell->p_map = p_map;
        new_cell->p_next = current_cell;
        new_cell->p_previous = old_cell;
        old_cell->p_next = new_cell;

        return list;
    }
}

linked_list_map remove_element(linked_list_map list, int indice){
    cell_map *current_cell = list;
    cell_map *old_cell = list;
    cell_map *copy_cell;

    //particular case : indice = 0
    if (indice == 0){
        (list->p_next)->p_previous = NULL;
        return list->p_next;
    }
    else{
        for (int ind = 0; ind < indice; ind++){
            current_cell = current_cell->p_next;
        }
        for (int ind = 0; ind < indice - 1; ind++){
            old_cell = old_cell->p_next;
        }

        copy_cell = current_cell;
        (current_cell->p_next)->p_previous = old_cell;
        current_cell = current_cell->p_next;
        old_cell->p_next = current_cell;
        free(copy_cell);
        
        return list;
    }
}

void deallocate_list(linked_list_map list){
    if (is_empty(list) == false){
        deallocate_list(list->p_next);
        free(list);
    }    
}