Actualizaciones perdidas
------------------------
1) El programa fileconc.c ilustra el problema de "actualizaciones perdidas" por la falta de control de concurrencia en el sistema de archivos de Linux. Dos procesos (padre e hijo) abren el mismo archivo para escribir un texto diferente. El archivo conservara solo uno de los textos, el otro se perdera. Cual de los dos textos, el del padre o el del hijo, es el que se pierde?

Compilacion: cc -o fileconc fileconc.c
Uso: ./fileconc <file-name> <texto-padre> <texto-hijo>
Ejemplo: ./fileconc f1 Father Son

2) El programa fileconc1.c realiza algo similar. El archivo contiene un numero entero (saldo de una cuenta). Los dos procesos que se generan (padre e hijo) abren el archivo, leen el saldo, incrementan el saldo con el monto respectivo y lo vuelven a grabar al archivo. Que sucede con el saldo que queda, finalmente, grabado en el archivo?

Compilacion: cc -o fileconc1 fileconc1.c

Uso: ./fileconc1 <file-name> <monto-padre> <monto-hijo>
Ejemplo: ./fileconc1 f2 1000 2000

Pueden utilizar el script saldo.bash para crear un archivo con el saldo inicial. Por ejemplo, el comando:

./saldo.bash  f2 260
crea el archivo f2 con el saldo inicial 260 (entero de 4 octetos).

3) El programa fileconc2.c implementa control de concurrencia para evitar la perdida de actualizaciones de los saldos. Los dos procesos (padre e hijo) utilizan un "advisory lock" para coordinar el acceso al archivo. La compilacion y uso son similares a los de fileconc1.c.

PREGUNTAS
---------
Que es un "advisory lock"?
Que otros tipos de locks existen, a mas de los "advisory locks"?
Es seguro el control de concurrencia implementado en fileconc2.c?
Es eficiente el control de concurrencia implementado en fileconc2.c?
Seria mejor (mas seguro, mas eficiente) utilizar semaforos?
Seria mejor (mas seguro, mas eficiente) utilizar mutex?
Como implementaria usted control de concurencia en el programa de marras?


## Control de concurrencia
1. advisory lock

Un Advisory Lock es uno de los tipos de File Locking, un mecanismo de exclusión mutua. Estos funcionan solo cuando un  procesoadquiere y libera bloqueos, y se ignoran si un  proceso no tiene conocimiento de los bloqueos.


2. Semáforo:

Estructura de datos solución para sincronización entre procesos que soporta 3 operaciones: -Inicialización-Espera-Señal

3. Mutex:

Mecanismo de sincronización para hilos, los cuales se emplean para obtener acceso exclusivo a recursos compartidos y para serializar el acceso a la sección critica en exclusión mutua. Solo un hilo puede tener acceso simultáneamente al mutex.-Semáforo binario con dos operaciones atómicas: lock, unlock 


### Archivo filecon.c 

``` C
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main (int argc, char *argv[]) {
  int fd;  		// file descriptor
  char fname[100];	// file name
  int pid;		// process ID
  int n;

  if (argc != 4) {
    printf ("USO: %s <file_name> <texto_padre> <texto_hijo>\n", argv[0]); 
    exit (1);
  }
  pid = fork();
  if (pid > 0) { // padre
    if((fd = open(argv[1], O_RDWR | O_CREAT, 00644))<0) {
      printf("P(OPEN)\n");exit(1);}
    if ((n = write (fd, argv[2], strlen (argv[2])))<0) { 
      printf ("P(WRITE)\n"); exit(1);}
    if (close (fd)<0) printf ("P(CLOSE) \n") ;
    exit (0);
  }
  else if (pid == 0) {  // hijo
    if((fd = open(argv[1], O_RDWR | O_CREAT, 00644))<0) {
      printf("H(OPEN)\n");exit(1);}
    if ((n = write (fd, argv[3], strlen (argv[3])))<0) { 
      printf ("H(WRITE)\n"); exit(1);}
    if (close (fd)<0) printf ("H(CLOSE) \n") ;
    exit (0);
  }  
  else {
    printf ("FORK EROOR...\n");
    exit (1);
  }
}
```

![image](https://user-images.githubusercontent.com/50051312/84670857-44529880-aeec-11ea-8ee6-c8fd478cf10b.png)


* Cual de los dos textos, el del padre o el del hijo, es el que se pierde?

Ninguno se pierde unicamente se escribe el primero que llego a recurso compartido en este caso el archivo texto.txt 
se da un problema de race condition procesos compitiendo en carrera por llegar antes que el otro, de manera que el estado y la salida del sistema dependerán de cuál llegó antes 
como se muestra en la imagen. Como estos textos se sobreescriben porque no existe ningun tipo de concurrencia


![image](https://user-images.githubusercontent.com/50051312/84671530-1cb00000-aeed-11ea-8499-7e308d88240b.png)

### Archivo fileconc1.c 

> El programa fileconc1.c realiza algo similar. El archivo contiene un numero entero (saldo de una cuenta).
Los dos procesos que se generan (padre e hijo) abren el archivo, leen el saldo, 
incrementan el saldo con el monto respectivo y lo vuelven a grabar al archivo.
Que sucede con el saldo que queda, finalmente, grabado en el archivo?

![image](https://user-images.githubusercontent.com/50051312/84679242-ab754a80-aef6-11ea-8b31-8fc03865471d.png)

En la ejecucióndel programa fileconc1 de igual forma se puede observar como ocurre un error al calcular el saldo de las cuentas.
Los valores no pueden ser actulizar como el programador lo requier

### Archivo fileconc2.c 

> El programa fileconc2.c implementa control de concurrencia para evitar la perdida de actualizaciones de los saldos. Los dos procesos (padre e hijo) utilizan un "advisory lock" para coordinar el acceso al archivo. La compilacion y uso son similares a los de fileconc1.c.

![image](https://user-images.githubusercontent.com/50051312/84680310-12dfca00-aef8-11ea-8aa9-4b95d04e3f3b.png)


Ahora en el programa fileconc2 implementadocontrol de concurrencia se corrigen los errores al acceder al archivopara el cálculodel saldo.

El  sistema operativo provee concurrenciaal utilizarhilos o procesos sin embargoelsistema operativo no provee el control de concurrencia.En la presente prácticael uso de advisory lock es el másadecuadodebido a quesolo se trabajan con un padre y un hijo. Para el trabajo con más procesos resultaría igual de eficiente, porque este se controla con funciones de permiso y no permiso. El uso de semáforosno tendría mayor eficiencia, porque este es manejado con más funciones sobre cada proceso y no sobre el archivo. Mutex  que  es  una  representación de productor  consumidor tendría  un  resultado igual de eficiente porque se manejaría al igual con funciones de control sobre el archivo.Un  control mediante mutex, con un consumidor que imprima el valor nuevo cada vez que se cambie el valor, y lo bloquee mientras este no sea impreso.