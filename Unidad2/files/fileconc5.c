// Control de concurrencia en el FS

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
  int fd;  		// file descriptor
  int pid;		// process ID
  int saldo;
  struct flock arg;

  if (argc != 4) {printf ("USO: %s <fname> <monto1> <monto2>\n", argv[0]); exit (1);}
  fd = open(argv[1], O_RDWR);
  arg.l_type = F_WRLCK;
  arg.l_whence = SEEK_SET;
  arg.l_start = 0;
  arg.l_len = 4;
  if (fd < 0) {printf ("OPEN Error (PADRE)...\n"); exit (1);}
  pid = fork();
  if (pid > 0) { // padre
    if (fcntl(fd, F_SETLKW, &arg)<0) printf ("FLOCK P1\n");
    read (fd, (char *)&saldo, sizeof(saldo));    
    printf ("P1: saldo = %d\n", saldo);
    lseek (fd, 0, SEEK_SET);
    saldo = saldo + atoi(argv[2]);
    write (fd, (char *)&saldo, sizeof(saldo));    
    lseek (fd, 0, SEEK_SET);
    fdatasync(fd);
    printf ("P2: saldo = %d\n", saldo);
    arg.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &arg)<0) printf ("FLOCK P2\n");
    close (fd);
    exit (0);
  }
  else if (pid == 0) {  // hijo
    if (fcntl(fd, F_SETLKW, &arg)<0) printf ("FLOCK H1\n");
    close (fd);
    read (fd, (char *)&saldo, sizeof(saldo));    
    printf ("H1: saldo = %d\n", saldo);
    lseek (fd, 0, SEEK_SET);
    saldo = saldo + atoi(argv[3]);
    write (fd, (char *)&saldo, sizeof(saldo));    
    lseek (fd, 0, SEEK_SET);
    fdatasync(fd);
    printf ("H2: saldo = %d\n", saldo);
    arg.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &arg)<0) printf ("FLOCK H2\n");
    close (fd);
    exit (0);
  }
  else {
    printf ("FORK EROOR...\n");
    exit (1);
  }
}
