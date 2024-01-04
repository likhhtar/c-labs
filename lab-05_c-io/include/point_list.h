#ifndef POINT_LIST_H_
#define POINT_LIST_H_

#include "stdio.h"

typedef struct point {
    int x, y;
    intrusive_node_t node;
} point_t;

void add_point(intrusive_list_t* list, int x, int y);
void remove_point(intrusive_list_t* list, int x, int y);
void show_all_points(intrusive_list_t* list);
void remove_all_points(intrusive_list_t* list);

#endif

