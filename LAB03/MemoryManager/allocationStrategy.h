 /***********************************************************************
* FILENAME : allocationStrategy.h
*
* DESCRIPTION : Lab 03
* 				Contains API to manage (create and remove) bloc memory.
*               This API should be implemented by differents algorithms

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
#define MAX_MEMORY_SIZE  2048
#define DEBUG 0

// RETURN CODE 
#define SUCCESS 0
#define ERROR_MEMORY_ALLOCATION 1
#define ERROR_MEMORY_OVERFLOW 2

// ENUM
typedef enum BLOC_TYPE BLOC_TYPE;
enum BLOC_TYPE {
    HOLE,
    PROCESS
};

typedef enum ALLOCATION_STRATEGY ALLOCATION_STRATEGY;
enum ALLOCATION_STRATEGY {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT,
    NEXT_FIT
};

// STRUCTURE PART
struct memoryBloc {
    void* blocAddress;
    BLOC_TYPE blocType;
    int start;
    int length;
};

/**
 * @brief 
 */
void initmem();

struct memoryBloc* alloumem(int size);

void liberemem(struct memoryBloc* blocToFree);

void mergeBloc(int previousBlocIndex, int nextBlocIndex);

int nbloclibres();

int nblocalloues();

int memlibre();

int mem_pgrand_libre();

int mem_small_free(int maxBlocSize);

int mem_est_alloue(int pByte);

void affiche_etat_memoire();

void affiche_parametres_memoire();

char* getBlocTypeName(BLOC_TYPE type);

void setAllocationStrategy(ALLOCATION_STRATEGY strategy);

// All allocations strategies
struct memoryBloc* allocationStrategyFirstFit(int size);

struct memoryBloc* allocationStrategyWorstFit(int size);

struct memoryBloc* allocationStrategyBestFit(int size);

struct memoryBloc* allocationStrategyNextFit(int size);

