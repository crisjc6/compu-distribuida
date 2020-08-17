// listado 3.7 del libro - bucles separados (un pragma paralelo para cada for)

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc , char *argv []) {
  if (argc!=2) { printf ("USO: %s <max-hilos>\n", argv[0]); exit (1);}
  int max = atoi(argv[1]);
  //omp_set_nested (1);
  #pragma omp parallel for
  for (int i = 1; i <= max; i++) {
    #pragma omp parallel for
    for (int j = 1; j <= max; j++) {
      printf ("%d: (%d,%d)\n", omp_get_thread_num (), i, j);
    }
  }
  return 0;
}
