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
Throughput  | 4 | 4 cycles

**`FMLA` key metrics:**
Metric  | Implementation | Meaning
------------- | ------------- | -------------
Pipelines  | V | FP/ASIMD 0/1/2/3 (4 pipelines)
Latency  | 4(2) | 4 or 2 cycles with late forwarding of add µOP
Throughput  | 4 | 4 cycles

#### 3.2 Pipeline restrictions
When the workload is bound by the `fmul` latency only two full FP64 OPs (or 4 FP32 OPs) can be executed every three cycles. That means that the GFLOPs for the _ARM Neoverse V1_ with assumed $2,6$GHz can be calculated as followed:

$
\begin{aligned}
\text{GFLOPs} &= \text{clock frequency} \cdot \frac{\text{(OPs/Instruction)}\cdot \text{pipeline width}}{\text{latency}} \cdot 10^{-9}\\
\Rightarrow \text{GFLOPs} &= 2,6 \cdot \frac{2 \cdot 2}{3} = 3,4
\end{aligned}
$

However, if my workload is bound by the latency of fmla operations, which has a latency of 4 cycles, the GFLOPS that can be achieved with a single 128-bit FP/ASIMD pipeline would be:

$
\text{GFLOPs} = 2,6 \cdot \frac{2 \cdot 2}{4} = 2,6
$

In the case where late forwarding is possible and the latency of fmla is reduced to 2 cycles, the GFLOPS that can be achieved with a single 128-bit FP/ASIMD pipeline would be:

$
\text{GFLOPs} = 2,6 \cdot \frac{2 \cdot 2}{2} = 5,2
$

In summary, the GFLOPS performance of a single FP/ASIMD pipeline is dependent on the latency of the floating-point operations in the workload, as well as the number of floating-point pipelines available. If the workload is latency-bound, having more pipelines will not significantly improve performance, and it's necessary to optimize the code to reduce the number of floating-point operations or improve data locality to improve performance.