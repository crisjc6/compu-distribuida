### Multiplicación de matrices utilizando el paradigma Parallel Loop with OpenMp

### Introducción

La multiplicación de matrices son uno de los principales problemas dentro de la implementación de programas paralelos.
Teniendo en cuenta que de manera secuencial mientras más alto es el número de dimensiones de las matrices son requieren un tiempo de ejecución mayor
La paralelización con OpenMp permite controlar con hilos de cada operación con la multiplicación de matrices 
Ejemplo que se desarrolló para la implementación es de la multiplicación de matrices cuadradas esto se realiza de manera eficiente con OpenMp además se plantea optimizar con la asignación en memoria para poder evitar los misses de cache. Los resultados de rendimiento se presentan en tres archivos
* Multiplicación de matrices secuencial
* Multiplicación de matrices parallel-Loop
* Multiplicación de matrices optimizado el parallel-Loop

### Requisitos 
* C
* OpenMp

### Compilación y Ejecución

run program :
`cc -o matrixMulti  pmp.c -fopenmp -lm`
lm: llamar a la Librería matemática
fopenmp: Llamara a la Librería de openMp

Ejecución:
`./matrixMulti <Number of iterations>`

### Desarrollo

#### Multiplicación secuencial
```c
double sequentialMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension){
	/*
        Multiplicacion secuencial de matrices recibe como entrada 
        las matrices A y B y la matriz donde se almacenara la matrix C
        y la respectiva dimension. y como resultado se optiene la matrix resultante
	*/

	struct timeval t0, t1;
	gettimeofday(&t0, 0);

	/* cabezera */
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			for(int k=0; k<dimension; k++){
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
	/* Piso */

	gettimeofday(&t1, 0);
	double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;

	return elapsed;
}

``` 

#### Multiplación paralela OpenMp

```c
double parallelMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension){
	/*
        Multipliacion paralela entradas las matrices A y B y la matrix C
        la dimension y como resultado se optiene la matriz resultante
	*/

	struct timeval t0, t1;
	gettimeofday(&t0, 0);

	/* cabecera */
	#pragma omp parallel for
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			for(int k=0; k<dimension; k++){
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
	/* Final */

	gettimeofday(&t1, 0);
	double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;

	return elapsed;
}
``` 

#### Optimizacion Multiplicación paralela OpenMp
```c
double optimizedParallelMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension){
	/*
	    Multipliacion paralela entradas las matrices A y B y la matrix C
        la dimension y como resultado se optiene la matriz resultante
        utilizando metodos mas optimos
	*/

	int i, j, k, iOff, jOff;
	TYPE tot;

	struct timeval t0, t1;
	gettimeofday(&t0, 0);

	/* cabecera */
	convert(matrixA, matrixB, dimension);
	#pragma omp parallel shared(matrixC) private(i, j, k, iOff, jOff, tot) num_threads(40)
	{
		#pragma omp for schedule(static)
		for(i=0; i<dimension; i++){
			iOff = i * dimension;
			for(j=0; j<dimension; j++){
				jOff = j * dimension;
				tot = 0;
				for(k=0; k<dimension; k++){
					tot += flatA[iOff + k] * flatB[jOff + k];
				}
				matrixC[i][j] = tot;
			}
		}
	}
	/* final o cola */

	gettimeofday(&t1, 0);
	double elapsed = (t1.tv_sec-t0.tv_sec) * 1.0f + (t1.tv_usec - t0.tv_usec) / 1000000.0f;

	return elapsed;
}
``` 

### Resultados
* Maquina gitpod Virtual
  
> model name      : Intel(R) Xeon(R) CPU @ 2.20GHz

> 8 cpu asignada

> 16 core cpu logicos

> cache size : 56320 KB
  
![image](https://user-images.githubusercontent.com/50051312/88010785-5327fe80-cadb-11ea-9e9b-840d06524f1c.png)

* Maquina fisica 1 
  
> model name	: Intel(R) Core(TM) i5 CPU       M 450  @ 2.40GHz

> 2 core cpu fisicos

> 4 core cpu logicos

> cache size : 3072 KB


![image](https://user-images.githubusercontent.com/50051312/88012293-21189b80-cadf-11ea-8e40-9ec53e149d98.png)


* Maquina fisica 2

> model name      : Intel(R) Core(TM) i5-9600K CPU @ 3.70GHz

> 6 core cpu fisicos

> 0 core cpu logicos

> cache size : 9216 KB


![image](https://user-images.githubusercontent.com/50051312/88013700-abaeca00-cae2-11ea-956d-659a31ee29fd.png)

### Conclusiones
### Recomendaciones
### Futuras acciones

### Referencias
[matrix multiplicacion](https://medium.com/tech-vision/parallel-matrix-multiplication-c-parallel-processing-5e3aadb36f27)
