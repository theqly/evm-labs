#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <ctime>

union ticks{
  unsigned long long t64;
  struct s32 {long th, tl;} t32;
} start, end;

void array_traversal(const uint32_t* array, uint64_t size, uint32_t times){
  uint64_t k = 0;
  for(uint64_t i = 0; i < size * times; ++i) k = array[k];
  if(k == 123) std::cout << "WOW";
}

void sort(uint32_t* array, uint64_t size, uint32_t num_of_fragments, uint32_t offset){
  for(uint64_t i = 0; i < num_of_fragments; ++i){
	for(uint64_t j = 0; j < size / num_of_fragments; ++j){
	  array[offset * i + j] = (i + 1) * offset + j;
	}
  }
  for(uint64_t i = 0; i < size / num_of_fragments; ++i){
	array[offset * (num_of_fragments - 1) + i] = i + 1;
  }

}

uint64_t get_traversal_time(uint32_t* array, uint64_t size){
  uint64_t time = LLONG_MAX;
  array_traversal(array, size, 1);
  for(uint64_t i = 0; i < 5; ++i){
	asm("rdtsc\n":"=a"(start.t32.th),"=d"(start.t32.tl));
	array_traversal(array, size, 10);
	asm("rdtsc\n":"=a"(end.t32.th),"=d"(end.t32.tl));
	time = std::min(time, static_cast<uint64_t>(end.t64 - start.t64)/(size * 10));
  }
  return time;
}

void matrix_mul() {
  auto* matrix1 = (float*)calloc(1024 * 1024, sizeof(float));
  auto* matrix2 = (float*)calloc(1024 * 1024, sizeof(float));
  auto* res = (float*)calloc(1024 * 1024, sizeof(float));
  for(size_t i = 0; i < 1024; ++i){
	for(size_t j = 0; j < 1024; ++j){
	  const size_t index = i*1024 +j;
	  for(size_t k = 0; k < 1024; ++k){
		res[i*1024 + k] += matrix1[index] * matrix2[j*1024 + k];
	  }
	}
  }
  free(matrix1);
  free(matrix2);
  free(res);
}


int main(){

  matrix_mul();

  uint64_t offset = 16 * 1024 * 1024 / sizeof(uint32_t);
  uint64_t size = 16 * 1024 * 1024 / sizeof(uint32_t);

  for(uint32_t fragments = 1; fragments < 33; ++fragments){
	auto* array = new uint32_t[size * 32];
	sort(array, size, fragments, offset);
	std::cout << fragments << " " <<get_traversal_time(array, size) << std::endl;
	delete[] array;
  }

  return 0;
}