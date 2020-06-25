## Linux Scheduler simulation


LinSched es un simulador de código abierto que en la actualidad  en los servidor de git de google,  Que le permite simular como se manejan la tareas multitask.
Simula el schedule de linux a nivel de usuario como se da el funcionamiento de las politicas de scheduling. ya que medir esta eficacia de las politicas  de shceduling no es tareas facil en linux.

El simulador crear un conjunto de API que permite evidenciar el comportamiento, trabajando asi sobre el kernel original.

#### Link repositorio del simulador
> git clone https://kernel.googlesource.com/pub/scm/linux/kernel/git/pjt/linsched

Desde la versión 2.6.23 de linux el planificador de tareas fue reemplazado por CFS completely Fair Scheduler el 80% del diseño de CFS modela un procesador multi tarea, con enfoque en programación paralela. Este utiliza colas basadas en el tiempo.
Las políticas de scheduling
Con la técnica de tiempo compartido lo que hace es asignar un quantum de tiempo para ejecutarse en el procesador
el  scheduling se ejecuta  acorde a un ranking de prioridades 
Existen 2 tipos de prioridades las estaticas y la dinámicas.
**Estática**: es asignada cuando el proceso es creado. real time tiene 0-99
SCHED_FIFO
SCHED_RR
los normales utilizan SCHED_OTHER
El rango de las prioridades dinámicas estan entre 100 a 140.
Las tareas que se tiene son 
* normales
* en batch
* real time
**LinSched**  para modelar estos escenarios de tareas. la **API** permite la creación de tareas normales con la política SCHED_NORMAL, batch con la política SCHED_BATCH, o de tiempo real. 
SCHED_FIFO, SCHED_RR, 

Esta se pueden probar en
"uniprocessor" "dual_cpu" "dual_cpu_mc" "quad_cpu" "quad_cpu_mc" "quad_cpu_dual_socket" "quad_cpu_quad_socket" "hex_cpu_dual_socket_smt"

``` C
void test_new_test(int argc, char **argv)
{
  int count = 0 , mask;
  struct linsched_topology topo;
  int type = parse_topology(argv[2]);
 
  topo = linsched_topo_db[type];
 
  // Allow all tasks to use any processor.
  mask = (1 << count) - 1;
 
  // Initialize the topology as provided by the script interpreter
  linsched_init(&topo);
 
  // Create five processor-bound tasks (sleep 10, busy 90)
  create_tasks(5, mask, 10, 90);
 
  // Create five I/O-bound tasks (sleep 90, busy 10)
  create_tasks(5, mask, 90, 10);
 
  // Create a busy real-time round-robin task with a priority of 90
  linsched_create_RTrr_task( linsched_create_sleep_run(0,100), 90 );
 
  // Run the simulation
  linsched_run_sim(TEST_TICKS);
 
  // Emit the task statistics
  linsched_print_task_stats();
 
  return;
}

```

``` C
Task id =  1, exec_time =   305000000, run_delay = 59659000000, pcount = 156
Task id =  2, exec_time =   302000000, run_delay = 58680000000, pcount = 154
Task id =  3, exec_time =   304000000, run_delay = 58708000000, pcount = 155
Task id =  4, exec_time =   304000000, run_delay = 58708000000, pcount = 155
Task id =  5, exec_time =   304000000, run_delay = 58708000000, pcount = 155
Task id =  6, exec_time =   296000000, run_delay = 56118000000, pcount = 177
Task id =  7, exec_time =   296000000, run_delay = 56118000000, pcount = 177
Task id =  8, exec_time =   296000000, run_delay = 56118000000, pcount = 177
Task id =  9, exec_time =   296000000, run_delay = 56118000000, pcount = 177
Task id = 10, exec_time =   296000000, run_delay = 56118000000, pcount = 177
Task id = 11, exec_time = 57001000000, run_delay =  2998000000, pcount = 61
```
Este resultado muestra la lista de tareas (numeradas por ID de tarea), su tiempo de ejecución total (en ticks), la cantidad de tiempo que esperaron para ejecutarse y, finalmente, la cantidad de veces que se invocaron.
Un solo ticks representa cien nanosegundos.

Según este escenario, las primeras cinco tareas son tareas ocupadas y duermen el 10% del tiempo. Las segundas cinco tareas duermen la mayor parte del tiempo y están ocupadas el 10% del tiempo. La última tarea es una tarea en tiempo real y está ocupada el 100% del tiempo. Como se muestra, la tarea en tiempo real recibe la mayor parte del procesador único y se invoca solo 61 veces.


Ahora, veamos la misma prueba del  pero esta vez en una topología de cuatro núcleos y cuatro sockets (16 procesadores lógicos). Como cada tarea puede tener su propio procesador lógico, recibe considerablemente más tiempo de procesador durante la misma duración de la prueba. Aunque las tareas ocupadas y no ocupadas se invocan el mismo número de veces, las tareas no ocupadas reciben el 10% del tiempo de ejecución en comparación con las tareas ocupadas. Esta diferencia es el resultado de la configuración de reposo / ocupado (las tareas ocupadas se ejecutan durante 90 ticks, mientras que las tareas no ocupadas se ejecutan durante 10 ticks). También es interesante notar que su tarea en tiempo real se invoca una vez y se ejecuta durante la prueba (porque nunca duerme, nunca se reprogramó en su procesador).
``` C
Task id =  1, exec_time = 54000000000, run_delay = 0, pcount = 601
Task id =  2, exec_time = 54000156250, run_delay = 0, pcount = 600
Task id =  3, exec_time = 54000281250, run_delay = 0, pcount = 600
Task id =  4, exec_time = 54000406250, run_delay = 0, pcount = 600
Task id =  5, exec_time = 54000031250, run_delay = 0, pcount = 600
Task id =  6, exec_time =  6000187500, run_delay = 0, pcount = 600
Task id =  7, exec_time =  6000312500, run_delay = 0, pcount = 600
Task id =  8, exec_time =  6000437500, run_delay = 0, pcount = 600
Task id =  9, exec_time =  6000062500, run_delay = 0, pcount = 600
Task id = 10, exec_time =  6000218750, run_delay = 0, pcount = 600
Task id = 11, exec_time = 59999343750, run_delay = 0, pcount = 1
```


### Conclusiones
* Las tareas en tiempo real tienen mayor prioridad  a los procesos comunes nunca pueden ser bloqueados, mayor tiempo de ejecución.
* Los procesos que no han sido ejecutados por el procesador en un periodo largo de tiempo, aumentan su prioridad. Los que han sido ejecutados por mayor tiempo, reducen su prioridad.


Referencias


git clone https://kernel.googlesource.com/pub/scm/linux/kernel/git/pjt/linsched

https://www.ibm.com/developerworks/library/l-linux-scheduler-simulator/index.html

https://www.ibm.com/developerworks/library/l-linux-scheduler-simulator/l-linux-scheduler-simulator-pdf.pdf

http://webdelprofesor.ula.ve/ingenieria/gilberto/so/02_Planificador.pdf
