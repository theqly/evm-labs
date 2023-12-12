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

void direct_sort(uint32_t * array, uint64_t size){
  for(uint64_t i = 0; i < size - 1; ++i){
	array[i] = i + 1;
  }
  array[size - 1] = 0;
}

void reverse_sort(uint32_t* array, uint64_t size){
  for(uint64_t i = size - 1; i > 0; --i){
	array[i] = i - 1;
  }
  array[0] = size - 1;
}

void random_sort(uint32_t* array, uint64_t size){
  std::vector<int> vec(size-1);
  for (int i = 0; i < size-1; ++i) vec[i] = i + 1;
  int oldIndex = 0;
  for (int i = 0; i < size-1; ++i){
	int index = rand() % vec.size();
	int val = vec[index];
	vec.erase(vec.begin() + index);
	array[oldIndex] = val;
	oldIndex = val;
  }
}

uint64_t get_traversal_time(uint32_t* array, uint64_t size){
  uint64_t time = LLONG_MAX;
  array_traversal(array, size, 1);
  for(uint32_t i = 0; i < 5; ++i){
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
  srand(time(nullptr));

  matrix_mul();

  std::ofstream out("../out.txt");

  for(uint64_t size = 256; size <= 2500000; size = static_cast<uint64_t>(size * 1.2)){
	out << size * 4 << " ";
	auto array = new uint32_t[size];
	direct_sort(array, size);
	out << get_traversal_time(array, size) << std::endl;
	delete[] array;
  }

  out << std::endl;

  for(uint64_t size = 256; size <= 2500000; size = static_cast<uint64_t>(size * 1.2)){
	out << size * 4 << " ";
	auto array = new uint32_t[size];
	reverse_sort(array, size);
	out << get_traversal_time(array, size) << std::endl;
	delete[] array;
  }

  out << std::endl;

  for(uint64_t size = 256; size <= 2500000; size = static_cast<uint64_t>(size * 1.2)){
	out << size * 4 << " ";
	auto array = new uint32_t[size];
	random_sort(array, size);
	out << get_traversal_time(array, size) << std::endl;
	delete[] array;
  }

  return 0;
}