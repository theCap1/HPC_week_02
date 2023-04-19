# HPC_week_1
## Homework for the 2nd week

### 2. Bits
#### 2.2 Working Bits
##### 2.2.2 function `instruction_asimd_compute`
function `instruction_asimd_compute` is implemented in class _bits.cpp_

##### 2.2.3 What did we achieve with `instruction_asimd_compute`?
We implemented the bitwise vectorial FMA operation. The execution of this would be much more efficient than implementing it otherwise.

### Pipelining
#### 3.1 `fmul` and `fmla` in the [Arm Neoverse V1 Software Optimization Guide](https://developer.arm.com/documentation/pjdoc466751330-9685/latest/ "Link to Arm Neoverse V1 Software Optimization Guide")
In the following only AArch64 operations and their key metrics will be listed and no SVE instructions.
**`FMUL` key metrics:**
Metric  | Implementation | Meaning
------------- | ------------- | -------------
Pipelines  | V | FP/ASIMD 0/1/2/3 (4 pipelines)
Latency  | 3 | 3 cycles
Throughput  | 4 | 4 cycles

**`FMLA` key metrics:**
Metric  | Implementation | Meaning
------------- | ------------- | -------------
Pipelines  | V | FP/ASIMD 0/1/2/3 (4 pipelines)
Latency  | 4(2) | 4 or 2 cycles with late forwarding of add µOP
Throughput  | 4 | 4 cycles

<details>
    <summary> Output FMA </summary>
<!-- empty line -->

```yaml
[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=4 ./build/micro_asimd 

[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=1 ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 1
peak_asimd_fmadd_sp
  duration: 17.606 seconds
  GFLOPS: 68.1585
peak_asimd_fmadd_dp
  duration: 16.8031 seconds
  GFLOPS: 35.7077
peak_asimd_fmla_sp
  duration: 20.3799 seconds
  GFLOPS: 58.8815
peak_asimd_fmla_dp
  duration: 19.6229 seconds
  GFLOPS: 30.5766
finished ASIMD microbenchmarks

[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=2 ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 2
peak_asimd_fmadd_sp
  duration: 17.6979 seconds
  GFLOPS: 135.61
peak_asimd_fmadd_dp
  duration: 18.1965 seconds
  GFLOPS: 65.9469
peak_asimd_fmla_sp
  duration: 21.9944 seconds
  GFLOPS: 109.119
peak_asimd_fmla_dp
  duration: 21.4417 seconds
  GFLOPS: 55.9658
finished ASIMD microbenchmarks

[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=3 ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 3
peak_asimd_fmadd_sp
  duration: 16.5329 seconds
  GFLOPS: 217.748
peak_asimd_fmadd_dp
  duration: 20.0798 seconds
  GFLOPS: 89.6425
peak_asimd_fmla_sp
  duration: 22.3587 seconds
  GFLOPS: 161.011
peak_asimd_fmla_dp
  duration: 23.3497 seconds
  GFLOPS: 77.0888

  running ASIMD microbenchmarks
  threads: 4
peak_asimd_fmadd_sp
  duration: 15.7861 seconds
  GFLOPS: 304.066
peak_asimd_fmadd_dp
  duration: 18.4593 seconds
  GFLOPS: 130.015
peak_asimd_fmla_sp
  duration: 23.5302 seconds
  GFLOPS: 203.994
peak_asimd_fmla_dp
  duration: 23.8929 seconds
  GFLOPS: 100.448
finished ASIMD microbenchmarks
```

</details>
<!-- empty line -->

</br>

![alt text](n_cpu_n_threads.png "bruder")
*Figure 1: Performance in GFLOPs per threads for FMADD (scalar FMA) and FMLA (vectorial FMA) in single and double precision. Every thread is performed on a separate CPU core.*

