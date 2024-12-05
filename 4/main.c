#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *PATH = "xmas.txt";
const char *PATTERN = "XMAS";
const int SIZE = 2048;
const int PATTERN_SIZE = 4;

int part_one();
int part_two();
int check_verticals(char **puzzle, int x, int y);
int check_horizontals(char **puzzle, int x, int y);
int check_diagonals(char **puzzle, int x, int y);
int check_cross(char **puzzle, int x, int y);

int main(){
    int total = part_one();
    printf("There are a total of %d XMAS's\n", total);
    total = part_two();
    printf("There are a total of %d X-Mas's\n", total);
}

int part_one(){
    FILE *file;
    file = fopen(PATH, "r");

    char **puzzle = (char **) malloc(SIZE * sizeof(char *));

    for(int a = 0; a < SIZE; a++){
        puzzle[a] = (char *) malloc(SIZE * sizeof(char));
    }

    char *buffer = (char *) malloc(1024 * sizeof(char *));

    int i = 0;
    while(fgets(buffer, 1024, file) && i < SIZE){

        strncpy(puzzle[i], buffer, SIZE);
        i++;
    }

    int count = 0;

    for(int x = 0; x < SIZE; x++){

        for(int y = 0; y < SIZE; y++){
            count += check_verticals(puzzle, x, y);
            count += check_horizontals(puzzle, x, y);
            count += check_diagonals(puzzle, x, y);
        }
    }
    

    return count;
}

int part_two(){
    FILE *file;
    file = fopen(PATH, "r");

    char **puzzle = (char **) malloc(SIZE * sizeof(char *));

    for(int a = 0; a < SIZE; a++){
        puzzle[a] = (char *) malloc(SIZE * sizeof(char));
    }

    char *buffer = (char *) malloc(1024 * sizeof(char *));

    int i = 0;
    while(fgets(buffer, 1024, file) && i < SIZE){

        strncpy(puzzle[i], buffer, SIZE);
        i++;
    }

    int count = 0;

    for(int x = 0; x < SIZE; x++){

        for(int y = 0; y < SIZE; y++){
            count += check_cross(puzzle, x, y);
        }
    }

    return count;
}

int check_cross(char **puzzle, int x, int y){
    if(puzzle[x][y] != 'A'){
        return 0;
    }

    int count = 0;

    if(x - 1 < 0 || y - 1 < 0){
        return 0;
    }

    if(x + 1 > SIZE || y + 1 > SIZE){
        return 0;
    }

    if(puzzle[x-1][y-1] == 'M'){
        if(puzzle[x+1][y+1] == 'S'){
            count++;
        }
    }
    else if(puzzle[x-1][y-1] == 'S'){
        if(puzzle[x+1][y+1] == 'M'){
            count++;
        }
    }

    if(puzzle[x-1][y+1] == 'M'){
        if(puzzle[x+1][y-1] == 'S'){
            count++;
        }
    }
    else if(puzzle[x-1][y+1] == 'S'){
        if(puzzle[x+1][y-1] == 'M'){
            count++;
        }
    }
    
    if(count == 2){
        return 1;
    }

    return 0;
}

int check_diagonals(char **puzzle, int x, int y){
    int count = 0;

    if(puzzle[x][y] == '\0'){
        return 0;
    }


    for(int i = 0; i < PATTERN_SIZE+1; i++){
        if(i == PATTERN_SIZE){
            count++;
            break;
        }

        if(puzzle[x+i][y+i] != PATTERN[i]){
            break;
        }
    }

    for(int i = 0; i < PATTERN_SIZE+1; i++){
        if(i == PATTERN_SIZE){
            count++;
            break;
        }

        if(x-i < 0){
            break;
        }

        if(puzzle[x-i][y+i] != PATTERN[i]){
            break;
        }
    }

    for(int i = 0; i < PATTERN_SIZE+1; i++){
        if(i == PATTERN_SIZE){
            count++;
            break;
        }

        if(y-i < 0){
            break;
        }

        if(puzzle[x+i][y-i] != PATTERN[i]){
            break;
        }
    }

    for(int i = 0; i < PATTERN_SIZE+1; i++){
        if(i == PATTERN_SIZE){
            count++;
            break;
        }

        if(x-i < 0 || y-i < 0){
            break;
        }

        if(puzzle[x-i][y-i] != PATTERN[i]){
            break;
        }
    }

    return count;
}

int check_horizontals(char **puzzle, int x, int y){
    int count = 0;
    //Check forwards
    int i = 0;

    for(int a = y; a < SIZE; a++){
        if(i == PATTERN_SIZE){
            count++;
            break;
        }

        if(puzzle[x][a] == PATTERN[i]){
            i++;
        }
        else{
            break;
        }
    }

    //Check backwards
    i = 0;

    for(int a = y; a > -1; a--){
        if(puzzle[x][a] == PATTERN[i]){
            i++;
            if(i == PATTERN_SIZE){
                count++;
                break;
            }
        }
        else{
            break;
        }
    }

    return count;
}

int check_verticals(char **puzzle, int x, int y){
    int count = 0;
    //Check forwards
    int i = 0;

    if(puzzle[x][y] == '\0'){
        return 0;
    }

    for(int a = x; a < SIZE; a++){
        if(i == PATTERN_SIZE){
            count++;
            break;
        }

        if(puzzle[a][y] == PATTERN[i]){
            i++;
        }
        else{
            break;
        }
    }

    //Check backwards
    i = 0;

    for(int a = x; a > -1; a--){
        if(puzzle[a][y] == PATTERN[i]){
            i++;

            if(i == PATTERN_SIZE){
                count++;
                break;
            }
        }
        else{
            break;
        }
    }

    return count;
}
