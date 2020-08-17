// Listing 3.19 Computing π by random shooting using parallel sections 

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
  int num_hits = 0;
  #pragma omp parallel reduction (+: num_hits)
  {
    unsigned int seed = omp_get_thread_num ();
    int loc_shots = (num_shots / omp_get_num_threads ()) +
    (( num_shots % omp_get_num_threads () > omp_get_thread_num ()) ? 1 : 0);
    while (loc_shots-- > 0) {
      double x = rnd (&seed);
      double y = rnd (&seed);
      if (x * x + y * y <= 1) num_hits = num_hits + 1;
    }
  }
  double pi = 4.0 * (double)num_hits / (double)num_shots;
  printf ("%lf\n", pi);
  return 0;
}
