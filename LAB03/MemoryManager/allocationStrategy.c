 /***********************************************************************
* FILENAME : allocationStrategy.h
*
* DESCRIPTION : Lab 03
* 				Contains the implementation to manage (create and remove) bloc memory.
*               There are 4 implementations :
*                   1- first-fit
*                   2- best-fit
*                   3- worst-fit
*                   4- next-fit
*
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

#include "allocationStrategy.h"

ALLOCATION_STRATEGY selectedAllocationStrategy = FIRST_FIT;


void setAllocationStrategy(ALLOCATION_STRATEGY strategy){
    selectedAllocationStrategy = strategy;
}

void initmem(){
    
}

struct memoryBloc* alloumem(){
    
}

void liberemem(struct memoryBloc* blocToFree){
    
}

int nbloclibres(){
    
}

int nblocalloues(){
    
}

int memlibre(){
    
}

int mem_pgrand_libre(){
    
}

int mem_small_free(int maxBlocSize){
    
}

void mem_est_alloue(int pByte){
    
}

void affiche_etat_memoire(){
    
}

void affiche_parametres_memoire(){
    
}


// All allocations strategies

struct memoryBloc* allocationStrategyFirstFit(){
    
}

struct memoryBloc* allocationStrategyWorstFit(){
    
}

struct memoryBloc* allocationStrategyBestFit(){
    
}

struct memoryBloc* allocationStrategyNextFit(){
    
}