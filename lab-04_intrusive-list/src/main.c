#include "clist.h"
#include "stdio.h"

typedef struct point {
  int x, y;
  intrusive_node_t node;
} point_t;

void add_point(intrusive_list_t* list, int x, int y) {
    point_t* new_point = (point_t*) malloc(sizeof(point_t));
    new_point->x = x;
    new_point->y = y;
    add_node(list, &new_point->node);
}

void remove_point(intrusive_list_t* list, int x, int y) { // removes all (x, y) pairs
    intrusive_node_t* head = list->head->next;
    while(head){
        point_t* cur_point = container_of(head, point_t, node);
	intrusive_node_t* next = head->next;
        if(cur_point->x == x && cur_point->y == y){
            remove_node(list, head);
            free(cur_point);
        }
        head = next;
    }
}

void show_all_points(intrusive_list_t* list) {
    intrusive_node_t* head = list->head->next;
    int length = get_length(list);
    while(head){
        point_t* cur_point = container_of(head, point_t, node);

        printf("(%d %d)", cur_point->x, cur_point->y);

        head = head->next;
        if(head){
            printf(" ");
        }
    }
    printf("\n");
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

int main() {
    intrusive_list_t l;
    init_list(&l);

    int x = 0;
    int y = 0;
    char command[6] = "";
    while(1){
        scanf("%6s", command);

        if (!strcmp(command, "add")){
            scanf("%d %d", &x, &y);
            add_point(&l, x, y);
        }
        else if (!strcmp(command, "rm")){
            scanf("%d %d", &x, &y);
            remove_point(&l, x, y);
        }
        else if (!strcmp(command, "rma")){
            remove_all_points(&l);
        }
        else if (!strcmp(command, "len")){
            int length = get_length(&l);
            printf("%d\n", length);
        }
        else if (!strcmp(command, "print")){
            show_all_points(&l);
        }
        else if (!strcmp(command, "exit")){
            break;
        }
        else{
            printf("Unknown command\n");
        }
    }

    remove_all_points(&l);
    destroy_list(&l);
    return 0;
}
