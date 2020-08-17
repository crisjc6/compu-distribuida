// Listado 3.14 - Sum of ints from a given interval using reduction — fast

#include <stdio.h>
 
  int main (int argc , char *argv []) {
  int max; sscanf (argv [1], "%d", &max);
  int sum = 0;
  #pragma omp parallel for reduction (+: sum)
    for (int n = 1; n <= max; n++)
      sum = sum + n;
  printf ("%d\n", sum);
  return 0;
}
