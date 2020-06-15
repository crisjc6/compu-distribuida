// Abrir y escribir concurrentemente un mismo archivo

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
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
