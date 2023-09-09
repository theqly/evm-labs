#include <time.h>
#include <stdlib.h>
#include <stdio.h>

double monte_carlo(long long int N){
  double x, y;
  long long int M = 0;
  for(long long int i = 0; i < N; i++){
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    if(((x*x + y*y) <= 1)){
      M += 1;
    }
  }
  return (double)(4*M)/(double)N;
}

int main(int argc, char* argv[]){
  long long int N;
  scanf("%lld", &N);
  srand(time(NULL));
  double pi = monte_carlo(N);
  printf("pi: %lf", pi);
  return 0;
}