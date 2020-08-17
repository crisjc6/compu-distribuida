// listado 3.17 - random shooting para calculo de pi

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double rnd (unsigned int *seed) {
  *seed = (1140671485 * (*seed) + 12820163) % (1 << 24);
  return (( double)(* seed)) / (1 << 24);
}

int main (int argc , char *argv []) {
  if (argc!=2) { printf ("USO: %s <num_shots>\n", argv[0]); exit (1);}
  int num_shots = atoi(argv[1]);   
  unsigned int seeds[omp_get_max_threads ()];
  for (int th = 0; th < omp_get_max_threads (); th ++) seeds[th] = th;
  int num_hits = 0;
  #pragma omp parallel for reduction (+: num_hits)
    for (int shot = 0; shot < num_shots ; shot ++) {
      int thread = omp_get_thread_num ();
      double x = rnd (&seeds[thread]);
      double y = rnd (&seeds[thread]);
      if (x * x + y * y <= 1) num_hits = num_hits + 1;
    }
  printf ("%20.18lf\n", 4.0 * (double)num_hits / (double)num_shots);
  return 0;
}

