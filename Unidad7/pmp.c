#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <omp.h>
#include <math.h>

typedef double TYPE;
#define MAX_DIM 1000*1000
#define MAX_VAL 10
#define MIN_VAL 1

// Metodos genericos
TYPE** randomSquareMatrix(int dimension);
TYPE** zeroSquareMatrix(int dimension);
void displaySquareMatrix(TYPE** matrix, int dimension);
void convert(TYPE** matrixA, TYPE** matrixB, int dimension);

// Metodos de multiplicacion de matrices
double sequentialMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension);
double parallelMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension);
double optimizedParallelMultiply(TYPE** matrixA, TYPE** matrixB, TYPE** matrixC, int dimension);

// Prueba de las multiplicaciones
void sequentialMultiplyTest(int dimension, int iterations);
void parallelMultiplyTest(int dimension, int iterations);
void optimizedParallelMultiplyTest(int dimension, int iterations);

//1 Matriz dimensional en la pila
TYPE flatA[MAX_DIM];
TYPE flatB[MAX_DIM];

// Verificiacion de la multiplicacion
void verifyMultiplication(TYPE** matrixA, TYPE** matrixB, TYPE** result, int dimension);

int main(int argc, char* argv[]){
	int iterations = strtol(argv[1], NULL, 10);

	// Generacion de archivos de reporte
	// Creacion de log para el sucuencial
	FILE* fp;
	fp = fopen("multi-secuencial.txt", "w+");
	fclose(fp);

	// Creacion de log para multipliacion paralela
	fp = fopen("paralel-multi.txt", "w+");
	fclose(fp);

	// Creacion de log para multiplicaicon de matrices optimizada
	fp = fopen("optimi-multi.txt", "w+");
	fclose(fp);

	for(int dimension=200; dimension<=1000; dimension+=200){
		optimizedParallelMultiplyTest(dimension, iterations);
	}

	for(int dimension=200; dimension<=1000; dimension+=200){
		parallelMultiplyTest(dimension, iterations);
	}

	for(int dimension=200; dimension<=1000; dimension+=200){
		sequentialMultiplyTest(dimension, iterations);
	}

	return 0;
}

TYPE** randomSquareMatrix(int dimension){
	/*
		Generar una matriz de TIPO aleatorio esta son matrices cuadradas.
	*/

	TYPE** matrix = malloc(dimension * sizeof(TYPE*));

	for(int i=0; i<dimension; i++){
		matrix[i] = malloc(dimension * sizeof(TYPE));
	}

	//Random seed
	srandom(time(0)+clock()+random());

    // ya se utiliza OpenMp para reducir el tiempo de creacion
	#pragma omp parallel for
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			matrix[i][j] = rand() % MAX_VAL + MIN_VAL;
		}
	}

	return matrix;
}

TYPE** zeroSquareMatrix(int dimension){
	/*
		generar dos matrices dimencionales con zeros
	*/

	TYPE** matrix = malloc(dimension * sizeof(TYPE*));

	for(int i=0; i<dimension; i++){
		matrix[i] = malloc(dimension * sizeof(TYPE));
	}

	//Random seed
	srandom(time(0)+clock()+random());
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			matrix[i][j] = 0;
		}
	}

	return matrix;
}

void displaySquareMatrix(TYPE** matrix, int dimension){
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			printf("%f\t", matrix[i][j]);
		}
		printf("\n");
	}
}

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

void convert(TYPE** matrixA, TYPE** matrixB, int dimension){
	#pragma omp parallel for
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			flatA[i * dimension + j] = matrixA[i][j];
			flatB[j * dimension + i] = matrixB[i][j];
		}
	}
}

void verifyMultiplication(TYPE** matrixA, TYPE** matrixB, TYPE** result, int dimension){
	/*
		Verificacion del resultado de la multiplicación
	*/
	printf("Verificando el resultado\n");
	printf("----------------\n");
	TYPE tot;
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			tot = 0;
			for(int k=0; k<dimension; k++){
				tot += matrixA[i][k] * matrixB[k][j];
			}
			if(tot != result[i][j]){
				printf("Resultado incorrecto!\n");
				return;
			}
		}
	}
	printf("Resultado incorrecto\n");

}

void sequentialMultiplyTest(int dimension, int iterations){
	FILE* fp;
	fp = fopen("multi-secuencial.txt", "a+");

	// Console write
	printf("----------------------------------\n");
	printf("Prueba : Multipliacion secuencial        \n");
	printf("----------------------------------\n");
	printf("Dimension : %d\n", dimension);
	printf("..................................\n");
	
	// File write
	fprintf(fp, "----------------------------------\n");
	fprintf(fp, "Prueba : Multipliacion secuencial        \n");
	fprintf(fp, "----------------------------------\n");
	fprintf(fp, "Dimension : %d\n", dimension);
	fprintf(fp, "..................................\n");

	double* opmLatency = malloc(iterations * sizeof(double));
	TYPE** matrixA = randomSquareMatrix(dimension);
	TYPE** matrixB = randomSquareMatrix(dimension);
	
	// Iteracion y rendimiento
	for(int i=0; i<iterations; i++){
		TYPE** matrixResult = zeroSquareMatrix(dimension);
		opmLatency[i] = sequentialMultiply(matrixA, matrixB, matrixResult, dimension);
		free(matrixResult);

		// consola
		printf("%d.\t%f\n", i+1, opmLatency[i]);

		// archivo
		fprintf(fp, "%d.\t%f\n", i+1, opmLatency[i]);
	}

	// consola
	printf("\n");
	printf("----------------------------------\n");
	printf("Análisis              \n");
	printf("----------------------------------\n");

	// archivo
	fprintf(fp, "\n");
	fprintf(fp, "----------------------------------\n");
	fprintf(fp, "Análisis              \n");
	fprintf(fp, "----------------------------------\n");

	double sum = 0.0;
	double sumSquared = 0.0;

	// Análisis estadistico
	for(int i=0; i<iterations; i++){
		sum += opmLatency[i];
		sumSquared += pow(opmLatency[i], 2.0);
	}

	double mean = sum / iterations;
	double squareMean = sumSquared / iterations;
	double standardDeviation = sqrt(squareMean - pow(mean, 2.0));

	// Console
	printf("Media               : %f\n", mean);
	printf("Desviacion Estandar : %f\n", standardDeviation);
	printf("----------------------------------\n");

	//File write
	fprintf(fp, "Media               : %f\n", mean);
	fprintf(fp, "Desviacion Estandar : %f\n", standardDeviation);
	fprintf(fp, "----------------------------------\n");

	// Releasing memory
	fclose(fp);
	free(opmLatency);
	free(matrixA);
	free(matrixB);
}

void parallelMultiplyTest(int dimension, int iterations){
	FILE* fp;
	fp = fopen("paralel-multi.txt", "a+");

	// Console write
	printf("----------------------------------\n");
	printf("Prueba : Multiplicacion paralela          \n");
	printf("----------------------------------\n");
	printf("Dimension : %d\n", dimension);
	printf("..................................\n");
	
	// File write
	fprintf(fp, "----------------------------------\n");
	fprintf(fp, "Prueba : Multiplicacion paralela          \n");
	fprintf(fp, "----------------------------------\n");
	fprintf(fp, "Dimension : %d\n", dimension);
	fprintf(fp, "..................................\n");

	double* opmLatency = malloc(iterations * sizeof(double));
	TYPE** matrixA = randomSquareMatrix(dimension);
	TYPE** matrixB = randomSquareMatrix(dimension);
	
	// Iterate and measure performance
	for(int i=0; i<iterations; i++){
		TYPE** matrixResult = zeroSquareMatrix(dimension);
		opmLatency[i] = parallelMultiply(matrixA, matrixB, matrixResult, dimension);
		free(matrixResult);

		// Console write
		printf("%d.\t%f\n", i+1, opmLatency[i]);

		// File write
		fprintf(fp, "%d.\t%f\n", i+1, opmLatency[i]);
	}

	// Console write
	printf("\n");
	printf("----------------------------------\n");
	printf("Análisis              \n");
	printf("----------------------------------\n");

	// File write
	fprintf(fp, "\n");
	fprintf(fp, "----------------------------------\n");
	fprintf(fp, "Análisis              \n");
	fprintf(fp, "----------------------------------\n");

	double sum = 0.0;
	double sumSquared = 0.0;

	// Análisis estadistico
	for(int i=0; i<iterations; i++){
		sum += opmLatency[i];
		sumSquared += pow(opmLatency[i], 2.0);
	}

	double mean = sum / iterations;
	double squareMean = sumSquared / iterations;
	double standardDeviation = sqrt(squareMean - pow(mean, 2.0));

	// Console write
	printf("Media               : %f\n", mean);
	printf("Desviacion Estandar : %f\n", standardDeviation);
	printf("----------------------------------\n");

	//File write
	fprintf(fp, "Media               : %f\n", mean);
	fprintf(fp, "Desviacion Estandar : %f\n", standardDeviation);
	fprintf(fp, "----------------------------------\n");

	// liberar memoria
	fclose(fp);
	free(opmLatency);
	free(matrixA);
	free(matrixB);
}

void optimizedParallelMultiplyTest(int dimension, int iterations){
	FILE* fp;
	fp = fopen("optimi-multi.txt", "a+");

	// Console write
	printf("----------------------------------\n");
	printf("Prueba : Multiplicacion paralela optimizada\n");
	printf("----------------------------------\n");
	printf("Dimension : %d\n", dimension);
	printf("..................................\n");
	
	// File write
	fprintf(fp, "----------------------------------\n");
	fprintf(fp, "Prueba : Multiplicacion paralela optimizada\n");
	fprintf(fp, "----------------------------------\n");
	fprintf(fp, "Dimension : %d\n", dimension);
	fprintf(fp, "..................................\n");

	double* opmLatency = malloc(iterations * sizeof(double));
	TYPE** matrixA = randomSquareMatrix(dimension);
	TYPE** matrixB = randomSquareMatrix(dimension);
	
	// iteracion y medicion de rendimiento
	for(int i=0; i<iterations; i++){
		TYPE** matrixResult = zeroSquareMatrix(dimension);
		opmLatency[i] = optimizedParallelMultiply(matrixA, matrixB, matrixResult, dimension);
		free(matrixResult);

		// Console write
		printf("%d.\t%f\n", i+1, opmLatency[i]);

		// File write
		fprintf(fp, "%d.\t%f\n", i+1, opmLatency[i]);
	}

	// Console write
	printf("\n");
	printf("----------------------------------\n");
	printf("Análisis de medidas              \n");
	printf("----------------------------------\n");

	// File write
	fprintf(fp, "\n");
	fprintf(fp, "----------------------------------\n");
	fprintf(fp, "Análisis de medidas            \n");
	fprintf(fp, "----------------------------------\n");

	double sum = 0.0;
	double sumSquared = 0.0;

	// Análisis estadistico
	for(int i=0; i<iterations; i++){
		sum += opmLatency[i];
		sumSquared += pow(opmLatency[i], 2.0);
	}

	double mean = sum / iterations;
	double squareMean = sumSquared / iterations;
	double standardDeviation = sqrt(squareMean - pow(mean, 2.0));

	// Console write
	printf("Media               : %f\n", mean);
	printf("Desviacion estandar : %f\n", standardDeviation);
	printf("----------------------------------\n");

	//File write
	fprintf(fp, "Media               : %f\n", mean);
	fprintf(fp, "Desviacion estandar : %f\n", standardDeviation);
	fprintf(fp, "----------------------------------\n");

	// liberacion de memoria
	fclose(fp);
	free(opmLatency);
	free(matrixA);
	free(matrixB);
}