#include <stdio.h>

void tower_of_hanoi(int n, int start, int end, int temp) {
    // Base case
    if (n == 1) {
        printf("Disk goes from rod %d to rod %d\n", start, end);
        return;
    }

    // Put (n-1) disks onto the temp rod
    tower_of_hanoi(n-1, start, temp, end);
    // Put the largest disk onto the target rod
    tower_of_hanoi(1, start, end, temp);
    // Put (n-1) disks onto the target rod
    tower_of_hanoi(n-1, temp, end, start);
}

int main() {
    int n;
    printf("Enter the number to calculate Tower of Hanoi for: ");
    scanf("%d", &n);
    tower_of_hanoi(n, 1, 2, 3);
}  