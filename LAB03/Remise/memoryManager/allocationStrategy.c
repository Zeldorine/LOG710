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
*     1.0   13/11/2017  TC & MN     Create file. 
*     1.1   20/11/2017  TC & MN     Add these methods :
*                                       - void setAllocationStrategy(ALLOCATION_STRATEGY strategy)
*                                       - void initmem(int size)
*                                       - struct memoryBloc* alloumem(int size)
*                                       - void liberemem(struct memoryBloc* blocToFree)
*                                       - void mergeBloc(int previousBlocIndex, int nextBlocIndex)
*                                       - int nbloclibres()
*                                       - int mem_pgrand_libre();
*                                       - int mem_small_free(int maxBlocSize);
*                                       - int mem_est_alloue(int pByte);
*                                       - void affiche_etat_memoire();
*                                       - void affiche_parametres_memoire();
*                                       - void setAllocationStrategy(ALLOCATION_STRATEGY strategy);
*     1.2   27/11/2017  TC & MN     Add these methods :
*                                       - struct memoryBloc* addMemorybloc(int size, int index, struct memoryBloc* currentMemBloc)
*                                       - struct memoryBloc* allocationStrategyNextFit(int size)
*                                       - struct memoryBloc* allocationStrategyBestFit(int size)
*                                       - struct memoryBloc* allocationStrategyWorstFit(int size)
* 
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "allocationStrategy.h"
#include "linkedList.h"
#include "logger.h"
#include "limits.h"


// Attributs
ALLOCATION_STRATEGY selectedAllocationStrategy = FIRST_FIT;
struct linkedList_type* memoryList;
int maxMemorySize = MAX_MEMORY_SIZE;

// Methods
void setAllocationStrategy(ALLOCATION_STRATEGY strategy){
    selectedAllocationStrategy = strategy;
}

void initmem(int size){
    memoryList = linkedListCreator(&memoryList);
    
    if(size >= 0){
        maxMemorySize = size;
    } else {
        char debugMsg[128];
        sprintf(debugMsg, "Cannot initialize memory with size : %d. Init to default size : %d", size, MAX_MEMORY_SIZE);
        log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    }
    
    // create a bloc for free memory
    struct memoryBloc* newBloc = malloc(sizeof(struct memoryBloc));
    newBloc->blocType = HOLE;
    newBloc->length = size;
    newBloc->start = 0;
        
    addElement(memoryList, newBloc);
}

struct memoryBloc* alloumem(int size){
    
    switch(selectedAllocationStrategy){
        case FIRST_FIT:
            return allocationStrategyFirstFit(size);
        case BEST_FIT:
            return allocationStrategyBestFit(size);
        case WORST_FIT:
            return allocationStrategyWorstFit(size);
        case NEXT_FIT:
            return allocationStrategyNextFit(size);
        default :
            log(ERROR, "allocationStrategy.c", "Allocation strategy unknow", __LINE__);
            return NULL;
    }
}

void liberemem(struct memoryBloc* blocToFree){
    char debugMsg[128];
    
    if(blocToFree == NULL){
        log(INFO, "allocationStrategy.c", "Cannot remove a null bloc", __LINE__);
        return;
    }
    
    if(blocToFree->blocType == HOLE){
        log(INFO, "allocationStrategy.c", "Cannot remove a hole bloc", __LINE__);
        return;
    }
    
    // Get the node correspondant to the memerybloc in the list
    for(int i=0; i < memoryList->size; i++){
        struct node* currentNode = get(memoryList, i);
        struct memoryBloc* currentMemBloc = (struct memoryBloc*)currentNode->element;
        
        if(blocToFree->start == currentMemBloc->start){
            struct node* previousNode = currentNode->previous;
            struct node* nextNode = currentNode->next;
            
            // remove current memory bloc
            free(currentMemBloc->blocAddress);
            currentMemBloc->blocType = HOLE;
            
            sprintf(debugMsg, "free bloc with attributs : start = %d, length = %d", currentMemBloc->start, currentMemBloc->length);
            log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
            
            // Merge with previous if necessary
            if(previousNode != NULL){
                struct memoryBloc* previousMemBloc = (struct memoryBloc*)previousNode->element;
                if(previousMemBloc->blocType == HOLE){
                    // Need to merge bloc
                    sprintf(debugMsg, "Merge two blocs : index = %d, index = %d", (i-1) % memoryList->size, i);
                    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
                    mergeBloc((i-1) % memoryList->size, i);
                    i--;
                }
            }
            
            // Merge with next if necessary
            if(nextNode != NULL){
                struct memoryBloc* nextMemBloc = (struct memoryBloc*)nextNode->element;
                if(nextMemBloc->blocType == HOLE){
                    // Need to merge bloc
                    sprintf(debugMsg, "Merge two blocs : index = %d, index = %d", i, (i+1) % memoryList->size);
                    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
                    mergeBloc(i, (i+1) % memoryList->size);
                }
            }
            
            return;
        }
    }
    
    // At this point, cannot remove the memory bloc
    sprintf(debugMsg, "Cannot remove memory bloc with attributs : size = %d, start = %d", blocToFree->length, blocToFree->start);
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
}


void mergeBloc(int previousBlocIndex, int nextBlocIndex){
    char debugMsg[128];
    sprintf(debugMsg, "Merge bloc at index : previousBlocIndex = %d, nextBlocIndex = %d", previousBlocIndex, nextBlocIndex);
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    
    struct node* previousBloc = get(memoryList, previousBlocIndex);
    struct node* nextBloc = get(memoryList, nextBlocIndex);
    
    if(previousBloc == NULL && nextBloc == NULL){
        log(INFO, "allocationStrategy.c", "Cannot merge null blocs", __LINE__);
        return;
    }
    
    struct memoryBloc* previousMemBloc = (struct memoryBloc*)previousBloc->element;
    struct memoryBloc* nextMemBloc = (struct memoryBloc*)nextBloc->element;
    
    // create a new bloc correspondant to the merge bloc
    previousMemBloc->blocType = HOLE;
    previousMemBloc->length = previousMemBloc->length + nextMemBloc->length;
    
    // remove old two blocs
    removeElementAt(memoryList, nextBlocIndex);
    free(nextMemBloc);
    
    sprintf(debugMsg, "Merge success, new bloc attribut : start = %d, length = %d", previousMemBloc->start, previousMemBloc->length);
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    
    return;
}

int nbloclibres(){
    //char debugMsg[128];
    int nbBlocFree = 0;
    
    for(int i=0; i < memoryList->size; i++){
        struct node* currentNode = get(memoryList, i);
        struct memoryBloc* currentMemBloc = (struct memoryBloc*)currentNode->element;
        
        if(currentMemBloc->blocType == HOLE){
            nbBlocFree++;
            
            /*sprintf(debugMsg, "Free memory bloc at index : %d, with attributs : start = %d, length = %d", i, currentMemBloc->start, currentMemBloc->length);
            log(INFO, "allocationStrategy.c", debugMsg, __LINE__);*/
        }
    }
    
    return nbBlocFree;
}

int nblocalloues(){
    //char debugMsg[128];
    int nbBlocUsed = 0;
    
    for(int i=0; i < memoryList->size; i++){
        struct node* currentNode = get(memoryList, i);
        struct memoryBloc* currentMemBloc = (struct memoryBloc*)currentNode->element;
        
        if(currentMemBloc->blocType == PROCESS){
            nbBlocUsed++;
            
            /*sprintf(debugMsg, "Process memory bloc at index : %d, with attributs : start = %d, length = %d", i, currentMemBloc->start, currentMemBloc->length);
            log(INFO, "allocationStrategy.c", debugMsg, __LINE__);*/
        }
    }
    
    return nbBlocUsed;
}

int memlibre(){
    int freeMemorySize = 0;
    
    for(int i=0; i < memoryList->size; i++){
        struct node* currentNode = get(memoryList, i);
        struct memoryBloc* currentMemBloc = (struct memoryBloc*)currentNode->element;
        
        if(currentMemBloc->blocType == HOLE){
            freeMemorySize += currentMemBloc->length;
        }
    }
    
    return freeMemorySize;
}

int mem_pgrand_libre(){
    int maxFreeSize = 0;
    
    for(int i=0; i < memoryList->size; i++){
        struct node* currentNode = get(memoryList, i);
        struct memoryBloc* currentMemBloc = (struct memoryBloc*)currentNode->element;
        
        if(currentMemBloc->blocType == HOLE && currentMemBloc->length > maxFreeSize){
            maxFreeSize = currentMemBloc->length;
        }
    }
    
    return maxFreeSize;
}

int mem_small_free(int maxBlocSize){
    int nbBloc = 0;
    
    for(int i=0; i < memoryList->size; i++){
        struct node* currentNode = get(memoryList, i);
        struct memoryBloc* currentMemBloc = (struct memoryBloc*)currentNode->element;
        
        if(currentMemBloc->blocType == HOLE && currentMemBloc->length < maxBlocSize){
            nbBloc++;
        }
    }
    
    return nbBloc;
}

int mem_est_alloue(int pByte){
    char debugMsg[128];
    
    for(int i=0; i < memoryList->size; i++){
        struct node* currentNode = get(memoryList, i);
        struct memoryBloc* currentMemBloc = (struct memoryBloc*)currentNode->element;
        
        if(currentMemBloc->start <= pByte && pByte < (currentMemBloc->start + currentMemBloc->length)){
            sprintf(debugMsg, "Byte : %d, is in the bloc memory at index %d with attributs : bloc type : %s, start = %d, length = %d",pByte , i,  getBlocTypeName(currentMemBloc->blocType), currentMemBloc->start, currentMemBloc->length);
            log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
            
            if(currentMemBloc->blocType == PROCESS) {
                return 1;
            } else {
                return FALSE;
            }
        }
    }
    
    return FALSE;
}

void affiche_etat_memoire(){
    if(isEmpty(memoryList)){
        log(INFO, "allocationStrategy.c", "List is empty", __LINE__);
    } else {
        char debugMsg[128];
        sprintf(debugMsg, "There are %d element", memoryList->size);
        log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
                
        for(int i=0; i < memoryList->size; i++){
            struct node* currentNode = get(memoryList, i);
            struct memoryBloc* currentMemBloc = (struct memoryBloc*)currentNode->element;  
            
            sprintf(debugMsg, "Memory bloc at index %d, bloc type : %s, start = %d, length = %d", i, getBlocTypeName(currentMemBloc->blocType), currentMemBloc->start, currentMemBloc->length);
            log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
        }
    }
}

void affiche_parametres_memoire(int maxBlocSize){
    char debugMsg[128];
    sprintf(debugMsg, "Memory parameters - Total size :  %d", maxMemorySize);
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    
    sprintf(debugMsg, "Total free bloc :  %d", nbloclibres());
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    
    sprintf(debugMsg, "Total used bloc :  %d", nblocalloues());
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    
    sprintf(debugMsg, "Total free memory :  %d", memlibre());
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);

    sprintf(debugMsg, "Max free memory bloc size :  %d", mem_pgrand_libre());
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);

    if(maxBlocSize > 0){
        sprintf(debugMsg, "Available bloc with a size less than %d :  %d", maxBlocSize, mem_small_free(maxBlocSize));
        log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    }
}

char* getBlocTypeName(BLOC_TYPE type){
    switch(type){
        case PROCESS :
            return "Process";
        case HOLE :
            return "HOLE";
        default :
            return "TYPE UNKNOW";
    }
}
    

// All allocations strategies
struct memoryBloc* allocationStrategyFirstFit(int size){
    log(INFO, "allocationStrategy.c", "Add a new memory bloc with first fit strategy", __LINE__);
    int nbBloc = memoryList->size;
    
    for(int i=0; i<nbBloc; i++){
        struct node* currentNode = get(memoryList, i);
        struct memoryBloc* currentMemBloc = (struct memoryBloc*) currentNode->element;
        
        if(currentMemBloc->blocType == HOLE && currentMemBloc->length >= size){
            return addMemorybloc(size, i, currentMemBloc);
        } else {
            continue;
        }
    }
    
    // At this point, the systeme cannot allocate memory for the new process
    char debugMsg[128];
    sprintf(debugMsg, "Cannot allocate memory with size : %d", size);
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    return NULL;
}

struct memoryBloc* allocationStrategyWorstFit(int size){
    log(INFO, "allocationStrategy.c", "Add a new memory bloc with worst fit strategy", __LINE__);
    char debugMsg[128];
    int nbBloc = memoryList->size;
    int max = -1;
    int indexToInsert = -1;
    struct memoryBloc* holeBloc;
    
    for(int i=0; i<nbBloc; i++){
        struct node* currentNode = get(memoryList, i);
        struct memoryBloc* currentMemBloc = (struct memoryBloc*) currentNode->element;
        
        if(currentMemBloc->blocType == HOLE && currentMemBloc->length >= size && (currentMemBloc->length - size) > max){
            holeBloc = currentMemBloc;
            max = currentMemBloc->length - size;
            indexToInsert = i;  
        }
    }
    
    if(indexToInsert == -1) {
        // At this point, the systeme cannot allocate memory for the new process
        sprintf(debugMsg, "Cannot allocate memory with size : %d", size);
        log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
        return NULL;
    }
    
    return addMemorybloc(size, indexToInsert, holeBloc);
}

struct memoryBloc* allocationStrategyBestFit(int size){
    log(INFO, "allocationStrategy.c", "Add a new memory bloc with best fit strategy", __LINE__);
    int nbBloc = memoryList->size;
    int min = INT_MAX;
    int indexToInsert = -1;
    struct memoryBloc* holeBloc;
    
    for(int i=0; i<nbBloc; i++){
        struct node* currentNode = get(memoryList, i);
        struct memoryBloc* currentMemBloc = (struct memoryBloc*) currentNode->element;
        
        if(currentMemBloc->blocType == HOLE && currentMemBloc->length >= size && (currentMemBloc->length - size) < min){
            holeBloc = currentMemBloc;
            min = currentMemBloc->length - size;
            indexToInsert = i;  
        }
    }
    
    if(indexToInsert == -1) {
        // At this point, the systeme cannot allocate memory for the new process
        char debugMsg[128];
        sprintf(debugMsg, "Cannot allocate memory with size : %d", size);
        log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
        return NULL;
    }
    
    return addMemorybloc(size, indexToInsert, holeBloc);
}

struct memoryBloc* allocationStrategyNextFit(int size){
    log(INFO, "allocationStrategy.c", "Add a new memory bloc with next fit strategy", __LINE__);
    struct node* lastNodeInserted = memoryList->lastInserted;
    int nbBloc = memoryList->size;
    char debugMsg[128];
    
    for (int i=0; i<nbBloc; i++){
        struct node* currentNode = lastNodeInserted->next;
        struct memoryBloc* currentMemBloc = (struct memoryBloc*) currentNode->element;
        
        if(currentMemBloc->blocType == HOLE && currentMemBloc->length >= size){
            return addMemorybloc(size, (((i + memoryList->lastInsertedIndex) + 1) % memoryList->size), currentMemBloc);
        } 
        
        lastNodeInserted = currentNode;
    }
    
    // At this point, the systeme cannot allocate memory for the new process
    sprintf(debugMsg, "Cannot allocate memory with size : %d", size);
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    return NULL;
}

struct memoryBloc* addMemorybloc(int size, int index, struct memoryBloc* currentMemBloc){
    // create bloc
    struct memoryBloc* newBloc = malloc(sizeof(struct memoryBloc));
    newBloc->blocType = PROCESS;
    newBloc->length = size;
    newBloc->start = currentMemBloc->start;
    newBloc->blocAddress = malloc(size);
    
    addElementAt(memoryList, newBloc, index);
    char debugMsg[128];
    sprintf(debugMsg, "Add a new memory bloc with attributs : size = %d, start = %d", size, newBloc->start);
    log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    
    currentMemBloc->length = currentMemBloc->length-size;
    
    if(currentMemBloc->length == 0){
        //No more space in this bloc, remove it
        removeElementAt(memoryList, index+1);
        free(currentMemBloc);
        log(INFO, "allocationStrategy.c", "Remove Hole bloc because its size is 0", __LINE__);
    } else {
        currentMemBloc->start = newBloc->start + size;
        sprintf(debugMsg, "Update hole memory bloc with attributs : size = %d, start = %d", currentMemBloc->length, currentMemBloc->start);
        log(INFO, "allocationStrategy.c", debugMsg, __LINE__);
    }
    
 
    return newBloc;  
}