#include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;

void merge(int a[], int i1, int j1, int i2, int j2);

void mergesort_parallel(int arr[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergesort_parallel(arr, left, mid);

            #pragma omp section
            mergesort_parallel(arr, mid + 1, right);
        }

        merge(arr, left, mid, mid + 1, right);
    }
}

void mergesort_sequential(int arr[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        mergesort_sequential(arr, left, mid);
        mergesort_sequential(arr, mid + 1, right);
        merge(arr, left, mid, mid + 1, right);
    }
}

void merge(int arr[], int left1, int right1, int left2, int right2) {
    int temp[1000];
    int i = left1, j = left2, k = 0;

    while (i <= right1 && j <= right2) {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= right1)
        temp[k++] = arr[i++];

    while (j <= right2)
        temp[k++] = arr[j++];

    for (i = left1, j = 0; i <= right2; i++, j++)
        arr[i] = temp[j];
}

int main() {
    int *a, *b, n;
    cout << "\nEnter total number of elements => ";
    cin >> n;

    a = new int[n];
    b = new int[n];

    cout << "\nEnter elements => ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i]; 
    }

    double start, end;

    start = omp_get_wtime();
    mergesort_sequential(b, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nSequential Merge Sort Time: " << end - start << " seconds";

    start = omp_get_wtime();
    mergesort_parallel(a, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nParallel Merge Sort Time: " << end - start << " seconds";

    cout << "\n\nSorted array is => ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;
    return 0;
}