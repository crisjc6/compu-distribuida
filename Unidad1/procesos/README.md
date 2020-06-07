
fork.c - ilustra el uso de fork

sumSec.c - implementacion secuencial 
	USO: ./sumSec <n>   // Suma de 1 a n

sumPar.c - implementacion paralela
	USO: ./sumPar <n>   // Dos procesos suman de 1 a n

Makefile 
	USO: make	// compila todos los programas


Ejecutar los programas con diferentes valores de n 

Analizar los resultados. Hint: observar el orden de las salidas del programa
Explicar dichas salidas


## Resultado de las ejecuciones 

### Configuración Inicial

1. Verificar la instalacion de gcc 
    * En la linea de comando escribir:


> gcc --version & gcc

![image](https://user-images.githubusercontent.com/50051312/83976112-99bff180-a8bd-11ea-87b4-8e907b954f8c.png)


* con esto se comprueba que el compilador de C esta instalado

2. Ejecutar make para tener todos los programas compilados y listos para ser probados
    * ubicar la terminal a la altura de Makefile para ser ejecutado.

> make

![image](https://user-images.githubusercontent.com/50051312/83976232-616ce300-a8be-11ea-8dac-30012e1d2943.png)

* Con esto todos los programas C serán ejecutados.

3. Comando para ver el arbol de procesos 
> pstree -pl

```typescript


```

### Desarrollo

#### Procesos
#### Programa Fork 'fork.c'
* No se comparten memoria 
* No se comparten las variables
* Siempre el padre espera a que el hijo o los hijos terminen de ejecurar las tareas que fueron asignadas
* Los procesos child en el fork no se finalizan 



1. valor de n = 0
### Evaluación de ejecuciones



#### Hilos
* 



### Preguntas 

Que pasa con los procesos hijos cuando los procesos padres mueren o terminan
Que pasa con los hilos hijos cuando el hilo principal termina
