// listado 3.11 - iteraciones dependientes - race conditions

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc , char *argv []) {
  if (argc!=2) { printf ("USO: %s <max>\n", argv[0]); exit (1);}
  int max = atoi(argv[1]);
  int sum = 0;
  #pragma omp parallel for
  for (int i = 1; i <= max; i++)
    #pragma omp critical
    sum = sum + i;
  printf ("%d\n", sum);
  return 0;
}
