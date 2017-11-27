 /***********************************************************************
* FILENAME : logger.h
*
* DESCRIPTION : Lab 03
* 				Implementing a logger to keep a trace.

*       
* EQUIPE : 8
* 
* AUTHOR :
*       - Tony Cazorla
*       - Michael Nadeau      
* 
* START DATE :    13/11/2017
*
* CHANGES :
*
* VERSION   DATE        WHO         DETAIL
*     1.0   13/11/2017  TC & MN     Create a file and log the text. 
* 
*
*/

#define INFO_TEXT  "[INFO]"
#define ERROR_TEXT "[ERROR]"
#define DEFAULT_TEXT "[DEFAULT]"

#define APPENDIX "Log710_Lab03_log_"
#define FILE_TYPE ".txt"
#define TAB "\t"
#define NEWLINE "\n"

#define ERROR  1
#define INFO  0

/**
 * @brief 
 */
void initLogger();

/**
 * @brief 
 */
void closeLogger();

/**
 * @brief 
 * @return 
 */
char* getTimestamp();

/**
 * @brief 
 * @param level
 * @param tag
 * @param message
 * @param lineNumber
 */
void log(int level, const char* tag, const char* message, int lineNumber);