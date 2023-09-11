#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    bubblesort(arr, N);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    printf("Time taken: %lf sec.\n", end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec));
    return 0;
}
