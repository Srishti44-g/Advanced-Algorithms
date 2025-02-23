#include <stdio.h>
#include <stdlib.h>

#define MAX 10  // Max constraints/variables

// Function to find the leaving row (most negative in last column)
int findLeavingVariable(float table[MAX][MAX], int m, int n) {
    int row = -1;
    float minVal = 1e9;  // Large number

    for (int i = 0; i < m; i++) {
        if (table[i][n] < minVal) {
            minVal = table[i][n];
            row = i;
        }
    }
    return (minVal < 0) ? row : -1;
}

// Function to find the entering variable (minimum ratio test)
int findEnteringVariable(float table[MAX][MAX], int row, int n) {
    int col = -1;
    float minRatio = 1e9;

    for (int j = 0; j < n; j++) {
        if (table[row][j] < 0) {  // Must be negative
            float ratio = table[MAX - 1][j] / table[row][j];
            if (ratio < minRatio) {
                minRatio = ratio;
                col = j;
            }
        }
    }
    return col;
}

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

// Function to solve LP using Dual Simplex Algorithm
void dualSimplex(float table[MAX][MAX], int m, int n) {
    while (1) {
        int row = findLeavingVariable(table, m, n);
        if (row == -1) break;  // Optimal solution found

        int col = findEnteringVariable(table, row, n);
        if (col == -1) {
            printf("Infeasible solution.\n");
            return;
        }

        pivot(table, row, col, m, n);
    }

    // Print final optimal solution
    printf("Optimal Solution:\n");
    for (int i = 0; i < m; i++) {
        printf("x%d = %.2f\n", i + 1, table[i][n]);
    }
    printf("Max Z = %.2f\n", table[MAX - 1][n]);
}

// Driver function
int main() {
    int m, n;
    float table[MAX][MAX];

    printf("Enter number of constraints: ");
    scanf("%d", &m);
    printf("Enter number of variables: ");
    scanf("%d", &n);

    printf("Enter simplex table (coefficients of constraints and objective function):\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            scanf("%f", &table[i][j]);
        }
    }

    dualSimplex(table, m, n);

    return 0;
}
