        .text
        .type b_latency_src_asimd_fmul_sp, %function
        .global b_latency_src_asimd_fmul_sp
        /*
         * Microbenchmark measuring achievable performance using fmla instructions.
         * Repeats 30 independent SP ASIMD-FMAs.
         * @param x0 number of repetitions.
         * @return number of flops per iteration.
         */ 
b_latency_src_asimd_fmul_sp:
        // PCS: save required data in SIMD registers to stack
        stp  d8,  d9, [sp, #-16]!
        stp d10, d11, [sp, #-16]!
        stp d12, d13, [sp, #-16]!
        stp d14, d15, [sp, #-16]!

        // set SIMD registers to zero
        eor v0.16b, v0.16b, v0.16b
        eor v1.16b, v1.16b, v1.16b

        // perform the operations
loop_repeat:
        sub x0, x0, #1
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s

        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s

        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s

        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s

        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s

        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s

        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s

        fmul v0.4s, v0.4s, v1.4s
        fmul v0.4s, v0.4s, v1.4s
        
        cbnz x0, loop_repeat

        // PCS: restore SIMD registers
        ldp d14, d15, [sp], #16
        ldp d12, d13, [sp], #16
        ldp d10, d11, [sp], #16
        ldp  d8,  d9, [sp], #16


        // write number of flops to return register
        mov x0, 30*8

        ret
        .size b_latency_src_asimd_fmul_sp, (. - b_latency_src_asimd_fmul_sp)
