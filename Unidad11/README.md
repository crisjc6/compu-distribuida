PROGRAMAS OPENMP DEL CAPITULO 3 DEL TEXTO

COMPILAR:
	make -f Makefile.OpenMP


buclesAnidados-3-5.c:
	listado 3.5 del libro - bucles anidados

buclesColapsados-3-6.c:
	listado 3.6 del libro - bucles colapsados

buclesIterIndepend-3-3.c:
	Listado 3.3 - bucles con iteraciones independientes

buclesSeparados-3-7.c:
	listado 3.7 - bucles separados (un pragma paralelo para cada for)

hola-3-1.c:
	Listado 3.1 -/ Programa "hello-world.c" 

interDepend-3-11.c:
	listado 3.11 - iteraciones dependientes - race conditions

pi-3-15.c:
	Listado 3.15 - Computing π by integrating √1 − x2 from 0 to 1.

pi-3-16.c:
	Listado 3.16 - Calculo de pi: √1 − x2 de 0-1 con for non-paralelizable

reduccion-3-14.c:
	Listado 3.14 - Sum of ints from a given interval using reduction — fast

rndShoot-3-17.c:
	listado 3.17 - random shooting para calculo de pi

rndShoot-3-18.c:
	listado 3.18 - otra version de random shooting para calculo de pi

rndShootParSec-3-19.c:
	Listing 3.19 Computing π by random shooting using parallel sections 

runtime-3-20.c:
	Listado 3.20 - Uso de scheduling definido at runtime

tareas-3-24.c:
	Listado 3.24 - summation of integers by using a fixed number of tasks.

test.c:
	test - pragmas anidados no generan hilos paralelos


// Estudiante

comandos levantados en la terminal

```bash
    1  cd Unidad11/
    2  ls
    3  cc -o hello-world  hola-3-1.c -fopenmp -lm
    4  ./hello-world 
    5  export
    6  clear
    7  ./hello-world 
    8  export OMP_NUM_THREADS=8 ./hello-world
    9  export OMP_NUM_THREADS=8; ./hello-world
   10  for i in {1.10}; do ./hello-world ; done
   11  for i in {1..10}; do ./hello-world ; done
   12  echo $OMP_NUM_THREADS 
   13  cc -o hello-world  hola-3-1.c -fopenmp -lm
   14  ./hello-world 
   15  export OMP_NUM_THREADS=8; ./hello-world
   16  history
```
