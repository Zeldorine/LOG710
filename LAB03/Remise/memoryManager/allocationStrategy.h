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
 * @brief Initializes a memory space where memory blocs can be created.
 * @param size The size of the memory space.
 */
void initmem(int size);

/**
 * @brief Reserves a memory bloc of the given size.
 * @param size The size of the desired memory bloc.
 * @return A pointer pointing at the memory bloc.
 */
struct memoryBloc* alloumem(int size);

/**
 * @brief Frees the given memory bloc.
 * @param blocToFree The memory bloc to free.
 */
void liberemem(struct memoryBloc* blocToFree);

/**
 * @brief Merges the given memory blocs.
 * @param previousBlocIndex The first memory bloc to be merged.
 * @param nextBlocIndex The second memory bloc to be merged.
 */
void mergeBloc(int previousBlocIndex, int nextBlocIndex);

/**
 * @brief Returns the number of free memory blocs.
 * @return The number of free memory blocs.
 */
int nbloclibres();

/**
 * @brief Returns the number of memory blocs allocated.
 * @return The number of memory blocs allocated.
 */
int nblocalloues();

/**
 * @brief Returns the sum of all free memory blocs' size.
 * @return The sum of all free memory blocs' size.
 */
int memlibre();

/**
 * @brief Returns the size of the biggest free memory bloc.
 * @return The size of the biggest free memory bloc.
 */
int mem_pgrand_libre();

/**
 * @brief Returns the number of blocs' sizes smaller than maxBlocSize.
 * @param maxBlocSize The maximum bloc size.
 * @return The number of blocs' sizes smaller than maxBlocSize.
 */
int mem_small_free(int maxBlocSize);

/**
 * @brief Returns whether or not the given byte is allocated.
 * @param pByte The index of the given byte.
 * @return Whether or not the given byte is allocated.
 */
int mem_est_alloue(int pByte);

/**
 * @brief Prints current's memory state.
 */
void affiche_etat_memoire();

/**
 * @brief Prints memory allocation parameters. mem_pgrand_libre(), memlibre(), nbloclibres(), nblocalloues() and mem_small_free(maxTaillePetit).
 */
void affiche_parametres_memoire();

/**
 * @brief Returns a string for the given type of the memory bloc.
 * @param type The type of memory bloc.
 * @return A string for the given type of memory bloc.
 */
char* getBlocTypeName(BLOC_TYPE type);

/**
 * @brief Sets the allocation strategy.
 * @param strategy The allocation strategy to be used.
 */
void setAllocationStrategy(ALLOCATION_STRATEGY strategy);

// All allocations strategies
/**
 * @brief Allocates a memory bloc with the First-fit allocation strategy.
 * @param size The size of the memory bloc to allocate.
 * @return A pointer pointing at the memory bloc.
 */
struct memoryBloc* allocationStrategyFirstFit(int size);


/**
 * @brief Allocates a memory bloc with the Worst-fit allocation strategy.
 * @param size The size of the memory bloc to allocate.
 * @return A pointer pointing at the memory bloc.
 */
struct memoryBloc* allocationStrategyWorstFit(int size);

/**
 * @brief Allocates a memory bloc with the Best-fit allocation strategy.
 * @param size The size of the memory bloc to allocate.
 * @return A pointer pointing at the memory bloc.
 */
struct memoryBloc* allocationStrategyBestFit(int size);

/**
 * @brief Allocates a memory bloc with the Next-fit allocation strategy.
 * @param size The size of the memory bloc to allocate.
 * @return A pointer pointing at the memory bloc.
 */
struct memoryBloc* allocationStrategyNextFit(int size);

/**
 * @brief Adds a memory bloc to the memory space.
 * @param size The size of the memory bloc to be added.
 * @param index The index within the memory space at which the memory bloc will be added.
 * @param currentMemBloc The memory bloc to be added.
 */
struct memoryBloc* addMemorybloc(int size, int index, struct memoryBloc* currentMemBloc);