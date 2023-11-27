

float* inverse(const size_t M, float* matrix){
    float* tmp = calloc();
    matrix I(_size);
    matrix B = tmp.transpose() * (1.0f / (tmp.max_collumn() * tmp.max_row()));
    matrix R = I - (B * (*this));
    tmp = I;
    for (size_t i = 0; i < M; ++i) {
        tmp = tmp + R;
        R = R * R;
    }
    tmp = tmp * B;
    return tmp;
}

