# HPC_week_1
## Homework for the 2nd week

### 2. Bits
#### 2.2 Working Bits
##### 2.2.2 function `instruction_asimd_compute`
function `instruction_asimd_compute` is implemented in class _bits.cpp_

##### 2.2.3 What did we achieve with `instruction_asimd_compute`?
We implemented the bitwise vectorial FMA operation. The execution of this would be much more efficient than implementing it otherwise.

### 3 Pipelining
#### 3.1 `fmul` and `fmla` in the [Arm Neoverse V1 Software Optimization Guide](https://developer.arm.com/documentation/pjdoc466751330-9685/latest/ "Link to Arm Neoverse V1 Software Optimization Guide")
In the following only AArch64 operations and their key metrics will be listed and no SVE instructions.
**`FMUL` key metrics:**
Metric  | Implementation | Meaning
------------- | ------------- | -------------
Pipelines  | V | FP/ASIMD 0/1/2/3 (4 pipelines)
Latency  | 3 | 3 cycles
Throughput  | 4 | 4 OPs per cycle when fully loaded

**`FMLA` key metrics:**
Metric  | Implementation | Meaning
------------- | ------------- | -------------
Pipelines  | V | FP/ASIMD 0/1/2/3 (4 pipelines)
Latency  | 4(2) | 4 or 2 cycles with late forwarding of add µOP
Throughput  | 4 | 4 OPs per cycle when fully loaded

#### 3.2 Pipeline restrictions
When the workload is bound by the `fmul` latency only two full FP64 OPs (or 4 FP32 OPs) can be executed every three cycles. That means that the GFLOPs for the _ARM Neoverse V1_ with assumed $2,6$GHz can be calculated as followed:

$$
\begin{aligned}
\text{GFLOPs} &= \text{clock frequency} \cdot \frac{\text{(OPs/Instruction)}\cdot \text{pipeline width}}{\text{latency}} \cdot 10^{-9}\\
\Rightarrow \text{GFLOPs} &= 2,6 \cdot \frac{2 \cdot 2}{3} = 3,4
\end{aligned}
$$

However, if my workload is bound by the latency of fmla operations, which has a latency of 4 cycles, the GFLOPS that can be achieved with a single 128-bit FP/ASIMD pipeline would be:

$
\text{GFLOPs} = 2,6 \cdot \frac{2 \cdot 2}{4} = 2,6
$

In the case where late forwarding is possible and the latency of fmla is reduced to 2 cycles, the GFLOPS that can be achieved with a single 128-bit FP/ASIMD pipeline would be:

$
\text{GFLOPs} = 2,6 \cdot \frac{2 \cdot 2}{2} = 5,2
$

In summary, the GFLOPS performance of a single FP/ASIMD pipeline is dependent on the latency of the floating-point operations in the workload, as well as the number of floating-point pipelines available. If the workload is latency-bound, having more pipelines will not significantly improve performance, and it's necessary to optimize the code to reduce the number of floating-point operations or improve data locality to improve performance.

#### 3.3 & 3.4 Benchmark of `fmla` & `fmul` with dependencies

The exercise was to rewrite kernels with FP32 `FMLA` and `FMUL` vector instruction where read-after-write dependence were artificially implemented. In the following you can also expand the text based output with the graphic right beneath:

<details>
    <summary> Output for n threads on n cpu cores </summary>
<!-- empty line -->

```yaml
[sven@scalable pipelines]$ OMP_NUM_THREADS=1 ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 1
latency_src_asimd_fmla_sp
  duration: 231.02 seconds
  GFLOPS: 5.19436
latency_src_asimd_fmul_sp
  duration: 173.265 seconds
  GFLOPS: 6.9258
finished ASIMD microbenchmarks

[sven@scalable pipelines]$ OMP_NUM_THREADS=2 ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 2
latency_src_asimd_fmla_sp
  duration: 231.039 seconds
  GFLOPS: 10.3879
latency_src_asimd_fmul_sp
  duration: 173.278 seconds
  GFLOPS: 13.8506
finished ASIMD microbenchmarks

[sven@scalable pipelines]$ OMP_NUM_THREADS=3 ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 3
latency_src_asimd_fmla_sp
  duration: 231.098 seconds
  GFLOPS: 15.5778
  duration: 173.301 seconds
  GFLOPS: 20.7732

[sven@scalable pipelines]$ OMP_NUM_THREADS=4 ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 4
latency_src_asimd_fmla_sp
  duration: 232.996 seconds
  GFLOPS: 20.6012
latency_src_asimd_fmul_sp
  duration: 174.329 seconds
  GFLOPS: 27.5342
finished ASIMD microbenchmarks

```

</details>
<!-- empty line -->

</br>

As one can easily observe the performance took a big plunge when compared to last week's result. Roughly $\frac{1}{4}$th of the performance is the result when a read-after-write dependence is added to every FMA operation. This can most likely be backtraced to the missing possibility to parallelization. It is only possible to utilize one of four $(\frac{1}{4})$ pipelines which leads to a linearly proportional reduction of the performance.

Also some benchmarks with multiple threads on a single CPU core were performed with the following output.

<details>
    <summary> Output FMA </summary>
<!-- empty line -->

```yaml
[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=1 OMP_PLACES={2} ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 1
latency_src_asimd_fmla_sp
  duration: 231.025 seconds
  GFLOPS: 5.19423
latency_src_asimd_fmul_sp
  duration: 173.268 seconds
  GFLOPS: 6.92569
finished ASIMD microbenchmarks

[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=2 OMP_PLACES={2} ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 2
latency_src_asimd_fmla_sp
  duration: 462.1 seconds
  GFLOPS: 5.19368
latency_src_asimd_fmul_sp
  duration: 346.57 seconds
  GFLOPS: 6.925
finished ASIMD microbenchmarks

[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=3 OMP_PLACES={2} ./build/micro_asimd 


[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=4 OMP_PLACES={2} ./build/micro_asimd 

```

</details>
<!-- empty line -->

</br>

No noticable difference in performance can be observed when running multiple threads on the same CPU core. This behavior is surprizing since there was a noticable improvement of ~3 GFLOPs when executing two threads on the same CPU core instead of one. The assumption was that this was due to marginally more data movement when executing the benchmarks only once on every core. This is obviously not the case, otherwise similar behaviour could be observed this time. 