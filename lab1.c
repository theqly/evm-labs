#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void bubblesort(int* arr, long long int N){
    for(long long int i = 0; i < N-1; i++){
        for(long long int j = 0; j < N-1-i; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
        }
        }
    }
}

void filling(long long int N, int* arr){
    int num;
    for(long long int i = 0; i < N; i++){
        arr[i] = rand() % 500000 + 1000000;
    }
}

int main(){
    long long int N;
    scanf("%lld", &N);
    int* arr = (int*)malloc(sizeof(long long int) * N);
    filling(N, arr);
    bubblesort(arr, N);
    return 0;
}
