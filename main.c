#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "randfile.h"

int main() {
  RANDOM_PATH = "/dev/urandom";

  int my_arr[10];

  printf("Generating 10 random numbers\n");

  int i;
  for (i = 0; i < 10; i++) {
    my_arr[i] = rand_int();
    printf("%d: %d\n", i, my_arr[i]);
  }

  char * out_filename = "out";
  remove(out_filename);
  int fd = open(out_filename, O_WRONLY | O_CREAT, 0644);
  handle_err(fd, "Error opening file for writing");
  printf("Writing array to file\n");
  handle_err(write(fd, my_arr, sizeof(my_arr)), "Error writing arr to file");
  close(fd);

  handle_err(fd = open(out_filename, O_RDONLY), "Error opening file for reading");
  printf("Reading file into arr\n");

  int my_new_arr[10];

  handle_err(read(fd, my_new_arr, sizeof(my_new_arr)), "Error read arr to file");
  close(fd);

  printf("Printing new arr\n");

  for (i = 0; i < 10; i++) {
    printf("%d: %d\n", i, my_new_arr[i]);
  }

  return 0;
}
