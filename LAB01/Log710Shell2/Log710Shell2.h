#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

#include "string.h" 

// DEFINE PART
#define SUCCESS 0
#define ERROR_FORK 1
#define ERROR_EXECVP 2
#define ERROR_ARGS 3
#define ERROR_GETRUSAGE 4

#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE  2048
#define MAX_BACKGROUNG_PROCESS 128
#define DEBUG 0

// COMMAND TO MANAGE
const char EXIT_COMMAND[5] = "exit";
const char CD_COMMAND[3] = "cd";
const char APTACHES_COMMAND[9] = "aptaches";
const char PROMPT[15] = "\nLog710A2017%>";

// STRUCTURE PART
struct BackgroundProcess {
    int id;
    int pid;
    char* cmd;
    struct timeval* startTime;
};

// SIGNAL HANDLER PART
void sig_handler(int sig);

// FUNCTION PART

void registerSignalHandler();
void executShell();
void childProcessFct(char** cmd);
void executeBackgroundProcess(struct BackgroundProcess* currentProcess);
void executeCommand(char** cmd, int runInBackground, struct BackgroundProcess* currentProcess);
void parentProcessFct(pid_t pid);
void getWallClockTime(struct timeval* wallClockTime, struct timeval* startTime, struct timeval* endTime);
char** getCmdArgs(char* argv);
int handleCommand(char** cmd);
void displayStats(struct timeval* wcTime, struct rusage* usage);
void* trim(char* stringToTrim);
void checkBackgroundProcess();
void removeProcessFromList(struct BackgroundProcess* processToRemove);
void removeProcessAtIndexFromList(struct BackgroundProcess* processToRemove, int index);
void displayBackgroundProcess();
void waitingBackgroundProcess();
void displayCommandResult(struct timeval startTime);
void removeProcess(struct BackgroundProcess* process);
void reorgBackgroundProcessList(int index);