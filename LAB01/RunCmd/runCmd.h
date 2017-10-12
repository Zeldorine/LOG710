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

// Function part

void childProcessFct(char** argv);
void parentProcessFct();
void getWallClockTime(struct timeval* wallClockTime, struct timeval* startTime, struct timeval* endTime);
void displayStats(struct timeval* wcTime, struct rusage* usage);