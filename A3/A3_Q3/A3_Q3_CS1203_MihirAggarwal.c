#include <stdio.h>
#include <math.h>

// Merge sort

// Merge the two sorted lists
void merge(int arr[], int arrl[], int arrr[], int size, int sizel, int sizer, int* cc, int* sc) {
    if (size == 0) return;
    int l, r;
    if (sizel != 0) l = arrl[sizel-1];
    else l = -1;
    if (sizer != 0) r = arrr[sizer-1];
    else r = -1;
    (*cc)++;
    (*sc)++;
    if (r > l) {
        arrr[sizer-1] = NULL;
        sizer--;
        arr[size-1] = r;
    }
    else {
        arrl[sizel-1] = NULL;
        sizel--;
        arr[size-1] = l;
    }
    size--;
    merge(arr, arrl, arrr, size, sizel, sizer, cc, sc);
}

void merge_sort(int arr[], int size, int* cc, int* sc) {
    if (size <= 1) return;
    int arrl[size], arrr[size];
    
    // Split the array into 2 - slapping algorithm
    for (int i = 0; i < size; i++) {
        int j = i/2;
        if (i % 2 == 0) arrl[j] = arr[i];
        else arrr[j] = arr[i];
    }

    int s2 = size / 2;
    if (size % 2 == 0) {
        merge_sort(arrl, s2, cc, sc);
        merge_sort(arrr, s2, cc, sc);
        merge(arr, arrl, arrr, size, s2, s2, cc, sc);
    }
    else {
        merge_sort(arrl, (s2) + 1, cc, sc);
        merge_sort(arrr, s2, cc, sc);
        merge(arr, arrl, arrr, size, (s2) + 1, s2, cc, sc);
    }
}

// Quick sort
void quick_sort(int arr[], int size, int* cc, int* sc) {
    if (size <= 1) return;
    int l = arr[size-1];
    arr[size-1] = NULL;
    size--;
    int arrl[size], arrr[size], il = 0, ir = 0;

    // Partition around the pivot
    for (int i = 0; i < size; i++) {
        (*sc)++;
        (*cc)++;
        if (arr[i] <= l) {
            arrl[il] = arr[i];
            il++;
        }
        else {
            arrr[ir] = arr[i];
            ir++;
        }
    }

    quick_sort(arrl, il, cc, sc);
    quick_sort(arrr, ir, cc, sc);

    // Attach the sorted lists to the left and the right of the pivot
    int i;
    for (i = 0; i < il; i++) {
        arr[i] = arrl[i];
    }
    arr[i] = l;
    for (int j = 0; j < ir; j++) {
        i++;
        arr[i] = arrr[j];
    }
}

// Heap sort
void swap(int *xp, int *yp)
{   
    int temp;
    temp = *xp; *xp = *yp; *yp = temp;
}

void heapInsert(int arr[], int n, int elm, int *c1, int *c2)
{
    int i, parent; 

    arr[n] = elm;
    i = n;

    if (i == 0) return;

    while (i != 0){
        parent = (i-1)/2;
        (*c1)++;
        if (arr[parent] < arr[i]){ 
            swap(&arr[i], &arr[parent]);
            (*c2)++;
        }
        else break;
        i = parent;
    }
}

int heapDelete(int arr[], int n, int *c1, int *c2)
{
    int i, left, right, largest, val, flag = 1;

    if (n == 0) return -9999;
    val = arr[0];
    arr[0] = arr[n-1];
    i = 0;

    while (flag == 1){
        flag = 0; largest = i;
        left = 2*i+1; right = 2*i+2;
        (*c1)++;
        if (left <= n-1 && arr[left] > arr[largest]){
            largest = left; flag = 1;
        }
        (*c1)++;
        if (right <= n-1 && arr[right] > arr[largest]){
            largest = right; flag = 1;
        }
        if (flag == 1){
            (*c2)++;
            swap(&arr[i], &arr[largest]); i = largest;
        }
     }
     return val;
}

void heap_sort(int arr[], int n, int* cc, int* sc)
{
    int i, elm;

    for(i = 0; i < n; i++)  
        heapInsert(arr, i, arr[i], cc, sc);

    for(i = n; i > 0; i--){  
    	elm = heapDelete(arr, i, cc, sc);
	    arr[i-1] = elm;
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

    int n;

    int arr[10000], arr2[10000], arr3[10000];
    int comparisonCount = 0, swapCount = 0, comparisonCount2 = 0, swapCount2 = 0, comparisonCount3 = 0, swapCount3 = 0;
    double cc, sc, cc2, sc2, cc3, sc3;

    srand(time(NULL));

    printf("Merge sort\n");
    for (n = 1000; n <= 10000; n = n+1000){
        int k = n;
        cc = 0.0, sc = 0.0;
        for (int t = 0; t < 100; t++){
            for (int i = 0; i < n; i++)
                arr[i] = rand()%1000;

            merge_sort(arr, k, &comparisonCount, &swapCount);
            checkIfSorted(arr, k);
            
            cc += (double) comparisonCount;
            sc += (double) swapCount;
            
            comparisonCount = 0, swapCount = 0;
        }
        printf("n = %5d, %lf %lf\n", n, cc/(n*((log(n)/log(2)))*100.0), sc/(n*((log(n)/log(2)))*100.0));
    }
    printf("\n");

    printf("Quick sort\n");
    for (n = 1000; n <= 10000; n = n+1000){
        int k = n;
        cc2 = 0.0, sc2 = 0.0;
        for (int t = 0; t < 100; t++){
            for (int i = 0; i < n; i++)
                arr2[i] = rand()%1000;

            quick_sort(arr2, k, &comparisonCount2, &swapCount2);
            checkIfSorted(arr2, k);
            
            cc2 += (double) comparisonCount2;
            sc2 += (double) swapCount2;
            
            comparisonCount2 = 0, swapCount2 = 0;
        }
        printf("n = %5d, %lf %lf\n", n, cc2/(n*((log(n)/log(2)))*100.0), sc2/(n*((log(n)/log(2)))*100.0));
    }
    printf("\n");

    printf("Heap sort\n");
    for (n = 1000; n <= 10000; n = n+1000){
        int k = n;
        cc3 = 0.0, sc3 = 0.0;
        for (int t = 0; t < 100; t++){
            for (int i = 0; i < n; i++)
                arr3[i] = rand()%1000;

            heap_sort(arr3, k, &comparisonCount3, &swapCount3);
            checkIfSorted(arr3, k);
            
            cc3 += (double) comparisonCount3;
            sc3 += (double) swapCount3;
            
            comparisonCount3 = 0, swapCount3 = 0;
        }
        printf("n = %5d, %lf %lf\n", n, cc3/(n*((log(n)/log(2)))*100.0), sc3/(n*((log(n)/log(2)))*100.0));
    }
    printf("\n");

    return 0;
}