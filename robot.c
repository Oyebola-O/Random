/*
Oyebola Odukoya
TODO: Refactor code to work on robot
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct cell {
    // Boolean values to say if theres a wall or not 1 for true, 0 for false
    int north;
    int east;
    int south;
    int west;

    int value; // Floodfill value of the cell
    int visited; // 0 = has been visited, 1 otherwise
}cell;

struct mouse {
    int facing; // N,E,S,W => 0,1,2,3
    int row;
    int col;
}mouse;

int main(void){
    struct cell maze[7][7]; // Inititalizing the maze
    // Initialize all cell values with 0, this is because C fills w garbage by default
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            maze[i][j].north = 0;
            maze[i][j].east = 0;
            maze[i][j].south = 0;
            maze[i][j].west = 0;
            maze[i][j].value = 0;
            maze[i][j].visited = 0;
        }
    }

    // Filling out the initial flood fill numbers
    for(int row = 0; row < 7; row++){
        for(int col = 0; col < 7; col++){
            maze[row][col].value = abs(3-row) + abs(3-col);
        }
    }

    // Filling out the outer 4 walls
    for(int i = 0; i < 7; i++){ maze[0][i].north = 1;}
    for(int i = 0; i < 7; i++){ maze[6][i].south = 1;}
    for(int i = 0; i < 7; i++){ maze[i][0].west = 1;}
    for(int i = 0; i < 7; i++){ maze[i][6].east = 1;}

    // Filling out the inner maze walls
    maze[0][0].east = 1;
    maze[0][1].west = 1;

    maze[1][0].east = 1;
    maze[1][1].west = 1;

    maze[2][0].east = 1;
    maze[2][1].west = 1;

    maze[3][0].east = 1;
    maze[3][1].west = 1;

    maze[5][0].east = 1;
    maze[5][1].west = 1;

    maze[6][0].east = 1;
    maze[6][1].west = 1;

    maze[3][3].west = 1;
    maze[3][2].east = 1;

    maze[1][6].south = 1;
    maze[2][6].north = 1;

    maze[1][5].south = 1;
    maze[2][5].north = 1;

    maze[6][6].west = 1;
    maze[6][5].east = 1;





    // Initializing the mouse
    struct mouse mice;
    // Start cells, set to bottom left & facing north(This can be changed to any position in the maze and will still work!)
    mice.row = 6;
    mice.col = 0;
    mice.facing = 0;

    // Solve function:
    while(maze[mice.row][mice.col].value != 0){
        struct cell currCell = maze[mice.row][mice.col];
        // Printing out maze
        for(int row = 0; row < 7; row++){
            for(int col = 0; col < 7; col++){
                if(row == mice.row && col == mice.col){
                    switch (mice.facing){
                        case 0: printf("^ ");
                            break;
                        case 1: printf("> ");
                            break;
                        case 2: printf("˅ ");
                            break;
                        case 3: printf("< ");
                            break;
                        default: printf("There's an error somewhere \n");
                    }
                } else {
                    printf("%d ", maze[row][col].value);
                }
            }
            printf("\n");
        }
        printf("Facing %d, row: %d, col %d    \n", mice.facing, mice.row, mice.col);

        // Get the smallest value
        int array[4];
        // printf("N %d, E %d, S %d, W %d  ", currCell.north, currCell.east, currCell.south,currCell.west);

        array[0] = (currCell.north == 1) ? 1000 : maze[mice.row-1][mice.col].value;
        array[1] = (currCell.east == 1) ?  1000 : maze[mice.row][mice.col+1].value;
        array[2] = (currCell.south == 1) ? 1000 : maze[mice.row+1][mice.col].value;
        array[3] = (currCell.west == 1) ?  1000 : maze[mice.row][mice.col-1].value;

        // printf("Array values %d, %d, %d, %d\n", array[0], array[1], array[2], array[3]);
        int smallest = 1000;
        int smallestIndex = mice.facing;
        for(int i = 0; i < 4; i++){
            if(array[i] < smallest){
                smallest = array[i];
                smallestIndex = i;
            }
        }

        // Have I been to this cell before?
        if(currCell.visited == 0){
            // If I have not, Is there a wall around
            if(currCell.north || currCell.east || currCell.south || currCell.west == 1){
                // If there is update the values
                maze[mice.row][mice.col].value = smallest+1;
                currCell.visited = 1;
            }
        }

        // Move to the lowest number
        // If the mice is already facing the lowest number
        if(array[mice.facing] == smallest){
            //move to facing
            switch (mice.facing){
                case 0: mice.row--;
                    break;
                case 1: mice.col++;
                    break;
                case 2: mice.row++;
                    break;
                case 3: mice.col--;
                    break;
                default: printf("There's an error somewhere \n");
            }
        } else {
            // move to smallest and update facing
            switch (smallestIndex){
                case 0: mice.row--; mice.facing = 0;
                    break;
                case 1: mice.col++; mice.facing = 1;
                    break;
                case 2: mice.row++; mice.facing = 2;
                    break;
                case 3: mice.col--; mice.facing = 3;
                    break;
                default: printf("There's an error somewhere \n");
            }
        }
    }

    // Printing out maze
    for(int row = 0; row < 7; row++){
        for(int col = 0; col < 7; col++){
            if(row == mice.row && col == mice.col){
                switch (mice.facing){
                    case 0: printf("^ ");
                        break;
                    case 1: printf("> ");
                        break;
                    case 2: printf("˅ ");
                        break;
                    case 3: printf("< ");
                        break;
                    default: printf("There's an error somewhere \n");
                }
            } else {
                printf("%d ", maze[row][col].value);
            }
        }
        printf("\n");
    }

    printf("Facing %d, row: %d, col %d    \n", mice.facing, mice.row, mice.col);
    printf("Maze complete!!! \n");

    return 0;
}
