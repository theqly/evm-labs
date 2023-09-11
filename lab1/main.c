#include <time.h>
#include <stdlib.h>
#include <stdio.h>


double monte_carlo(long long int N){
  double x, y;
  long long int M = 0;
  for(long long int i = 0; i < N; i++){
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    if(((x*x + y*y) <= 1)) M += 1;
  }
  return (double)(4*M)/(double)N;
}

int main(int argc, char* argv[]){
  long long int N;
  scanf("%lld", &N);
  srand(time(NULL));
  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  double pi = monte_carlo(N);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  printf("Time taken: %lf sec.\n", end.tv_sec-start.tv_sec + 0.000000001*(end.tv_nsec-start.tv_nsec));
  printf("pi: %lf", pi);
  return 0;
}