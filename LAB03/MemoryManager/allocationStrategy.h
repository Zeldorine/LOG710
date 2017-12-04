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
#define TRUE 1
#define FALSE 0

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
void initmem(int size);

/**
 * @brief 
 * @param size
 * @return 
 */
struct memoryBloc* alloumem(int size);

/**
 * @brief 
 * @param blocToFree
 */
void liberemem(struct memoryBloc* blocToFree);

/**
 * @brief 
 * @param previousBlocIndex
 * @param nextBlocIndex
 */
void mergeBloc(int previousBlocIndex, int nextBlocIndex);

/**
 * @brief 
 * @return 
 */
int nbloclibres();

/**
 * @brief 
 * @return 
 */
int nblocalloues();

/**
 * @brief 
 * @return 
 */
int memlibre();

/**
 * @brief 
 * @return 
 */
int mem_pgrand_libre();

/**
 * @brief 
 * @param maxBlocSize
 * @return 
 */
int mem_small_free(int maxBlocSize);

/**
 * @brief 
 * @param pByte
 * @return 
 */
int mem_est_alloue(int pByte);

/**
 * @brief 
 */
void affiche_etat_memoire();

/**
 * @brief 
 */
void affiche_parametres_memoire();

/**
 * @brief 
 * @param type
 * @return 
 */
char* getBlocTypeName(BLOC_TYPE type);

/**
 * @brief 
 * @param strategy
 */
void setAllocationStrategy(ALLOCATION_STRATEGY strategy);

// All allocations strategies
/**
 * @brief 
 * @param size
 * @return 
 */
struct memoryBloc* allocationStrategyFirstFit(int size);


/**
 * @brief 
 * @param size
 * @return 
 */
struct memoryBloc* allocationStrategyWorstFit(int size);

/**
 * @brief 
 * @param size
 * @return 
 */
struct memoryBloc* allocationStrategyBestFit(int size);

/**
 * @brief 
 * @param size
 * @return 
 */
struct memoryBloc* allocationStrategyNextFit(int size);

/**
 * @brief 
 * @param size
 * @param index
 * @param currentMemBloc
 */
struct memoryBloc* addMemorybloc(int size, int index, struct memoryBloc* currentMemBloc);