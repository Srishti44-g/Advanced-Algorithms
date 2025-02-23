#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 100000  // Maximum array size

// Merge function to combine two sorted halves
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    // Copy remaining elements
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Parallel Merge Sort function
void parallelMergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Parallel execution using OpenMP
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, left, mid);
            
            #pragma omp section
            parallelMergeSort(arr, mid + 1, right);
        }

        merge(arr, left, mid, right);
    }
}

// Driver function
int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[MAX];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Set the number of threads
    omp_set_num_threads(4);

    // Perform parallel merge sort
    parallelMergeSort(arr, 0, n - 1);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
