#include<iostream>
#include<omp.h>
#include<stdlib.h>
using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void bubble(int* arr, int n){
    for(int i= 0; i<n; i++){
        int first = i % 2;

        #pragma omp parallel for shared(arr, first)
        for(int j= first; j<n-1; j+= 2)
        {
            if(arr[j]>arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }

}


int main(){
    int *a, *b, n;

    cout<<"Enter number of elements: ";
    cin>>n;

    a = new int[n];
    b = new int[n]; 

    cout<<"Enter elelments:"<<endl;
    for(int i = 0; i<n; i++){
        cin>>a[i];
        b[i] = a[i];

    }

    double start = omp_get_wtime();
    for(int i=0; i<n; i++){
        for(int j=0; j<n-1-i; j++){
            if(a[j]>a[j+1])
                swap(a[j],a[j+1]);
        }
    }
    double end = omp_get_wtime();

    cout<<"Seqential sort : ";
    for(int i=0; i<n; i++){
        cout<<a[i]<<" ";
    }

    cout<<"\nTime: "<<end-start<<" sec"<<endl;

    start = omp_get_wtime();
    bubble(b, n);
    end = omp_get_wtime();


    cout<<"Parallel sort : ";
    for(int i=0; i<n; i++){
        cout<<b[i]<<" ";
    }
    cout<<"\nTime: "<<end-start<<" sec"<<endl;

    return 0;
}