#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(){
  int rands[10];
  int copied[10];

  printf("generating random numbers:\n");
  int index = 0;
  while(index < 10){
    int num;
    int dev = open("/dev/random", O_RDONLY);
    read( dev, &num, sizeof( num));
    rands[index] = num;
    printf("random %d: %d\n", index, rands[index]);
    index++;
  }
  printf("\n");

  printf("writing numbers to file...\n");
  int textfile = open("file.txt", O_WRONLY);
  if( textfile < 0)
    printf("opening file error: %s\n", strerror(errno));

  int bytes_written = write( textfile, rands ,10 * sizeof(int));
  if( bytes_written < 0)
    printf("writing to file error: %s\n", strerror(errno));
  close( textfile);
  printf("\n");


  printf("reading numbers from file...\n");
  textfile = open("file.txt", O_RDONLY);
  if( textfile < 0)
    printf("opening file error: %s\n", strerror(errno));

  int bytes_read = read( textfile, copied, 10 * sizeof(int));
  if( bytes_read < 0)
    printf("reading file error: %s\n", strerror(errno));
  close( textfile);
  printf("\n");


  printf("verification that written values were the same:\n");
  int i = 0;
  while(i < 10){
    printf("  random %d: %d\n", i, copied[i]);
    i++;
  }
  return 0;
}
