#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int main(int argc, char *argv[]) {
  if (argc != 1) {
    fprintf(2, "Usage: pingpong\n");
    exit(1);
  }
  int p[2];
  pipe(p);
  if (fork() == 0) {
    // close(p[1]);
    char buf[4];
    if (read(p[0], buf, 4) != 0) {
      printf("%d: received ping\n", getpid());
      close(p[0]);
      write(p[1], "wcnm", 4);
      close(p[1]);
      exit(0);
    }
  } else {
    // close(p[0]);
    write(p[1], "wcnm", 4);
    close(p[1]);
    wait(0);
    char buf[4];
    if (read(p[0], buf, 4) > 0) {
      printf("%d: received pong\n", getpid());
      close(p[0]);
      exit(0);
    }
  }
}