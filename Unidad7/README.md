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
 
### Desarrollo

run program :
`cc -o matrixMulti  pmp.c -fopenmp -lm`
lm: llamar a la libreria matemática
fopenmp: Llamara a la libreria de openMp

Ejecución:
`./matrixMulti <Number of iterations>`


### Análisis
### Conclusiones
### Recomendaciones
### Futuras acciones

### Referencias
[matrix multiplicacion](https://medium.com/tech-vision/parallel-matrix-multiplication-c-parallel-processing-5e3aadb36f27)
