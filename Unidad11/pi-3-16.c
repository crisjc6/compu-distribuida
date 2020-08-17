// Listado 3.16 - Calculo de pi: √1 − x2 de 0-1 con for non-paralelizable

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc , char *argv []) {
  if (argc!=2) { printf ("USO: %s <# intervalos>\n", argv[0]); exit (1);}
  int intervals = atoi (argv[1]);
  double integral = 0.0;  double dx = 1.0 / intervals;
  double x = 0.0;
  #pragma omp parallel for reduction (+: integral)
  for (int i = 0; i < intervals; i++) {
    double fx = sqrt (1.0 - x * x);
    integral = integral + fx * dx;
    x = x + dx;
  }
  printf ("PI: %20.18lf\n", 4 * integral);
  return 0;
}
