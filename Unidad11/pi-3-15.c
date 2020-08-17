// Listado 3.15 - Computing π by integrating √1 − x2 from 0 to 1.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc , char *argv []) {
  if (argc!=2) { printf ("USO: %s <# intervalos>\n", argv[0]); exit (1);}
  int intervals = atoi (argv[1]);
  double integral = 0.0;  double dx = 1.0 / intervals;
  #pragma omp parallel for reduction (+: integral)
  for (int i = 0; i < intervals; i++) {
     double x = i * dx;
     double fx = sqrt (1.0 - x * x);
     integral = integral + fx * dx;
  }
  printf ("PI: %20.18lf\n", 4 * integral);
  return 0;
}

