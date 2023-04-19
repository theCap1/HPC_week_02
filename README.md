# HPC_week_1
##Homework for the 1st week

The textual output of the executable for the micro benchmarks of the given assembly code is the following collapsable section. Visually you can find it right beneath (1-4 threads on different cores):

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

It is visible that we get a linear relationship between the number of threads and the number of operations we can perform in a given time. Double the amout of threads results roughly in a doubling of the performance. This makes it obvious that no addiitional overhead is being created. Since the individual threads do not have to communicate no extra data transfer is needed and the strong increase in computational performance can be explained.

Next we have the output that we get when we spawn the threads on a single core:

<details>
  <summary> Output FMA on single core </summary>

```YAML
[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=1 OMP_PLACES={0} ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 1
peak_asimd_fmadd_sp
  duration: 14.9517 seconds
  GFLOPS: 80.2587
peak_asimd_fmadd_dp
  duration: 15.553 seconds
  GFLOPS: 38.5777
peak_asimd_fmla_sp
  duration: 19.9704 seconds
  GFLOPS: 60.0889
peak_asimd_fmla_dp
  duration: 21.326 seconds
  GFLOPS: 28.1347
finished ASIMD microbenchmarks

[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=2 OMP_PLACES={0} ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 2
peak_asimd_fmadd_sp
  duration: 28.8949 seconds
  GFLOPS: 83.0597
peak_asimd_fmadd_dp
  duration: 28.8989 seconds
  GFLOPS: 41.5241
peak_asimd_fmla_sp
  duration: 38.0936 seconds
  GFLOPS: 63.0028
peak_asimd_fmla_dp
  duration: 38.0931 seconds
  GFLOPS: 31.5018
finished ASIMD microbenchmarks

[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=3 OMP_PLACES={0} ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 3
peak_asimd_fmadd_sp
  duration: 43.4624 seconds
  GFLOPS: 82.8302
peak_asimd_fmadd_dp
  duration: 43.4466 seconds
  GFLOPS: 41.4302
peak_asimd_fmla_sp
  duration: 57.2779 seconds
  GFLOPS: 62.8515
peak_asimd_fmla_dp
  duration: 57.2216 seconds
  GFLOPS: 31.4567
finished ASIMD microbenchmarks

[sven@scalable aarch64_micro]$ OMP_NUM_THREADS=4 OMP_PLACES={0} ./build/micro_asimd 
running ASIMD microbenchmarks
  threads: 4
peak_asimd_fmadd_sp
  duration: 58.1389 seconds
  GFLOPS: 82.5609
peak_asimd_fmadd_dp
  duration: 58.2441 seconds
  GFLOPS: 41.2059
peak_asimd_fmla_sp
  duration: 76.6216 seconds
  GFLOPS: 62.6456
peak_asimd_fmla_dp
  duration: 76.3943 seconds
  GFLOPS: 31.416
finished ASIMD microbenchmarks
```
</details>

</br>

![alt text](1_cpu_n_threads.png "bruder")
*Figure 2: Performance in GFLOPs per threads for FMADD (scalar FMA) and FMLA (vectorial FMA) in single and double precision. Every thread is performed on the same CPU core.*

The results are as expected with a approximately constant performance. The only anomaly is the slight increase from one to two threads. Even though the driver executes one itteration of the benchmark as a dry run to get the benchmark data into the cache there might still be some other data movement when starting the actual benchmark with the time measurements. When the second and all further threads do the same again as the first thread. This additional overhead is already in the cache improving the performance of the overall microbenchmark. This is backed with a very slight decrease in performance for three and four threads due to the averaging.

Also we were supposed to write own kernels with the FMUL instruction with vectorial as well as scalar operation in double precision and single precision. In the following you can also expand the text based output with the graphic right beneath:

<details>
  <summary> FMUL output </summary>

  ```YAML
  [sven@scalable Vectors]$ OMP_NUM_THREADS=1 ./build/micro_asimd 
  running ASIMD microbenchmarks
    threads: 1
  peak_asimd_vmul_sp
    duration: 14.4404 seconds
    GFLOPS: 41.5502
  peak_asimd_vmul_dp
    duration: 14.4401 seconds
    GFLOPS: 20.7755
  peak_asimd_fmul_sp
    duration: 14.44 seconds
    GFLOPS: 41.5513
  peak_asimd_fmul_dp
    duration: 14.4401 seconds
    GFLOPS: 20.7754
  finished ASIMD microbenchmarks
  [sven@scalable Vectors]$ OMP_NUM_THREADS=2 ./build/micro_asimd 
  running ASIMD microbenchmarks
    threads: 2
  peak_asimd_vmul_sp
    duration: 20.0613 seconds
    GFLOPS: 59.8167
  peak_asimd_vmul_dp
    duration: 18.0767 seconds
    GFLOPS: 33.1919
  peak_asimd_fmul_sp
    duration: 14.4408 seconds
    GFLOPS: 83.0977
  peak_asimd_fmul_dp
    duration: 14.4406 seconds
    GFLOPS: 41.5494
  finished ASIMD microbenchmarks
  [sven@scalable Vectors]$ OMP_NUM_THREADS=3 ./build/micro_asimd 
  running ASIMD microbenchmarks
    threads: 3
  peak_asimd_vmul_sp
    duration: 21.2515 seconds
    GFLOPS: 84.6998
  peak_asimd_vmul_dp
    duration: 20.7445 seconds
    GFLOPS: 43.3851
  peak_asimd_fmul_sp
    duration: 15.6133 seconds
    GFLOPS: 115.286
  peak_asimd_fmul_dp
    duration: 16.1814 seconds
    GFLOPS: 55.6194
  finished ASIMD microbenchmarks
  [sven@scalable Vectors]$ OMP_NUM_THREADS=4 ./build/micro_asimd 
  running ASIMD microbenchmarks
    threads: 4
  peak_asimd_vmul_sp

    duration: 22.0588 seconds
    GFLOPS: 108.8
  peak_asimd_vmul_dp
    duration: 21.5653 seconds
    GFLOPS: 55.6448
  peak_asimd_fmul_sp
    duration: 16.9442 seconds
    GFLOPS: 141.642
  peak_asimd_fmul_dp
    duration: 15.8647 seconds
    GFLOPS: 75.6397
  finished ASIMD microbenchmarks
  ```

</details>

</br>

![alt text](FMUL.png "bruder")
*Figure 3: Performance in GFLOPs per threads for FMUL in single and double precision for scalar and vectorial operations. Every thread is performed on a separate CPU core.*

The output of this microbenchmark is reather surprising, because the scalar operations outperform the vector operations. This is unexpected since the Graviton 3 CPUs have dedicated vector processors to accellerate computations with vectorial registers. The reason for this is yet unknown and will hopefull be discussed in the lecture. Maybe there is a mistake in the kernels that has results in this.