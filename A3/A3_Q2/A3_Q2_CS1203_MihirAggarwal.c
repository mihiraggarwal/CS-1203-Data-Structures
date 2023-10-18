#include <stdio.h>

int n;

// Insertion Sort
void insert(int l, int arr[], int size, int* cc, int* sc) {
    int i = 0;
    int t = size;
    while ((arr[i] < l) && (i < size)) {
        (*cc)++;
        i++;
    }
    while (t > i) {
        (*cc)++;
        (*sc)++;
        arr[t] = arr[t - 1];
        t--;
    }
    arr[i] = l;
}

void insertion_sort(int arr[], int size, int* cc, int *sc) {
    if (size <= 1) return;

    int l = arr[size-1];
    arr[size-1] = NULL;

    insertion_sort(arr, size - 1, cc, sc);
    insert(l, arr, size - 1, cc, sc);
}

// Bubble sort  
void swap(int *xp, int *yp)
{
    int temp;
    temp = *xp; *xp = *yp; *yp = temp;
}

void bubble_sort(int arr[], int n, int* comparisonCnt, int* swapCnt)
{
    int i, j, flag;

    for (i = 0; i < n - 1; i++) {
        flag = 0;
        for (j = 0; j < n - i - 1; j++) {
            (*comparisonCnt)++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                flag = 1;
                (*swapCnt)++;
            }
        }
        if (flag == 0)
            break;
    }
}

// Common
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
}

void checkIfSorted(int arr[], int size){
    int i;
    for (i = 0; i < size-1; i++)
        if (arr[i] > arr[i+1]){
            printf("Error in sorting\n");
            exit(0);
        }
}

int main() {
    int arr[10000], arr2[10000];
    int comparisonCount = 0, swapCount = 0, comparisonCount2 = 0, swapCount2 = 0;
    double cc, sc, cc2, sc2;

    srand(time(NULL));

    printf("Insertion sort\n");
    for (n = 1000; n <= 10000; n = n+1000){
        int k = n;
        cc = 0.0, sc = 0.0;
        for (int t = 0; t < 100; t++){
            for (int i = 0; i < n; i++)
                arr[i] = rand()%1000;

            insertion_sort(arr, k, &comparisonCount, &swapCount);
            checkIfSorted(arr, k);
            
            cc += (double) comparisonCount;
            sc += (double) swapCount;
            
            comparisonCount = 0, swapCount = 0;
        }
        printf("n = %5d, %lf %lf\n", n, cc/((n*n)*100.0), sc/((n*n)*100.0));
    }
    printf("\n");

    printf("Bubble sort\n");
    for (n = 1000; n <= 10000; n = n+1000){
        int k = n;
        cc2 = 0.0, sc2 = 0.0;
        for (int t = 0; t < 100; t++){
            for (int i = 0; i < n; i++)
                arr2[i] = rand()%1000;

            bubble_sort(arr2, k, &comparisonCount2, &swapCount2);
            checkIfSorted(arr2, k);

            cc2 += (double) comparisonCount2;
            sc2 += (double) swapCount2;

            comparisonCount2 = 0, swapCount2 = 0;
        }
        printf("n = %5d, %lf %lf\n", n, cc2/((n*n)*100.0), sc2/((n*n)*100.0));
    }
    return 0;
}
