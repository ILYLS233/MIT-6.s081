#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int main(int argc, char* argv[]){
	int numbers[110], p[2], pid, index = 0;
	for(int i = 2; i <= 35; i++){
		numbers[index++] = i;
	}
	while(index){
		pipe(p);
		pid = fork();
		if(pid > 0){
			close(p[0]);
			for(int i = 0; i < index; i++){
				write(p[1], &numbers[i], sizeof(numbers[i]));
			}
            close(p[1]);
			wait((int *)0);
			exit(0);
		}
		else if(pid == 0){
			int prime = 0, tmp = 0;
            index = 0;
			close(p[1]);
			while(read(p[0], &tmp, sizeof(tmp)) > 0){
				if(prime == 0){
					prime = tmp;
				}
				else{
					if(tmp % prime){
						numbers[index++] = tmp;
					}		
				}
			}
            close(p[0]);
			printf("prime %d\n", prime);
		}
		else{
			fprintf(2, "fork failed\n");
			exit(1);
		}
	}
	exit(0);
}