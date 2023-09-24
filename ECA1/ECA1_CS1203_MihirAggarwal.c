#include <stdio.h>

// Check whether all the elements in an array are unique
int unique(int ls[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (ls[j] == ls[i]) {
                return 0;
            }
        }
    }
    return 1;
}

// Generate the next position array 
void gen_next(int t[], int n) {
    for (int i = n-1; i > -1; i--) {
        t[i] = (t[i] + 1) % n;
        if (t[i] != 0) {
            break;
        }
    }
}

// Check whether the elements in an array are less than those corresponding elements of another list
int le(int t[], int end[], int n) {
    for (int i = 0; i < n; i++) {
        if (t[i] < end[i]) {
            return 1;
        }
    }
    return 0;
}

// Logic: generate all possible arrays which will denote the position of each corresponding element in our array[1..n]
/* So for example if n = 3, then we want to generate all arrays starting from [0,1,2] to [2,1,0] which are unique. 
   Each element in these generated arrays will signify the position of its corresponding element in [1,2,3]. 
   So, if our generated array is [2,0,1] then it means that 1 goes on the 2nd index, 2 goes on the 0th index, and 3 goes on the 1st index. */
int main() {
    // Take the input from the user
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);

    // Create an array of all numbers from 1 to n
    // Initializing all arrays to size 8 since that's the maximum
    int ls[8], t[8], end[8];
    for (int i=0; i<n; i++) {
        ls[i] = i+1;
        t[i] = 0;
    }

    // Create the largest position array to signify the end of our while loop.
    // So for n=3, this will be [2,1,0]
    for (int i=n-1; i > -1; i--) {
        end[n-i-1] = i;
    }

    while (le(t, end, n) == 1) {
        gen_next(t, n);

        // If our generated position array doesn't have unique elements, generate again
        while (unique(t, n) == 0) {
            gen_next(t, n);
        }

        int ind[8];
        for (int i = 0; i < n; i++) {
            ind[i] = 0;
        }

        // Put the element in position i of our main array at position t[i] (where t is the position array) in ind
        for (int i = 0; i < n; i++) {
            ind[t[i]] = ls[i];
        }

        for (int i = 0; i < n; i++) {
            if (i == n-1) {
                printf("%d", ind[i]);
            } else {
                printf("%d,", ind[i]);
            }
        }
        printf("\n");
    }
}