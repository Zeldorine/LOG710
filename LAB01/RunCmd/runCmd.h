#include <sys/time.h>
#include <sys/resource.h>

// Return code part
int SUCCESS = 0;
int ERROR_FORK = 1;
int ERROR_EXECVP = 2;
int ERROR_ARGS = 3;
int ERROR_GETRUSAGE = 4;

// Function part
/**
 * @brief 
 * @param argc
 * @param argv
 */
void childProcessFct(int* argc, char **argv);

/**
 * @brief 
 */
void parentProcessFct();

/**
 * @brief 
 * @param startTime
 * @param endTime
 * @return 
 */
void getWallClockTime(struct timeval* wallClockTime, struct timeval* startTime, struct timeval* endTime);

/**
 * @brief 
 * @param wcTime
 * @param usage
 */
void displayStats(struct timeval* wcTime, struct rusage* usage);