### Multipliacción de matrices utilizando el paradigma Parallel Loop with OpenMp

### Introducción

La multiplicaición de matrices son uno de los principales problemas dentro de la implementacion de programas paralelos.
Teniendo en cuenta que de manera secuencial mientras mas alto es el numero de dimenciones de las matrices son requieren un timpo de ejecucion mayor
La paralelizacion con OpenMp permite controlar con hilos de cada operacion con la multiplicaición de matrices 
Ejemplo que se desarrollo para la implementacion es de la multiplicacion de matrices cuadradas esto se realiza de maenra eficiente con OpenMp ademans se plantea optimizar con la asignacion en 
memoria para poder evitar los misses de cache. Los resultados de rendimiento se prensetan en tres archivos
* Multiplicación de matrices secuencial
* Multiplicación de matrices parallel-Loop
* Multiplicación de matrices optimizado el parallel-Loop

### Compilación y Ejecución

run program :
`cc -o matrixMulti  pmp.c -fopenmp -lm`
lm: llamar a la libreria matemática
fopenmp: Llamara a la libreria de openMp

Ejecución:
`./matrixMulti <Number of iterations>`

### Desarrollo

* Maquina gitpod Virtual
  
model name      : Intel(R) Xeon(R) CPU @ 2.20GHz
8 core cpu fisicos
16 core cpu logicos
cache size : 56320 KB
  
![image](https://user-images.githubusercontent.com/50051312/88010785-5327fe80-cadb-11ea-9e9b-840d06524f1c.png)

* Maquina fisica 1 
  
model name	: Intel(R) Core(TM) i5 CPU       M 450  @ 2.40GHz
2 core cpu fisicos
4 core cpu logicos
cache size : 3072 KB


![image](https://user-images.githubusercontent.com/50051312/88012293-21189b80-cadf-11ea-8e40-9ec53e149d98.png)


* Maquina fisica 2
model name      : Intel(R) Core(TM) i5-9600K CPU @ 3.70GHz
6 core cpu fisicos
0 core cpu logicos
cache size : 9216 KB


![image](https://user-images.githubusercontent.com/50051312/88013700-abaeca00-cae2-11ea-956d-659a31ee29fd.png)


### Análisis
### Conclusiones
### Recomendaciones
### Futuras acciones

### Referencias
[matrix multiplicacion](https://medium.com/tech-vision/parallel-matrix-multiplication-c-parallel-processing-5e3aadb36f27)
