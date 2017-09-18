#include <sys/time.h>

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
void childProcessFct(int argc, char **argv);

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
struct timeval getWallClockTime(struct timeval startTime, struct timeval endTime);
