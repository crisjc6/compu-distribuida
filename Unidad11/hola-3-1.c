// Listado 3.1 -/ Programa "hello-world.c" 

#include <stdio.h>
#include <omp.h>
int main () {
   printf ("Hello , world:");
   #pragma omp parallel num_threads(3)
       printf (" %d", omp_get_thread_num ());
   printf ("\n");
   return 0;
}

