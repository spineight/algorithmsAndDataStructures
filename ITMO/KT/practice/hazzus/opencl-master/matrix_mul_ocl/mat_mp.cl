// LOC_WORK is tile width and height
// PER_THREAD is elements distributed on thread
// second_size and third_size must divide on LOC_WORK
kernel void mat_mp(global const float* first,
                       global const float* second,
                       global float* result,
                       uint useless,
                       uint second_size,
                       uint third_size) {
    size_t local0 = get_local_id(0);
    size_t local1 = get_local_id(1);
    int i = get_group_id(0) * LOC_WORK + local0;
    int j = get_group_id(1) * LOC_WORK + local1 * PER_THREAD;

    local float local_fst[LOC_WORK][LOC_WORK];
    local float local_snd[LOC_WORK][LOC_WORK];

    float acc[PER_THREAD];
    for (size_t elem = 0; elem < PER_THREAD; ++elem) {
        acc[elem] = 0.0f;
    }

    for (size_t shift = 0; shift < second_size; shift += LOC_WORK) {
        for (size_t elem = 0; elem < PER_THREAD; ++elem) {
        size_t indJ = local1 * PER_THREAD + elem;
            local_fst[local0][indJ]  = first[i * second_size + shift + local1 * PER_THREAD + elem];
            local_snd[indJ][local0] = second[(j + elem) * second_size + shift + local0];
        }
        barrier(CLK_LOCAL_MEM_FENCE);

        for (size_t k = 0; k < LOC_WORK; ++k) {
            for (size_t elem = 0; elem < PER_THREAD; ++elem) {
                acc[elem] += local_fst[local0][k] * local_snd[local1 * PER_THREAD + elem][k];
            }
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    for (size_t elem = 0; elem < PER_THREAD; ++elem) {
        result[i * third_size + j + elem] = acc[elem];
    }
}
