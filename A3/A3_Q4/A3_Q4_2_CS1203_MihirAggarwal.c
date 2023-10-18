#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_array(int arr[8][8], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if the current board is safe
int safe(int arr[8][8], int n) {
    int flag = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 8; j++) {
            if (arr[i][j] == 1) {
                for (int k = 0; k < 8; k++) {

                    // Check row
                    if ((k != j) && (arr[i][k] == 1)) {
                        flag = 0;
                        return flag;
                    }

                    // Check column
                    else if ((k != i) && (arr[k][j] == 1)) {
                        flag = 0;
                        return flag;
                    }

                    else {
                        // Check diagonal
                        for (int l = 0; l < 8; l++) {
                            if ((arr[k][l] == 1) && (abs(k-i) == abs(l-j)) && ((k != i) || (l != j))) {
                                flag = 0;
                                return flag;
                            }
                        }
                    }
                }

            }
        }
    }

    return flag;
}

int queens(int arr[800][8][8], int n, int size) {
    if (n == 0) return 1;
    
    // Find the possibilities with 1 less row
    size = queens(arr, n-1, size);

    int t_size = 0;
    int n_arr[800][8][8];

    // Go through all possible queen positions on the current row and check if safe
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 8; j++) {
            int t_arr[8][8];
            for (int k = 0; k < 8; k++) {
                for (int l = 0; l < 8; l++) {
                    t_arr[k][l] = arr[i][k][l];
                }
            }
            t_arr[n-1][j] = 1;
            if (safe(t_arr, n) == 1) {
                if (n == 8) print_array(t_arr, n);
                else {
                    for (int k = 0; k < 8; k++) {
                        for (int l = 0; l < 8; l++) {
                            n_arr[t_size][k][l] = t_arr[k][l];
                        }
                    }
                }
                t_size++;
            }
        }
    }
    for (int i = 0; i < t_size; i++) {
        for (int k = 0; k < 8; k++) {
            for (int l = 0; l < 8; l++) {
                arr[i][k][l] = n_arr[i][k][l];
            }
        }
    }
    size = t_size;
    return size;
}

int main() {
    // 8 queens
    int arr[800][8][8];

    // Initialize an empty board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            arr[0][i][j] = 0;
        }
    }

    printf("1 represents the position of queen\n\n");

    int j = queens(arr, 8, 1);

    printf("Total number of ways: %d\n", j);
    return 0;
}