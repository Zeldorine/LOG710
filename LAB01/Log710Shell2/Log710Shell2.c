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
*     1.0   25/09/2017  TC & MN     Add Background struct, list of process and managing process 
*
*H*/

#include "Log710Shell2.h"
#include "string.h"   // pour le type pid_t
#include <unistd.h>		// pour fork
#include <sys/wait.h>
#include <stdio.h>		// pour perror, printf
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

struct BackgroundProcess backgroundProcessList[MAX_BACKGROUNG_PROCESS];
int backgroundProcessListPointer = 0;
int backgroundProcessListCounter = 0;

/**
 * @brief 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char **argv) 
{
    //backgroundProcessList = calloc(MAX_BACKGROUNG_PROCESS, sizeof(struct BackgroundProcess));
    executShell();
	return SUCCESS;
}

/**
 * @brief 
 */
void executShell(){   
    int runInBackground;
        
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
            
        // Trim the input to prevent to execute empty command
        trim(inputArg);
            
        // Checks args before to process to make sure a command is provided by the user
        if (strlen(inputArg) == 0) {
            printf("A command must be specify in argument\n");
            fflush(stdout);
            continue;
        }
        
        // Check if it should be execute in background
        struct BackgroundProcess currentProcess;
        if (inputArg[strlen(inputArg) - 1] == '&') {
            inputArg[strlen(inputArg) - 1] = '\0';
            printf("Run in background\n");
            fflush(stdout);
            
            runInBackground = TRUE;
            currentProcess.cmd = malloc(strlen(inputArg) * sizeof(char*));
            strcpy(currentProcess.cmd, inputArg);
            fflush(stdout);
        }
        else {
            runInBackground = FALSE;
        }
        
        // Create command
        char **cmd = getCmdArgs(inputArg);
        
        // Verify if execute command in parent
        if(handleCommand(cmd) == TRUE){
            continue;
        }
        
        pid_t pid;
        printf("Before switch\n");
            fflush(stdout);
        switch(pid=fork()){
            case -1:
                perror("An error occured during fork()");
                fflush(stderr);
                break;
            
            case 0 :
                childProcessFct(cmd, &currentProcess);
                break;
                
            default:
                parentProcessFct(&runInBackground);
                break;
        }
    }
}

/**
 * @brief 
 * @param cmd
 */
int handleCommand(char **cmd){
    // EXIT
    if(strcmp(cmd[0], EXIT_COMMAND) == 0) {
        if(backgroundProcessListCounter > 0){
            printf("Cannot exit now, there are %d tasks running in background. Waiting...", backgroundProcessListCounter);
            // Wait all tache finish before to exit
        } 
        
        exit(0);
    } 
    // CD
    else if(strcmp(cmd[0], CD_COMMAND) == 0) {
        if (chdir(cmd[1]) < 0) {
            printf("Cannot move to %s\n", cmd[1]);
        } else {
            char cwd[BUFFER_SIZE];
            getcwd(cwd, BUFFER_SIZE);
            printf("Current working diretory: %s\n", cwd);
            fflush(stdout);
        }
        
        return TRUE;
    } 
    // APTACHES
    else if(strcmp(cmd[0], APTACHES_COMMAND) == 0){
        if(backgroundProcessListCounter > 0){
            for(int i=0; i<backgroundProcessListCounter;i++){
                struct BackgroundProcess process = backgroundProcessList[i];
                printf("%d %s\n", process.pid, process.cmd);
                fflush(stdout);
            }
        }
    }
}

/**
 * @brief 
 */
void checkBackgroundProcess(){
    if(backgroundProcessListCounter > 0){
        // dont forget to free memory
    }
}

/**
 * @brief 
 * @param cmd
 */
void childProcessFct(char **cmd, struct BackgroundProcess* currentProcess) {
    // If a current process is not null, we need to add it to the background process list
    if(currentProcess){ 
        currentProcess->pid = getpid();
        
        if(backgroundProcessListCounter == MAX_BACKGROUNG_PROCESS) {
            printf("Cannot add process to background process list, max size ");
        } else {
            backgroundProcessList[backgroundProcessListPointer] = *currentProcess;
            backgroundProcessListCounter++;
            backgroundProcessListPointer++;
            printf("Process %d added with cmd %s\n", currentProcess->pid, currentProcess->cmd);
            fflush(stdout);
        }
    }
    
    execvp(cmd[0], &cmd[0]);
	printf("Erreur %s \n",strerror(errno));
	fflush(stdout);
}

/**
 * @brief 
 */
void parentProcessFct(int* runInBackground) {
    if(runInBackground){
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
    } else {
        // Don't wait execution and add procces id into the array
        
    }
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
	
    free(inputCopy);
    free(separator);
    free(token);
    free(tmp);
    
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