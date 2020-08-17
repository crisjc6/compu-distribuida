// Listado 3.20 - Uso de scheduling definido at runtime

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>

int main (int argc , char *argv []) {
  if (argc!=2) { printf ("USO: %s <max-hilos>\n", argv[0]); exit (1);}
  int max = atoi (argv[1]);
  long int sum = 0;
  #pragma omp parallel for reduction (+: sum) schedule(runtime)
  for (int i = 1; i <= max; i++) {
    printf ("%2d @ %d\n", i, omp_get_thread_num ());
    sleep (i < 4 ? i + 1 : 1);
    sum = sum + i;
  }
  printf ("%ld\n", sum);
  return 0;
}
