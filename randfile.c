#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "randfile.h"

void handle_err(int result, char * err_msg) {
  if (result < 0) {
    printf("%s: %s\n", err_msg, strerror(errno));
    exit(-1);
  }
}

int rand_int() {
  int fd;
  handle_err(fd = open(RANDOM_PATH, O_RDONLY), "Error in opening file");
  int temp = 0;
  handle_err(read(fd, &temp, sizeof(temp)), "Error in reading file");
  close(fd);
  return temp;
}
