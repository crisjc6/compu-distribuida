// Listado 3.24 - summation of integers by using a fixed number of tasks.

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc , char *argv []) {
  if (argc!=2) {printf ("USO: %s <n> <#tareas>\n", argv[0]); exit (1);}
  int max= atoi(argv[1]);
  int tasks= atoi(argv[2]);
  if (max % tasks != 0) return 1;
  int sum = 0;
  #pragma omp parallel
  {
    #pragma omp single
      for (int t = 0; t < tasks; t++) {
        #pragma omp task
        {
          int local_sum = 0;
          int lo = (max / tasks) * (t + 0) + 1;
          int hi = (max / tasks) * (t + 1) + 0;
          // printf ("%d: %d..%d\n", omp_get_thread_num (), lo, hi);
          for (int i = lo; i <= hi; i++)
            local_sum = local_sum + i;
          #pragma omp atomic
          sum = sum + local_sum;
        }
      }
  }
  printf ("%d\n", sum);
  return 0;
}

