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
* START DATE :    25/09/2017
*
* CHANGES :
*
* VERSION   DATE        WHO         DETAIL
*     1.0   25/09/2017  TC & MN     Add a boucle, input command, cd and exit commands. 
*
*H*/

#include "Log710Shell.h"
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
    executShell();
	return SUCCESS;
}

void executShell(){
    while(TRUE){
        // Display prompt
        printf("Log710A2017%>");
        fflush(stdout);
        
        // Get command
        char inputArg[BUFFER_SIZE];
        fgets(inputArg, BUFFER_SIZE, stdin);
        
        // Remove \n
        if (inputArg[strlen(inputArg) - 1] == '\n')
            inputArg[strlen(inputArg) - 1] = '\0';
            
        // Trim the input to prevent to execut empty command
        printf("inputArg avant trim: %s\n", inputArg);
        fflush(stdout);
        trim(inputArg);
        printf("inputArg après trim: %s\n", inputArg);
        fflush(stdout);
            
        // Checks args before to process to make sure a command is provided by the user
        if (strlen(inputArg) == 0) {
            printf("A command must be specify in argument\n");
            fflush(stdout);
            continue;
        }
        
        // Create command
        char **cmd = getCmdArgs(inputArg);
        
        // Verify if execute command in parent
        if(handleCommand(cmd) == TRUE){
            continue;
        }
        
        pid_t pid;
        
        switch(pid=fork()){
            case -1:
                perror("An error occured during fork()");
                fflush(stderr);
                break;
            
            case 0 :
                childProcessFct(cmd);
                break;
                
            default:
                parentProcessFct();
                break;
        }
    }
}

/**
 * @brief 
 * @param cmd
 */
int handleCommand(char **cmd){
    if(strcmp(cmd[0], "exit") == 0) {
        exit(0);
    } else if(strcmp(cmd[0], "cd") == 0) {
        if (chdir(cmd[1]) < 0) {
            printf("Cannot move to %s\n", cmd[1]);
        } else {
            char cwd[BUFFER_SIZE];
            getcwd(cwd, BUFFER_SIZE);
            printf("Current working diretory: %s\n", cwd);
        }
        
        return TRUE;
    }
}

/**
 * @brief 
 * @param cmd
 */
void childProcessFct(char **cmd) {
    execvp(cmd[0], &cmd[0]);
	printf("Erreur %s \n",strerror(errno));
	fflush(stdout);
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

/**
 * @brief 
 * @param inputArgs
 * @return 
 */
char** getCmdArgs(char* inputArgs) {
    char* inputCopy = (char*) malloc(strlen(inputArgs) * sizeof(char*));
    char separator[2] = " ";
    char *tmp; 
    char *token; 
    int count = 0;
    
    // Count nb element
    strcpy(inputCopy, inputArgs);
    tmp = strtok(inputCopy, separator);
    while(tmp != NULL){
        count++;
        tmp = strtok(NULL, separator);
    }

    //Create args
    char **arg = calloc (count + 1, sizeof(char*));
    
    strcpy(inputCopy, inputArgs);
    token = strtok(inputCopy, separator);
    int index = 0;
    while(token != NULL){
        arg[index] = (char*) malloc(sizeof(token));
		arg[index] = token;
        token = strtok(NULL, separator);
        index++;
    }

	arg[index] = NULL;
	
   return arg;
}

/**
 * @brief 
 * @param stringToTrim
 */
void *trim(char* stringToTrim){
    int dest;
    int src=0;
    int len = strlen(stringToTrim);

    // Check if null
    if(!stringToTrim)
        return NULL;

    // Remove left whitespaces
    while(isspace(stringToTrim[src])) src++;

    if(strlen(stringToTrim) == 0){
        return stringToTrim;
    }

    // Copy the rest of the string to front of string and remove the last
    if(src > 0){
    for(dest=0; src<len; dest++, src++) 
        {
            stringToTrim[dest] = stringToTrim[src];
            stringToTrim[src] = '\0';
        }
    }

    // Remove right whitespaces
    for(dest=len-1; isspace(stringToTrim[dest]); --dest)
    {
        stringToTrim[dest] = '\0';
    }
}