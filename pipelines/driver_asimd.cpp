#include <cstdint>
#include <cmath>
#include <chrono>
#include <omp.h>
#include <iostream>

extern "C" {
  uint64_t a_latency_src_asimd_fmla_sp( uint64_t i_n_repetitions );
  uint64_t b_latency_src_asimd_fmul_sp( uint64_t i_n_repetitions );
}

int main() {
  std::cout << "running ASIMD microbenchmarks" << std::endl;
  std::chrono::steady_clock::time_point l_tp0, l_tp1;
  std::chrono::duration< double > l_dur;
  double l_g_flops = 0;
  int l_n_threads = 1;
  uint64_t l_n_repetitions = 5000;
  l_n_repetitions *= 1000000;

#pragma omp parallel
  {
   #pragma omp master
   {
     l_n_threads = omp_get_num_threads();
   } 
  }
  std::cout << "  threads: " << l_n_threads << std::endl;


  /*
   * Peak ASIMD FMADD SP
   */
  std::cout << "latency_src_asimd_fmla_sp" << std::endl;
  // dry-run
  a_latency_src_asimd_fmla_sp( 1 );

#pragma omp parallel
  {
#pragma omp barrier
#pragma omp master
    {
      l_tp0 = std::chrono::steady_clock::now();
    }
    l_g_flops = a_latency_src_asimd_fmla_sp( l_n_repetitions );
#pragma omp barrier
#pragma omp master
    {
      l_tp1 = std::chrono::steady_clock::now();
    }
  }

  l_dur = std::chrono::duration_cast< std::chrono::duration< double> >( l_tp1 - l_tp0 );

  std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
  l_g_flops *= l_n_threads;
  l_g_flops *= l_n_repetitions;
  l_g_flops *= 1.0E-9;
  l_g_flops /= l_dur.count();
  std::cout << "  GFLOPS: " << l_g_flops << std::endl;

  /*
   * Peak ASIMD FMADD DP
   */
  std::cout << "latency_src_asimd_fmul_sp" << std::endl;
  // dry-run
  b_latency_src_asimd_fmul_sp( 1 );

#pragma omp parallel
  {
#pragma omp barrier
#pragma omp master
    {
      l_tp0 = std::chrono::steady_clock::now();
    }
    l_g_flops = b_latency_src_asimd_fmul_sp( l_n_repetitions );
#pragma omp barrier
#pragma omp master
    {
      l_tp1 = std::chrono::steady_clock::now();
    }
  }

  l_dur = std::chrono::duration_cast< std::chrono::duration< double> >( l_tp1 - l_tp0 );

  std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
  l_g_flops *= l_n_threads;
  l_g_flops *= l_n_repetitions;
  l_g_flops *= 1.0E-9;
  l_g_flops /= l_dur.count();
  std::cout << "  GFLOPS: " << l_g_flops << std::endl;

  std::cout << "finished ASIMD microbenchmarks" << std::endl;
  return EXIT_SUCCESS;
}
