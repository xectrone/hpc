#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void merge(int arr[], int left1, int right1, int left2, int right2){
    int temp[1000];
    int i = left1,j = left2,k = 0;

    while(i<=right1 && j<=right2){
        if(arr[i]< arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    };

    while(i<=right1){
       temp[k++] = arr[i++];
    };

    while(j<=right2){
        temp[k++] = arr[j++];
    };

    for(i=left1, j=0; i<= right2; i++,j++)
    {
        arr[i] = temp[j];
    }

}



void sequential_mergesort(int arr[], int left, int right){
    int mid;
    if(left<right){
        mid = (left+right)/2;
        sequential_mergesort(arr, left, mid);
        sequential_mergesort(arr, mid+1, right);
        merge(arr,left, mid, mid+1, right);
    }
}

void parallel_mergesort(int arr[], int left, int right){
    int mid;
    if(left<right){
        mid = (left+right)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallel_mergesort(arr, left, mid);

            #pragma omp section
            parallel_mergesort(arr, mid+1, right);
        }

        merge(arr, left, mid, mid+1, right);
    }
}

int main(){
    int *a, *b, n;

    cout<<"Enter number of elements : ";
    cin>>n;

    a = new int[n];
    b = new int[n];

    cout<<"Enter elements:"<<endl;
    for(int i=0; i<n; i++){
       cin>>a[i];
       b[i] = a[i];
    }

    cout<<"Sequential Merge Sort : "<<endl;
    double start = omp_get_wtime();
    sequential_mergesort(a, 0, n-1);
    double end = omp_get_wtime();
    for(int i = 0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<"\nTime :"<< end-start<<" sec"<<endl;

    cout<<"Parallel Merge Sort : "<<endl;
    start = omp_get_wtime();
    parallel_mergesort(a, 0, n-1);
    end = omp_get_wtime();
    for(int i = 0; i<n; i++){
        cout<<b[i]<<" ";
    }
    cout<<"\nTime :"<< end-start<<" sec"<<endl;

    return 0;
}