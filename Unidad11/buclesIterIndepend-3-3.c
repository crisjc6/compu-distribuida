// Listado 3.3 - bucles con iteraciones independientes

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc , char *argv []) {
  if (argc!=2) { printf ("USO: %s <max-hilos>\n", argv[0]); exit (1);}
  int max = atoi(argv[1]);
  #pragma omp parallel for
    for (int i = 1; i <= max; i++)
      printf ("%d: %d\n", omp_get_thread_num (), i);
  return 0;
}

