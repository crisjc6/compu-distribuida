// Control de concurrencia con advisory lock

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
  int fd;  		// file descriptor
  int pid;		// process ID
  int saldo;

  if (argc != 4) {printf ("USO: %s <fname> <monto1> <monto2>\n", argv[0]); exit (1);}
  pid = fork();
  if (pid > 0) { // padre
    fd = open(argv[1], O_RDWR);
    if (fd < 0) {printf ("OPEN Error (PADRE)...\n"); exit (1);}
    flock (fd, LOCK_EX);
    read (fd, (char *)&saldo, sizeof(saldo));    
    printf ("P: saldo = %d\n", saldo);
    lseek (fd, 0, SEEK_SET);
    saldo = saldo + atoi(argv[2]);
    write (fd, (char *)&saldo, sizeof(saldo));    
    close (fd);
    flock (fd, LOCK_UN);
    exit (0);
  }
  else if (pid == 0) {  // hijo
    fd = open(argv[1], O_RDWR);
    if (fd < 0) {printf ("OPEN Error (HIJO)...\n"); exit (1);}
    flock (fd, LOCK_EX);
    read (fd, (char *)&saldo, sizeof(saldo));    
    printf ("H: saldo = %d\n", saldo);
    lseek (fd, 0, SEEK_SET);
    saldo = saldo + atoi(argv[3]);
    write (fd, (char *)&saldo, sizeof(saldo));    
    close (fd);
    flock (fd, LOCK_UN);
    exit (0);
  }
  else {
    printf ("FORK EROOR...\n");
    exit (1);
  }
}
