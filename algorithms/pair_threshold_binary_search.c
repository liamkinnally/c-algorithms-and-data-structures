#include <stdio.h>
#include <stdlib.h>

int n, *row1, *row2;

int validRow(int *row, int limit) {
    int prev = -1;
    for (int i = 0; i < n; i++) {
        if (limit < row[i]) {
            if (prev == -1) {
                prev = row[i];
            } else if (prev == row[i]) {
                prev = -1;
            } else {
                return 0;
            }
        }
    }
    
    return prev == -1;
}

int canLift(int limit) {
    return validRow(row1, limit) && validRow(row2, limit);
}

int main(void) {
    scanf("%d", &n);
    row1 = malloc(n * sizeof(int));
    row2 = malloc(n * sizeof(int));
    
    int maxWeight = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &row1[i]);
        if (row1[i] > maxWeight) {
            maxWeight = row1[i];
        }
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &row2[i]);
        if (row2[i] > maxWeight) {
            maxWeight = row2[i];
        }
    }
    
    int low = 0;
    int high = maxWeight;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (canLift(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    printf("%d\n", low);
    free(row1);
    free(row2);
    
    return 0;
}


