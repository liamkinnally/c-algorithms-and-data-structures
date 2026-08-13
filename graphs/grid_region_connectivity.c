#include <stdio.h>

#define MAX_SIZE 1001

char grid[MAX_SIZE][MAX_SIZE];
int region[MAX_SIZE][MAX_SIZE];
int row;
int col;

int rowOffset[] = {-1, 1, 0, 0};
int colOffset[] = {0, 0, 1, -1};

int rowQueue[MAX_SIZE * MAX_SIZE];
int colQueue[MAX_SIZE * MAX_SIZE];

void floodFill(int startRow, int startCol, int regionId) {
    char target = grid[startRow][startCol];
    
    int front = 0;
    int back = 0;
    rowQueue[back] = startRow;
    colQueue[back] = startCol;
    back++;
    region[startRow][startCol] = regionId;
    
    while (front < back) {
        int currRow = rowQueue[front];
        int currCol = colQueue[front];
        front++;
        
        for (int i = 0; i < 4; i++) {
            int newRow = currRow + rowOffset[i];
            int newCol = currCol + colOffset[i];
            
            if (1 <= newRow && row >= newRow && 1 <= newCol && newCol <= col && region[newRow][newCol] == 0 && grid[newRow][newCol] == target) {
                region[newRow][newCol] = regionId;
                rowQueue[back] = newRow;
                colQueue[back] = newCol;
                back++;
            }
        }
    }
}

int main(void) {
    scanf("%d", &row);
    scanf("%d", &col);
    
    for (int i = 1; i <= row; i++) {
        scanf("%s", grid[i] + 1);
    }
    
    int regionId = 0;
    for (int i = 1; i <= row; i++) {
        for(int j = 1; j <= col; j++) {
            if (region[i][j] == 0) {
                regionId++;
                floodFill(i, j, regionId);
            }
        }
    }
    
    int n;
    scanf("%d", &n);
    
    while (n--) {
        int row1;
        int col1;
        int row2;
        int col2;
        scanf("%d", &row1);
        scanf("%d", &col1);
        scanf("%d", &row2);
        scanf("%d", &col2);
        
        if (region[row1][col1] == region[row2][col2]) {
            if (grid[row1][col1] == '0') {
                printf("binary\n");
            } else {
                printf("decimal\n");
            }
        } else {
            printf("neither\n");
        }
    }
    return 0;
}