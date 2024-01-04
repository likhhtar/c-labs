#include "clist.h"

void init_list(intrusive_list_t* list){
    intrusive_node_t* new = (intrusive_node_t*)malloc(sizeof(intrusive_node_t));
    list->head = new;
    list->head->prev = NULL;
    list->head->next = NULL;
}

void add_node(intrusive_list_t* list, intrusive_node_t* node){
   node->next = list->head->next;
   node->prev = list->head;

   if(list->head->next)
       list->head->next->prev = node;
   list->head->next = node;
}

void remove_node(intrusive_list_t* list, intrusive_node_t* node){
    node->prev->next = node->next;
    if(node->next)
        node->next->prev = node->prev;
}

int get_length(intrusive_list_t* list){
    int length = 0;
    intrusive_node_t* head = list->head->next;
    while(head){
        head = head->next;
        length++;
    }
    return length;
}

void destroy_list(intrusive_list_t* list)
{
    free(list->head);
}
