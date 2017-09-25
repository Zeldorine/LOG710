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
*     1.1   19/09/2017  TC & MN     Add display informations function with rusage struct. 
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
            childProcessFct(argv);
            break;
            
        default:
            parentProcessFct();
            break;
    }
    
	return SUCCESS;
}

/**
 * @brief 
 * @param argv
 */
void childProcessFct(char **argv) {
	execvp(argv[1], &argv[1]);
	printf("Erreur during execvp %s \n", strerror(errno));
	fflush(stdout);
    exit(ERROR_EXECVP);
}

/**
 * @brief 
 */
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
    
    struct timeval wcTime;
    getWallClockTime(&wcTime, &startTime, &endTime);
    
    displayStats(&wcTime, &usage);
}

/**
 * @brief 
 * @param wallClockTime
 * @param startTime
 * @param endTime
 */
void getWallClockTime(struct timeval* wallClockTime, struct timeval* startTime, struct timeval* endTime){
    long microseconds = (endTime->tv_sec - startTime->tv_sec) * (long)1000000 + ((long)endTime->tv_usec - (long)startTime->tv_usec);
    
    wallClockTime->tv_sec = microseconds / (long)1000000;
    wallClockTime->tv_usec = microseconds % (long)1000000;
}

/**
 * @brief 
 * @param wcTime
 * @param usage
 */
void displayStats(struct timeval* wcTime, struct rusage* usage){
        // Display stats of execution.
    printf("+-----\n");
    printf("| Temps Wallclock : %li seconds, %li microseconds\n", wcTime->tv_sec , wcTime->tv_usec / (long) 1000); /*  user CPU time used */
    printf("| Temps CPU : %li seconds, %li microseconds\n", usage->ru_stime.tv_sec, usage->ru_stime.tv_usec / (long) 1000); /* system CPU time used */
    printf("| Commutation de context involontaire : %li\n", (usage->ru_nivcsw)); /* involuntary context switches */
    printf("| Commutation de context volontaire : %li\n", (usage->ru_nvcsw)); /* voluntary context switches */
    printf("| Defaults de pages : %li\n", usage->ru_majflt); /* page faults (hard page faults) */
    printf("| Pages reclamees : %li\n", usage->ru_minflt); /* page reclaims (soft page faults) */
    printf("+-----\n");
}