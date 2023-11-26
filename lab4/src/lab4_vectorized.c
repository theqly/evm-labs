#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "math.h"

#define N 2048

float* init() {
	float* matrix = calloc(N*N, sizeof(float));
	return matrix;
}

float* init_single() {
	float* matrix = calloc(N*N, sizeof(float));
	for(size_t i = 0; i < N; ++i){
		matrix[i*N + i] = 1;
	}
	return matrix;
}

void transpose(const float* matrix, float* res) {
	__asm__ volatile(
			"mov rdi, %0\n\t"
			"mov rsi, %1\n\t"
			"xor rcx, rcx\n\t"
			"xor rdx, rdx\n\t"
			"start_loop:\n\t"
			"movss xmm0, [rdi + rcx*4]\n\t"
			"movss [rsi + rcx], xmm0\n\t"
			"add rcx, 4\n\t"
			"cmp rcx, %2\n\t"
			"jne start_loop\n\t"
			: // output
			: "r" (matrix), "r" (res), "r" (N) // input
			: "xmm0", "rcx", "rdx", "rdi", "rsi" // clobbered
			);
}

void plus(const float* matrix1, const float* matrix2, float* res) {
	__asm__ volatile(
			"mov rdi, %0\n\t"
			"mov rsi, %1\n\t"
			"mov rdx, %3\n\t"
			"xor rcx, rcx\n\t"
			"start_loop:\n\t"
			"movss xmm0, [rdi + rcx*4]\n\t"
			"movss xmm1, [rsi + rcx*4]\n\t"
			"addss xmm0, xmm1\n\t"
			"movss [rdx + rcx*4], xmm0\n\t"
			"add rcx, 4\n\t"
			"cmp rcx, %2\n\t"
			"jne start_loop\n\t"
			: // output
			: "r" (matrix1), "r" (matrix2), "r" (N), "r" (res) // input
			: "xmm0", "xmm1", "rcx", "rdx", "rdi", "rsi" // clobbered
			);
}

void minus(const float* matrix1, const float* matrix2, float* res) {
	__asm__ volatile(
			"mov rdi, %0\n\t"
			"mov rsi, %1\n\t"
			"mov rdx, %3\n\t"
			"xor rcx, rcx\n\t"
			"start_loop:\n\t"
			"movss xmm0, [rdi + rcx*4]\n\t"
			"movss xmm1, [rsi + rcx*4]\n\t"
			"subss xmm0, xmm1\n\t"
			"movss [rdx + rcx*4], xmm0\n\t"
			"add rcx, 4\n\t"
			"cmp rcx, %2\n\t"
			"jne start_loop\n\t"
			: // output
			: "r" (matrix1), "r" (matrix2), "r" (N), "r" (res) // input
			: "xmm0", "xmm1", "rcx", "rdx", "rdi", "rsi" // clobbered
			);
}

void mul(const float* matrix1, const float* matrix2, float* res) {
	__asm__ volatile(
			"mov rdi, %0\n\t"
			"mov rsi, %1\n\t"
			"mov rdx, %3\n\t"
			"xor rcx, rcx\n\t"
			"start_loop:\n\t"
			"xor r8, r8\n\t"
			"start_inner_loop:\n\t"
			"xor r9, r9\n\t"
			"movss xmm0, [rdi + rcx*4]\n\t"
			"movss xmm1, [rsi + r8]\n\t"
			"mulss xmm0, xmm1\n\t"
			"addss xmm0, [rdx + rcx*4]\n\t"
			"movss [rdx + rcx*4], xmm0\n\t"
			"add r8, %4\n\t"
			"add r9, 4\n\t"
			"cmp r9, %2\n\t"
			"jne start_inner_loop\n\t"
			"add rcx, 4\n\t"
			"cmp rcx, %2\n\t"
			"jne start_loop\n\t"
			: // output
			: "r" (matrix1), "r" (matrix2), "r" (N), "r" (res), "r" (N) // input
			: "xmm0", "xmm1", "rcx", "rdx", "rdi", "rsi", "r8", "r9" // clobbered
			);
}

void scalar_mul(const float* matrix, const float scalar, float* res) {
	__asm__ volatile(
			"mov rdi, %0\n\t"
			"mov rsi, %1\n\t"
			"mov rdx, %3\n\t"
			"xor rcx, rcx\n\t"
			"start_loop:\n\t"
			"movss xmm0, [rdi + rcx*4]\n\t"
			"mulss xmm0, %4\n\t"
			"movss [rdx + rcx*4], xmm0\n\t"
			"add rcx, 4\n\t"
			"cmp rcx, %2\n\t"
			"jne start_loop\n\t"
			: // output
			: "r" (matrix), "r" (res), "r" (N), "r" (res), "r" (scalar) // input
			: "xmm0", "rcx", "rdx", "rdi", "rsi" // clobbered
			);
}

float max_row(const float* matrix) {
	float max = 0.0f;
	for(size_t i = 0; i < N; ++i){
		float current = 0.0f;
		for(size_t j = 0; j < N; ++j){
			current += fabs(matrix[i*N + j]);
		}
		if(current > max) max = current;
	}
	return max;
}

float max_collumn(const float* matrix) {
	float* tmp = calloc(N * N, sizeof(float));
	transpose(matrix, tmp);
	const float max = max_row(tmp);
	free(tmp);
	return max;
}


void print(const float* matrix) {
	for(size_t i = 0; i < N; ++i){
		for(size_t j = 0; j < N; ++j){
			printf("%f ", matrix[i*N + j]);
		}
		printf("\n");
	}
	printf("\n");
}

void inverse(const size_t M, float* matrix, float* res){
	float* B = init();
	float* R = init();
	float* I = init_single();
	float* transposed = init();
	transpose(matrix, transposed);
	scalar_mul(transposed, 1.0f / (max_collumn(matrix) * max_row(matrix)), B);
	mul(B, matrix, R);
	minus(I, R, R);
	const size_t size = N * N * sizeof(float);
	memcpy(matrix, R, size);
	for (size_t i = 0; i < M; ++i) {
		plus(res, matrix, res);
		memset(I, 0, size);
		mul(matrix,R, I);
		memcpy(matrix, I, size);
	}
	mul(res, B, res);
	free(B);
	free(R);
	free(transposed);
	free(I);
}

int main() {
	float* matrix = init_single();
	float* res = init_single();
	const size_t start = clock();
	inverse(10, matrix, res);
	printf("was taken %f seconds", (float)(clock() - start) / CLOCKS_PER_SEC);
	free(matrix);
	free(res);
	return 0;
}