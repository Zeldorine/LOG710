 /***********************************************************************
* FILENAME : allocationStrategyFatcory.h
*
* DESCRIPTION : Lab 03
* 				A factory to create a specific algorithm to manage memory.
*               The algorithm implements allocationStrategy API.

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
*     1.0   13/11/2017  TC & MN     Create file and first implementation. 
* 
*
*/

// DEFINE PART
#define MAX_BLOC_SIZE  2048
#define NB_BLOC_SIZE 128
#define DEBUG 0

// RETURN CODE 
#define SUCCESS 0
#define ERROR_MEMORY_ALLOCATION 1

// ALGORITHM
const char FIRST_FIT[9] = "firstFit";
const char BEST_FIT[8] = "bestFit";
const char WORST_FIT[9] = "worstFit";
const char NEXT_FIT[8] = "nextFit";

