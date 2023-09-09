#include <time.h>
#include <stdlib.h>
#include <stdio.h>

double monte_carlo(int N){
  srand(time(NULL));
  double x, y;
  int M = 0;
  for(int i = 0; i < N; i++){
    x = (double)(0 + rand() % (2 - 0 + 1));
    y = (double)(0 + rand() % (2 - 0 + 1));
    if(((x*x + y*y) < 1)){
      M += 1;
    }
  }
  return (double)(4*M)/N;
}

int main(int argc, char* argv[]){
  int N = argc;
  double pi = monte_carlo(N);
  printf("pi: %lf", pi);
  return 0;
}