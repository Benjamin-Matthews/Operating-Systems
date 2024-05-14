#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 2D array to store sudoku grid
int grid[9][9];

void* processSubgrid(void* index) {
    int* subgridIndex = (int*)index;
    int valid = 1;

    // validation 
    int encountered[10] = {0};

    // starting row and column for the current subgrid
    int startRow = (*subgridIndex / 3) * 3;
    int startCol = (*subgridIndex % 3) * 3;

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
           

            int currentValue = grid[i][j];

            // check if number has been encountered before
            if (encountered[currentValue] == 1) {
                valid = 0;
                break;
            }

            // mark
            encountered[currentValue] = 1;
        }
    }

    // valid?
    
    if (valid) {
    printf("Thread # %2d (subgrid %d) is valid\n", *subgridIndex + 1, *subgridIndex + 1);
    } else {
    printf("Thread # %2d (subgrid %d) is INVALID\n", *subgridIndex + 1, *subgridIndex + 1);
    }
    free(index);
    return NULL;
}


void* processRow(void* index) {
    int* rowIndex = (int*)index;
    //boolean for valid or not
    int valid = 1;

    // array to keep track of encountered numbers in the row
    int encountered[10] = {0};  

    for (int j = 0; j < 9; j++){
    

        int currentValue = grid[*rowIndex][j];

        // if the number has been encountered before
        if (encountered[currentValue] == 1) {
            valid = 0;
            break;  
        }

        // mark
        encountered[currentValue] = 1;

    }

    // output
    if (valid) {
    printf("Thread # %2d (row %d) is valid\n", *rowIndex + 10, *rowIndex + 1);
    } else {
    printf("Thread # %2d (row %d) is INVALID\n", *rowIndex + 10, *rowIndex + 1);
    }

    

    free(index);  
    return NULL;
}

void* processColumn(void* index) {
    int* colIndex = (int*)index;
    //boolean for valid or not
    int valid = 1;

    // array to keep track of encountered numbers in the column
    int encountered[10] = {0};  

    for (int j = 0; j < 9; j++){



        int currentValue = grid[j][*colIndex];

        // the number has been encountered before
        if (encountered[currentValue] == 1) {
            valid = 0;
            break;  
        }

        // mark
        encountered[currentValue] = 1;


    }

    // output
    if (valid) {
    printf("Thread # %2d (column %d) is valid\n", *colIndex + 19, *colIndex + 1);
    } else {
    printf("Thread # %2d (column %d) is INVALID\n", *colIndex + 19, *colIndex + 1);
    }

    

    free(index);  
    return NULL;
}

int main(int argc, char* argv[]) {
    // open file
    char* filename = argv[1];
    FILE* file = fopen(filename, "r");

    // read Sudoku grid from the file
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fscanf(file, "%d", &grid[i][j]);
        }
    }

    // close file
    fclose(file);


    // threads
    pthread_t threads[27];

    // 9 threads for subgrid
    for (int i = 0; i < 9; i++) {
        int* subgridIndex = malloc(sizeof(int));
        *subgridIndex = i;
        pthread_create(&threads[i], NULL, processSubgrid, (void*)subgridIndex);
    }

    // 9 threads for rows
    for (int i = 9; i < 18; i++) {
        int* rowIndex = malloc(sizeof(int));
        *rowIndex = i - 9;
        pthread_create(&threads[i], NULL, processRow, (void*)rowIndex);
    }

    // 9 threads for columns
    for (int i = 18; i < 27; i++) {
        int* colIndex = malloc(sizeof(int));
        *colIndex = i - 18;
        pthread_create(&threads[i], NULL, processColumn, (void*)colIndex);
    }

    // wait for threads
    for (int i = 0; i < 27; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
