// LOC_WORK is elements per local group
// UBOUND is just log2(LOC_WORK) for not computing it in device
kernel void prefix_sum(global const float *array,
                       global float *result,
                       uint n) {

    const uint id = get_local_id(0);
    const uint chunks = n / LOC_WORK;
    const uint LOC_WORK_MIN_ONE = LOC_WORK - 1;

    local float odd[LOC_WORK];
    local float even[LOC_WORK];

    float accum = 0.0f;

    local float* result_src = even;
    if (UBOUND & 1) {
        result_src = odd;
    }

    for (uint chunk = 0; chunk < chunks; chunk++){
        uint speed = chunk * LOC_WORK + id;

        even[id] = array[speed];

        barrier(CLK_LOCAL_MEM_FENCE);

        uint max_id = 1;
        for (uint i = 0; i < UBOUND; i++) {
            local float* src = even;
            local float* dst = odd;

            if (i & 1) {
                local float* tmp = src;
                src = dst;
                dst = tmp;
            }

            dst[id] = src[id] + ((id < max_id) ? 0.0 : src[id - max_id]);

            max_id <<= 1;
            barrier(CLK_LOCAL_MEM_FENCE);
        }

        result[speed] = accum;
        result[speed] += result_src[id];
        accum += result_src[LOC_WORK_MIN_ONE];

        barrier(CLK_LOCAL_MEM_FENCE);
    }
}
