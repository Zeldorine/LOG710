#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

#include "string.h"

// Return code part
int SUCCESS = 0;
int ERROR_FORK = 1;
int ERROR_EXECVP = 2;
int ERROR_ARGS = 3;
int ERROR_GETRUSAGE = 4;

int TRUE = 1;
int FALSE = 0;
int BUFFER_SIZE = 2048;

// Commands to manage
char EXIT_COMMAND[5] = "exit";
char CD_COMMAND[3] = "cd";

// Function part

void executShell();
void childProcessFct(char** cmd);
void parentProcessFct();
void getWallClockTime(struct timeval* wallClockTime, struct timeval* startTime, struct timeval* endTime);
char** getCmdArgs(char* argv);
int handleCommand(char** cmd);
void displayStats(struct timeval* wcTime, struct rusage* usage);
void* trim(char* stringToTrim);