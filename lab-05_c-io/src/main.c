#include "clist.h"
#include "point_list.h"
#include "stdio.h"

void op_points(intrusive_node_t* node, void* format)
{
    point_t* cur_point = container_of(node, point_t, node);
    printf((char*)format, cur_point->x, cur_point->y);
}

void op_count(intrusive_node_t* node, void* count)
{
    (*(int*)count)++;
}

void show_points(intrusive_list_t* list, char* format)
{
    apply(list, op_points, format);
    printf("\n");
}

void show_count(intrusive_list_t* list)
{
    int count = 0;
    apply(list, op_count, &count);
    printf("%d\n", count);
}

void load_text(char* file_name, intrusive_list_t* list)
{
    FILE* fin = fopen(file_name, "r");
    int check;
    while(1){
        int x, y;
        check = fscanf(fin, "%d %d", &x, &y);
        if(check != 2) break;
        add_point(list, x, y);
    }
    fclose(fin);
}

void load_bin(char* file_name, intrusive_list_t* list)
{
    FILE* fin = fopen(file_name, "r");
    int x, y;
    const size_t size = 6;
    int check;
    unsigned char result[size];

    while (1)
    {
        check = fread(result, sizeof(char), size, fin);
        if (check != size) break;

        x = (int)result[0] + ((int)result[1] << 8) + ((int)result[2] << 16);
        y = (int)result[3] + ((int)result[4] << 8) + ((int)result[5] << 16);

        if (x >= 256 * 256 * 128) x -= 256 * 256 * 256;
        if (y >= 256 * 256 * 128) y -= 256 * 256 * 256;

        add_point(list, x, y);
    }

    fclose(fin);
}

void show_text_points(intrusive_list_t* list, char* filename) {
    FILE* fout = fopen(filename, "w");

    intrusive_node_t* head = list->head;
    while(head->next){
        point_t* cur_point = container_of(head->next, point_t, node);

        fprintf(fout, "%d %d\n", cur_point->x, cur_point->y);

        head = head->next;
    }
    fclose(fout);
}

void show_bin_points(intrusive_list_t* list, char* filename) {
    FILE* fout = fopen(filename, "wb");

    int x, y;
    const size_t size = 6;
    unsigned char result[size];

    intrusive_node_t* head = list->head;
    while(head->next){
        point_t* cur_point = container_of(head->next, point_t, node);
        x = cur_point->x;
        y = cur_point->y;

        if(x < 0) x += 256 * 256 * 256;
        if(y < 0) y += 256 * 256 * 256;

        result[0] = x & (unsigned char)255;
        result[1] = (x >> 8) & (unsigned char)255;
        result[2] = (x >> 16) & (unsigned char)255;

        result[3] = y & (unsigned char)255;
        result[4] = (y >> 8) & (unsigned char)255;
        result[5] = (y >> 16) & (unsigned char)255;

        fwrite(result, sizeof(char), size, fout);

        head = head->next;
    }

    fclose(fout);
}

int main(int argc, char* argv[]) {
    intrusive_list_t l;
    init_list(&l);

    if(!strcmp(argv[1], "loadtext")){
        load_text(argv[2], &l);
    }
    else{
        load_bin(argv[2], &l);
    }

    if(!strcmp(argv[3], "savetext")){
        show_text_points(&l, argv[4]);
    }
    else if(!strcmp(argv[3], "savebin")){
        show_bin_points(&l, argv[4]);
    }
    else if(!strcmp(argv[3], "print")){
        show_points(&l, argv[4]);
    }
    else if(!strcmp(argv[3], "count")){
        show_count(&l);
    }

    remove_all_points(&l);
    destroy_list(&l);
    return 0;
}


