#include "clist.h"

void init_list(intrusive_list_t* list){
    intrusive_node_t* new = (intrusive_node_t*)malloc(sizeof(intrusive_node_t));
    list->head = new;
    list->head->prev = NULL;
    list->head->next = NULL;
}

void add_node(intrusive_list_t* list, intrusive_node_t* node){
   intrusive_node_t* head = list->head;
   while(head->next){
       head = head->next;
   }
   
   node->prev = head;
   node->next = NULL;
   head->next = node;
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

void destroy_list(intrusive_list_t* list){
    free(list->head);
}

void apply(intrusive_list_t* list, void (*op)(intrusive_node_t *node, void *data), void* data){
    intrusive_node_t* head = list->head;
    while(head->next)
    {
        op(head->next, data);
        head = head->next;
    }
}

