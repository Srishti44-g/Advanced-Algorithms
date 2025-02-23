#include <stdio.h>
#include <stdlib.h>

#define MAX 10  // Maximum number of variables or constraints

// Function to perform the pivot operation
void pivot(float table[MAX][MAX], int row, int col, int m, int n) {
    float pivotValue = table[row][col];
    
    // Normalize pivot row
    for (int j = 0; j <= n; j++) {
        table[row][j] /= pivotValue;
    }
    
    // Update other rows
    for (int i = 0; i <= m; i++) {
        if (i != row) {
            float factor = table[i][col];
            for (int j = 0; j <= n; j++) {
                table[i][j] -= factor * table[row][j];
            }
        }
    }
}

// Function to find the entering variable (most negative in last row)
int findEnteringVariable(float table[MAX][MAX], int n) {
    int col = -1;
    float minVal = 0;

    for (int j = 0; j < n; j++) {
        if (table[MAX - 1][j] < minVal) {
            minVal = table[MAX - 1][j];
            col = j;
        }
    }
    return col;
}

// Function to find the leaving variable (minimum ratio test)
int findLeavingVariable(float table[MAX][MAX], int col, int m, int n) {
    int row = -1;
    float minRatio = 1e9;  // A very large number

    for (int i = 0; i < m; i++) {
        if (table[i][col] > 0) {
            float ratio = table[i][n] / table[i][col];
            if (ratio < minRatio) {
                minRatio = ratio;
                row = i;
            }
        }
    }
    return row;
}

// Function to perform Simplex Algorithm
void simplex(float table[MAX][MAX], int m, int n) {
    while (1) {
        int col = findEnteringVariable(table, n);
        if (col == -1) break;  // Optimal solution reached

        int row = findLeavingVariable(table, col, m, n);
        if (row == -1) {
            printf("Unbounded solution.\n");
            return;
        }

        pivot(table, row, col, m, n);
    }

    // Print final optimal solution
    printf("Optimal Solution: \n");
    for (int i = 0; i < m; i++) {
        printf("x%d = %.2f\n", i + 1, table[i][n]);
    }
    printf("Max Z = %.2f\n", table[MAX - 1][n]);
}

// Driver function
int main() {
    int m, n;
    float table[MAX][MAX];

    printf("Enter the number of constraints: ");
    scanf("%d", &m);
    printf("Enter the number of variables: ");
    scanf("%d", &n);

    printf("Enter the simplex table (coefficients of constraints and objective function):\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            scanf("%f", &table[i][j]);
        }
    }

    simplex(table, m, n);

    return 0;
}
