#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *PATH = "rules.txt";

typedef struct Rule{
    int page;
    struct Clause *clauses;
    struct Rule *next;
} Rule;

typedef struct Clause{
    int clause;
    struct Clause *next;
} Clause;

int part_one();
int part_two();
struct Rule* append_rule(struct Rule *rule, int page, int clause);
int check_rule(struct Rule *rule, int* book, int page, int size);

int main(){
    int total = part_one();
    printf("The sum of middle pages in valid books is %d\n", total);
}

int part_one(){
    FILE *file;
    file = fopen(PATH, "r");

    char *buffer = (char *) malloc(1024 * sizeof(char));

    struct Rule *rule;

    while(fgets(buffer, 1024, file)){
        if(buffer[0] == '\n'){
            break;
        }

        char *token = strtok(buffer, "|");
        int page = atoi(token);

        token = strtok(NULL, "|");
        int clause = atoi(token);

        rule = append_rule(rule, page, clause);
    }

    int count = 0;

    while(fgets(buffer, 1024, file)){
        int *book = (int*) malloc(sizeof(int) * 128);

        char *token = strtok(buffer, ",");

        int valid = 1;
        int i = 0;
        while(token != NULL){
            int page = atoi(token);

            valid = check_rule(rule, book, page, i);

            if(!valid){
                break;
            }

            token = strtok(NULL, ",");
            book[i] = page;
            i++;
        }

        if(valid){
            int mid = (i/2);
            count += book[mid];
        }

    }

    return count;
}

int check_rule(struct Rule *rule, int *book, int page, int size){

    while(rule != NULL){

        if(rule->page == page){
            
            struct Clause *clause = rule->clauses;

            while(clause != NULL){
                
                for(int i = 0; i < size; i++){

                    if(book[i] == clause->clause){
                        return 0;
                    }

                }

                clause = clause->next;
            }

        }


        rule = rule->next;
    }

    return 1;

}

struct Rule* append_rule(struct Rule *rule, int page, int clause){

    struct Rule *curr = rule;

    while(curr != NULL){

        if(curr->page == page){
            
            struct Clause *c_curr = curr->clauses;

            while(c_curr != NULL){
                if(c_curr->clause == clause){
                    return rule;
                }

                c_curr = c_curr->next;
            }

            struct Clause *ptr = (struct Clause*) malloc(sizeof(struct Clause));
            ptr->clause = clause;
            ptr->next = curr->clauses;

            curr->clauses = ptr;
            return rule;
        }

        curr = curr->next;
    }

    struct Rule *ptr = (struct Rule*) malloc(sizeof(Rule));

    ptr->page = page;
    ptr->next = rule;

    struct Clause *clse = (struct Clause*) malloc(sizeof(Clause));
    clse->clause = clause;


    ptr->clauses = clse;

    return ptr;

}