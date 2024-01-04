#include "clist.h"
#include "point_list.h"

void add_point(intrusive_list_t* list, int x, int y) {
    point_t* new_point = (point_t*) malloc(sizeof(point_t));
    new_point->x = x;
    new_point->y = y;
    add_node(list, &new_point->node);
}

void show_all_points(intrusive_list_t* list) {
    intrusive_node_t* head = list->head->next;
    while(head){
        point_t* cur_point = container_of(head, point_t, node);

        //printf(fin, "%d %d", cur_point->x, cur_point->y);

        head = head->next;
        if(head){
            printf("\n");
        }
    }
}


void remove_all_points(intrusive_list_t* list) {
    intrusive_node_t* head = list->head;
    while(head->next){
        head = head->next;
    }
    while(head->prev)
    {
        head = head->prev;
        point_t* this_point = container_of(head->next, point_t, node);
        remove_node(list, head->next);
        free(this_point);
    }
}

