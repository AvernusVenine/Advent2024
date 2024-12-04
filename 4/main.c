#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *PATH = "test.txt";
const char *PATTERN = "XMAS";
const int SIZE = 2048;
const int PATTERN_SIZE = 4;

int part_one();
int check_verticals(char **puzzle, int x, int y);
int check_horizontals(char **puzzle, int x, int y);
int check_diagonals(char **puzzle, int x, int y);

int main(){
    int total = part_one();
    printf("There are a total of %d XMAS's\n", total);
}

int part_one(){
    FILE *file;
    file = fopen(PATH, "r");

    char **puzzle = (char **) malloc(SIZE * sizeof(char *));

    for(int a = 0; a < SIZE; a++){
        puzzle[a] = (char *) malloc(SIZE * sizeof(char));
    }

    int i = 0;
    while(fgets(puzzle[i], SIZE, file)){
        i++;
    }

    int count = 0;

    for(int x = 0; x < SIZE; x++){

        for(int y = 0; y < SIZE; y++){
            int precount = count;

            //count += check_verticals(puzzle, x, y);
            count += check_horizontals(puzzle, x, y);
            //count += check_diagonals(puzzle, x, y);
        }
    }
    

    return count;
}

int check_diagonals(char **puzzle, int x, int y){
    int count = 0;

    char buffer[4];

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

    if(puzzle[x][y] == '\0'){
        return 0;
    }

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
