 /***********************************************************************
* FILENAME : runCmd.c 
*
* DESCRIPTION :	Lab part 1
*       		The Shell must execute a command and display time stats.
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
*     1.0   18/09/2017  TC & MN     Added execvp function and fork. 
*     1.1   19/09/2017  TC & MN     Added display informations function with rusage struct. 
* 	  1.2	12/10/2017	TC & MN		Added the DOC.
* 									Formatted for release.
**/

#include "runCmd.h"

/**
 * @brief Main loop for the Shell execution.
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
    
    switch(pid=fork()) {
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
 * @brief Executes the command as a child process.
 * @param cmd The command to execute
 */
void childProcessFct(char** argv) {
	execvp(argv[1], &argv[1]);
	printf("Erreur during execvp %s \n", strerror(errno));
	fflush(stdout);
	
    exit(ERROR_EXECVP);
}

/**
 * @brief Waits for the child process to be finished and displays it.
 */
void parentProcessFct() {
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);
        
	wait(NULL);
    
    gettimeofday(&endTime, NULL);
    
    struct rusage usage;
    // Get statistics for child of the calling process 
    if(getrusage(RUSAGE_CHILDREN, &usage) != 0) {
        perror("An error occured during getrusage()");  
        exit(ERROR_GETRUSAGE); 
    }
    
    struct timeval wcTime;
    getWallClockTime(&wcTime, &startTime, &endTime);
    
    displayStats(&wcTime, &usage);
}

/**
 * @brief Sets clock time.
 * @param wallClockTime The time's structure
 * @param startTime Time at which it started
 * @param endTime Time at which it ended
 */
void getWallClockTime(struct timeval* wallClockTime, struct timeval* startTime, struct timeval* endTime){
    long microseconds = (endTime->tv_sec - startTime->tv_sec) * (long)1000000 + ((long)endTime->tv_usec - (long)startTime->tv_usec);
    
    wallClockTime->tv_sec = microseconds / (long)1000000;
    wallClockTime->tv_usec = microseconds % (long)1000000;
}

/**
 * @brief Displays time stats for a given usage Struct.
 * @param wcTime Time's Struct
 * @param usage Usage's Struct
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