#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *PATH = "locations.txt";

typedef struct List{
    int val;
    struct List *next;
} List;

typedef struct HashMap{
    int val;
    int count;
    struct HashMap *next;
} HashMap;

void load_locations(struct List** list_one, struct List** list_two);
void load_hashmap(struct HashMap** map_one, struct HashMap** map_two);
struct List* append_list(struct List* list, int val);
void append_map(struct HashMap* map, int val);

int main(){

    struct List *list_one = NULL;
    struct List *list_two = NULL;

    load_locations(&list_one, &list_two);

    long total_diff = 0;

    while(list_one != NULL && list_two != NULL){
        long diff = list_one-> val - list_two-> val;
        total_diff += abs(diff);

        list_one = list_one->next;
        list_two = list_two->next;
    }

    printf("Total difference is %d\n", total_diff);

    struct HashMap *map_one = NULL;
    struct HashMap *map_two = NULL;
}

void load_hashmap(struct HashMap** map_one, struct HashMap** map_two){
    FILE *file;
    file = fopen(PATH, "r");

    if(file == NULL){
        perror("Failed to open file");
        return;
    }

    char buffer[256];

    while(fgets(buffer, sizeof(buffer), file)){

    }
}

void append_map(struct HashMap* map, int val){
    
}

void load_locations(struct List** list_one, struct List** list_two){
    FILE *file;
    file = fopen(PATH, "r");

    if(file == NULL){
        perror("Failed to open file");
        return;
    }

    char buffer[256];

    while(fgets(buffer, sizeof(buffer), file)){

        char* token = strtok(buffer, " ");
        int val = atoi(token);
        *list_one = append_list(*list_one, val);

        token = strtok(NULL, " ");
        int size = strlen(token);
        token[size] = '\0';
        val = atoi(token);
        *list_two = append_list(*list_two, val);
    }

}

struct List* append_list(struct List* list, int val){
    struct List* ptr = (struct List*) malloc(sizeof(struct List));
    ptr->val = val;

    struct List* prev = NULL;
    struct List* curr = list;

    while(curr != NULL && curr->val < val){
        prev = curr;
        curr = curr->next;
    }

    ptr->next = curr;
    

    if(prev != NULL){
        prev->next = ptr;
        return list;
    }

    return ptr;

}
