 /*H**********************************************************************
* FILENAME : runCmd.c 
*
* DESCRIPTION :
*       
*
*
* AUTHOR :
*       - Tony Cazorla
*       - Michael Nadeau      
* 
* START DATE :    18/09/2017
*
* CHANGES :
*
* VERSION   DATE        WHO         DETAIL
*     1.0   18/09/2017  TC & MN     Add execvp function and fork. 
*
*H*/

#include "runCmd.h"
#include "string.h"   // pour le type pid_t
#include <unistd.h>		// pour fork
#include <sys/wait.h>
#include <stdio.h>		// pour perror, printf
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

/**
 * @brief 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char **argv) 
{
    // Checks args before to process to make sure a command is provided by the user
	if (argc < 2) {
		printf("Error, a command must be specify in argument\n");
		fflush(stdout);
        exit(ERROR_ARGS);
	}
    
	pid_t pid;
    
    switch(pid=fork()){
        case -1:
            perror("An error occured during fork()");
            fflush(stderr);
            exit(ERROR_FORK);
            break;
        
        case 0 :
            childProcessFct(argc, argv);
            break;
            
        default:
            parentProcessFct();
            break;
    }
    
	return SUCCESS;
}

void childProcessFct(int argc, char **argv) {
	execvp(argv[1], &argv[1]);
	printf("Erreur %s \n",strerror(errno));
	fflush(stdout);
    exit(ERROR_EXECVP);
}

void parentProcessFct() {
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);
        
	wait(NULL);
    
    gettimeofday(&endTime, NULL);
    
    struct rusage usage;
    // Get statistics for child of the calling process 
    if(getrusage(RUSAGE_CHILDREN, &usage) != 0){
        perror("An error occured during getrusage()");  
        exit(ERROR_GETRUSAGE); 
    }
    
    struct timeval wcTime = getWallClockTime(startTime, endTime);
    
    // Display stats of execution.
    printf("+-----\n");
    printf("| Temps Wallclock : %ld seconds, %ld microseconds\n", wcTime.tv_sec , wcTime.tv_usec / (long) 1000); /*  user CPU time used */
    printf("| Temps CPU : %li seconds, %ld microseconds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec / (long) 1000); /* system CPU time used */
    printf("| Commutation de context : %li\n", (usage.ru_nvcsw + usage.ru_nivcsw));
    printf("| Defaults de pages : %li\n", usage.ru_majflt); /* page faults (hard page faults) */
    printf("| Pages reclamees : %li\n", usage.ru_minflt); /* page reclaims (soft page faults) */
    printf("+-----\n");
}

struct timeval getWallClockTime(struct timeval startTime, struct timeval endTime){
    long microseconds = (endTime.tv_sec - startTime.tv_sec) * (long)1000000 + ((long)endTime.tv_usec - (long)startTime.tv_usec);
    
    struct timeval wallClockTime;
    wallClockTime.tv_sec = microseconds / (long)1000000;
    wallClockTime.tv_usec = microseconds % (long)1000000;
    
    return wallClockTime;
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