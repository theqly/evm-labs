#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void bubblesort(int* arr, int N){
    for(int i = 0; i < N-1; i++){
        for(int j = 0; j < N-1-i; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
        }
        }
    }
}

void reading(int N, int* arr){
    int num;
    for(int i = 0; i < N; i++){
        scanf("%d", &num);
        arr[i] = num;
    }
}

void print(int N, int* arr){
    for(int i = 0; i < N; i++){
        printf("%d ", arr[i]);
    }
}

int main(){
    int N;
    scanf("%d", &N);
    int* arr = (int*)malloc(sizeof(int) * N);
    reading(N, arr);
    bubblesort(arr, N);
    print(N, arr);
    return 0;
}