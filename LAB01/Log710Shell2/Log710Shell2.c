 /***********************************************************************
* FILENAME : runCmd.c 
*
* DESCRIPTION :
*       
*
* EQUIPE : 8
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
*     1.1   03/10/2017  TC & MN     Add trim method and create background process 
*     1.2   10/10/2017  TC & MN     Fix bug when creating process (all process had the same adress) and 
*                                   remove background process from the list when it finished.
*                                   Fix bug for wallclock for background process.
*                                   To verify :
*                                       - Methode exit, wait all process before to quit
*                                       - Display background process result
*                                       - Check background process state in background
*
*/

#include "Log710Shell2.h"
#include "string.h" 
#include <unistd.h>	 // pour fork
#include <sys/wait.h>// pour le type pid_t
#include <stdio.h> // pour perror, printf
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

struct BackgroundProcess *backgroundProcessList[MAX_BACKGROUNG_PROCESS];
int backgroundProcessListCounter = 0;

/**
 * @brief 
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char **argv) {
    executShell();
	
	return SUCCESS;
}

/**
 * @brief 
 */
void executShell() {   
        
    while(TRUE) {
        // Verify background process
        checkBackgroundProcess();
        
        // Display prompt
        int runInBackground = FALSE;
        printf(PROMPT);
        fflush(stdout);
        
        // Get command
        char inputArg[BUFFER_SIZE];
        fgets(inputArg, BUFFER_SIZE, stdin);
        
        // Remove \n
        if (inputArg[strlen(inputArg) - 1] == '\n')
            inputArg[strlen(inputArg) - 1] = '\0';
			
		// Remove &
		// Task to be executed in background
		if (inputArg[strlen(inputArg) - 1] == '&') {
            inputArg[strlen(inputArg) - 1] = '\0';
			runInBackground = TRUE;
		}
            
        // Trim the input to prevent executing empty command
        trim(inputArg);
            
        // Check if a command is provided by the user
        if (strlen(inputArg) == 0) {
            printf("A command must be specify in argument\n");
            fflush(stdout);
            continue;
        }
		
        // Check if task to be executed in background
        if (runInBackground) {
            struct BackgroundProcess* currentProcess = malloc(sizeof(struct BackgroundProcess));
            currentProcess->cmd = malloc(strlen(inputArg) * sizeof(char*));
            currentProcess->id = backgroundProcessListCounter+1;
            strcpy(currentProcess->cmd, inputArg);
            executeBackgroundProcess(currentProcess);
            continue;
        }
  
        // Create command
        char** cmd = getCmdArgs(inputArg);

        // Check if command has to be handled
        if(handleCommand(cmd) == TRUE){
            continue;
        }
    
        executeCommand(cmd, runInBackground, NULL);
    }
}

void executeCommand(char **cmd, int runInBackground, struct BackgroundProcess* currentProcess){
    if(DEBUG){
        printf("executeCommand, arg cmd: %s, runInBackground: %d\n", cmd[0], runInBackground);
        fflush(stdout);
    }
    
    pid_t pid;
    switch(pid = fork()) {
        case -1:
            perror("An error occured during fork()\n");
            fflush(stderr);
            break;
        
        case 0 :
            childProcessFct(cmd);
            break;
            
        default:
        
            if(!runInBackground){
                parentProcessFct(pid);
            } else if(runInBackground && currentProcess){
                currentProcess->pid = pid; 
                struct timeval* time = malloc(sizeof(struct timeval));
                gettimeofday(time, NULL);
                printf("| Temps Wallclock : %li seconds, %li microseconds\n", time->tv_sec , time->tv_usec / (long) 1000);
                fflush(stdout);
                currentProcess->startTime = time;
            }

            break;
    }
}


/**
 * @brief 
 * @param cmd
 */
void childProcessFct(char **cmd) {  
    if(DEBUG){
        printf("childProcessFct, cmd: %s\n", cmd[0]);
        fflush(stdout);
    }
     
    execvp(cmd[0], &cmd[0]);
	printf("Erreur - execvp: %s \n",strerror(errno));
	fflush(stdout);
}


/**
 * @brief 
 * @param cmd
 */
int handleCommand(char** cmd) {
    if(DEBUG){
        printf("handleCommand, arg cmd: %s\n", cmd[0]);
        fflush(stdout);
    }
    
    
    // EXIT
    if(strcmp(cmd[0], EXIT_COMMAND) == 0) {
        if(backgroundProcessListCounter > 0) {
            printf("Cannot exit now, there are %d tasks running in background. Waiting...\n", backgroundProcessListCounter);
            fflush(stdout);
            
            // Wait for all tasks to finish before exiting
            waitingBackgroundProcess();
        } 
        
        exit(0);
    } 
    
    // CD
    else if(strcmp(cmd[0], CD_COMMAND) == 0) {
        if (chdir(cmd[1]) < 0) {
            printf("Cannot move to %s\n", cmd[1]);
			fflush(stdout);
        } else {
            char cwd[BUFFER_SIZE];
            getcwd(cwd, BUFFER_SIZE);
            printf("Current working diretory: %s\n", cwd);
            fflush(stdout);
        }
        
        return TRUE;
    } 
    
    // APTACHES
    else if(strcmp(cmd[0], APTACHES_COMMAND) == 0) {
        fflush(stdout);
        if(backgroundProcessListCounter > 0) {
            for(int i = 0; i < backgroundProcessListCounter; i++) {
                struct BackgroundProcess* process = backgroundProcessList[i];
                printf("[%d] %d %s\n", process->id,process->pid, process->cmd);
                fflush(stdout);
            }
        } else {
            printf("No task in background\n");
            fflush(stdout);
        }
        
        return TRUE;
    }
	
	return FALSE;
}

void waitingBackgroundProcess(){    
    if(DEBUG){
        printf("waitingBackgroundProcess\n");
        fflush(stdout);
    }
    
    while(backgroundProcessListCounter > 0){
        checkBackgroundProcess();
        sleep(1);
    }
}

/**
 * @brief 
 */
void checkBackgroundProcess() {
    if(DEBUG){
        printf("checkBackgroundProcess\n");
        fflush(stdout);
    }
    
    printf("checkBackgroundProcess backgroundProcessListCounter = %d\n", backgroundProcessListCounter);
    fflush(stdout);
    if(backgroundProcessListCounter > 0){
        for(int i = 0; i < backgroundProcessListCounter; i++) {
            struct BackgroundProcess* process = backgroundProcessList[i];
            
            printf("\n Check process cmd:%s and pid: %d\n",process->cmd,process->pid);
            fflush(stdout);
            
            pid_t pid;
            int status;
           
            if((pid = waitpid(process->pid, &status, WNOHANG)) == -1){
                printf("Wait no hang error for pid %d and status; %d\n",pid, status);
                fflush(stdout);
            } else if (pid == 0){
                printf("Child %d is still running \n",process->pid);
                fflush(stdout);
            } else {
                if(WIFEXITED(status)){
                    printf("Background process executed\n");
                    printf("[%d] %d %s\n",process->id, process->pid, process->cmd);
                    fflush(stdout);
                } else {
                    printf("Child %d exited with status of %d\n", WEXITSTATUS(status));
                    fflush(stdout);
                }
                
                displayCommandResult(*process->startTime);
                
                // remove process and free memory               
                removeProcess(process); 
                
                if(backgroundProcessListCounter > 1){
                    reorgBackgroundProcessList(i);
                }
                
                backgroundProcessListCounter--;
            }
        }
    }
}

void reorgBackgroundProcessList(int index){
    if(DEBUG){
        printf("reorgBackgroundProcessList, index: %d\n", index);
        fflush(stdout);
    }
    
    for(int i=index; i<backgroundProcessListCounter-1; i++){
        backgroundProcessList[i] = backgroundProcessList[i+1];
    }
    
    printf("Remove last element after reorg array of process\n");
    fflush(stdout);
    backgroundProcessList[backgroundProcessListCounter-1] = 0;
}

void removeProcess(struct BackgroundProcess* process){
    if(DEBUG){
        printf("removeProcess\n");
        fflush(stdout);
    }
    
    free(process->startTime);
    free(process->cmd);
    free(process);
}

void executeBackgroundProcess(struct BackgroundProcess* currentProcess) {
    if(DEBUG){
        printf("executeBackgroundProcess\n");
        fflush(stdout);
    }
    
     // If a current process is not null, we need to add it to the background process list
    if(currentProcess) { 
        if(backgroundProcessListCounter == MAX_BACKGROUNG_PROCESS) {
            printf("Cannot add process to background process list, no more space\n");
            fflush(stdout);
        } else {
            backgroundProcessList[backgroundProcessListCounter] = currentProcess;
            backgroundProcessListCounter++;

            // Create command
            char** cmd = getCmdArgs(currentProcess->cmd);
            executeCommand(cmd, TRUE, currentProcess);

            printf("Process %d added with cmd %s\n", currentProcess->pid, currentProcess->cmd);
            printf("[%d] %d\n", currentProcess->id, currentProcess->pid);
            fflush(stdout);
        }
    }   
}

/**
 * @brief 
 */
void parentProcessFct(pid_t pid) {
    if(DEBUG){
        printf("parentProcessFct\n");
        fflush(stdout);
    }
    
    struct timeval startTime, endTime;
    gettimeofday(&startTime, NULL);
        
    int status;
    waitpid(pid, &status, NULL);
    
    displayCommandResult(startTime);
}

void displayCommandResult(struct timeval startTime){
    if(DEBUG){
        printf("displayCommandResult\n");
        fflush(stdout);
    }
    
    struct timeval endTime;
    gettimeofday(&endTime, NULL);
    
    struct rusage usage;
    // Get statistics for child of the calling process 
    if(getrusage(RUSAGE_CHILDREN, &usage) != 0){
        perror("An error occured during getrusage()\n");  
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
    if(DEBUG){
        printf("getWallClockTime\n");
        fflush(stdout);
    }
    
    long microseconds = (endTime->tv_sec - startTime->tv_sec) * (long)1000000 + ((long) endTime->tv_usec - (long) startTime->tv_usec);
    
    wallClockTime->tv_sec = microseconds / (long) 1000000;
    wallClockTime->tv_usec = microseconds % (long) 1000000;
}

/**
 * @brief 
 * @param wcTime
 * @param usage
 */
void displayStats(struct timeval* wcTime, struct rusage* usage){
    if(DEBUG){
        printf("displayStats\n");
        fflush(stdout);
    }
    
    // Display stats of execution.
    printf("+-----\n");
    printf("| Temps Wallclock : %li seconds, %li microseconds\n", wcTime->tv_sec , wcTime->tv_usec / (long) 1000); /*  user CPU time used */
    printf("| Temps CPU : %li seconds, %li microseconds\n", usage->ru_stime.tv_sec, usage->ru_stime.tv_usec / (long) 1000); /* system CPU   time used */
    printf("| Commutation de context involontaire : %li\n", (usage->ru_nivcsw)); /* involuntary context switches */
    printf("| Commutation de context volontaire : %li\n", (usage->ru_nvcsw)); /* voluntary context switches */
    printf("| Defaults de pages : %li\n", usage->ru_majflt); /* page faults (hard page faults) */
    printf("| Pages reclamees : %li\n", usage->ru_minflt); /* page reclaims (soft page faults) */
    printf("+-----\n");
    fflush(stdout);
}

/**
 * @brief 
 * @param inputArgs
 * @return 
 */
char** getCmdArgs(char* inputArgs) {
    if(DEBUG){
        printf("getCmdArgs, inputArgs: %s\n", inputArgs);
        fflush(stdout);
    }
    
    char* inputCopy = (char*) malloc(strlen(inputArgs) * sizeof(char*));
    char separator[2] = " ";
    char* tmp; 
    char* token; 
    int count = 0;
	
    // Count elements
    strcpy(inputCopy, inputArgs);
    tmp = strtok(inputCopy, separator);
    while(tmp != NULL){
        count++;
        tmp = strtok(NULL, separator);
    }

    // Create args
    char** arg = calloc (count + 1, sizeof(char*));
    
    strcpy(inputCopy, inputArgs);
    token = strtok(inputCopy, separator);
    int index = 0;
    while(token != NULL){
        arg[index] = (char*) malloc(sizeof(token));
        strcpy(arg[index], token);

        token = strtok(NULL, separator);
        index++;
    }

	arg[index] = NULL;
	
    free(inputCopy);
    free(token);
    free(tmp);
	
    return arg;
}

/**
 * @brief 
 * @param stringToTrim
 */
void *trim(char* stringToTrim) {
    if(DEBUG){
        printf("trim, stringToTrim: %s\n", stringToTrim);
        fflush(stdout);
    }
    
    int dest;
    int src = 0;
    int len = strlen(stringToTrim);

    // Check if null
    if(!stringToTrim)
        return NULL;

    // Remove left whitespaces
    while(isspace(stringToTrim[src])) src++;

    if(strlen(stringToTrim) == 0)
        return stringToTrim;

    // Copy the rest of the string to front of string and remove the last
    if(src > 0)
		for(dest=0; src<len; dest++, src++) {
			stringToTrim[dest] = stringToTrim[src];
			stringToTrim[src] = '\0';
		}

    // Remove right whitespaces
    for(dest = len-  1; isspace(stringToTrim[dest]); --dest)
        stringToTrim[dest] = '\0';
}