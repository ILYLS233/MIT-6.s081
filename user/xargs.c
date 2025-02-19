#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/param.h"

#define MAXLINE 1024

int main(int argc, char *argv[]){
    char line[MAXLINE];
    char* params[MAXARG];
    int n, args_index = 0;
    int i;

    char* cmd = argv[1];
    for (i = 1; i < argc; i++) params[args_index++] = argv[i];

    while ((n = read(0, line, MAXLINE)) > 0){
        if (fork() == 0) {
            char *arg = (char*) malloc(sizeof(line));
            int index = 0;
            for (i = 0; i < n; i++){
                if (line[i] == ' ' || line[i] == '\n')
                {
                    arg[index] = 0;
                    params[args_index++] = arg;
                    index = 0;
                    arg = (char*) malloc(sizeof(line));
                }
                else arg[index++] = line[i];
            }
            arg[index] = 0;
            params[args_index] = 0;
            exec(cmd, params);
        }
        else wait((int*)0);
    }
    exit(0);
}