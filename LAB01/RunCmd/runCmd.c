#include "runCmd.h"

#include <sys/types.h>   // pour le type pid_t
#include <unistd.h>		// pour fork
#include <stdio.h>		// pour perror, printf
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv) 
{
	if (argc < 2) {
		printf("no cmd \n");
		fflush(stdout);
	}
	pid_t pid;
    
    switch(pid=fork()){
        case -1:
            perror("An error occured during fork()");
            fflush(stderr);
            break;
        
        case 0 :
            childProcessFct(argc, argv);
            break;
            
        default:
            parentProcessFct(pid);
            break;
    }
    
	return 0;
}

void childProcessFct(int argc, char **argv) {
	execvp(argv[1], &argv[1]);
	printf("Erreur %s\n",strerror(errno));
	fflush(stdout);
}

void parentProcessFct(pid_t pid) {
	wait(pid);
}

/*char* getCmd(char** argv) {
	return argv[1];
}

char** getCmdArgs(int argc, char** argv) {
	char** arg = (char**) malloc((argc - 1) * sizeof(char*));
	
	int i = 2;
	for (i; i < argc; i++) {
		arg[i - 2] = (char*) malloc(sizeof(argv[i]));
		arg[i - 2] = argv[i];
	}
	printf("%d\n", sizeof(arg));
	fflush(stdout);
	arg[i - 2] = NULL;
	
   return arg;
}*/