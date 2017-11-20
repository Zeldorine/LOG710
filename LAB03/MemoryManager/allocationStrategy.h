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

// ENUM
enum BLOC_TYPE {
    HOLE,
    PROCESS;
}

// STRUCTURE PART
struct memoryBloc {
    unsigned long blocAddress;
    enum BLOC_TYPE blocType = HOLE;
    int start;
    int length;
}

/**
 * @brief 
 */
void initmem();

void alloumem();

void liberemem();

void nbloclibres();

void nblocalloues;

void memlibre();

void mem_pgrand_libre();

void mem_small_free();

void mem_est_alloue();

void affiche_etat_memoire();

void affiche_parametres_memoire();