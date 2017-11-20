 /***********************************************************************
* FILENAME : linkedList.h
*
* DESCRIPTION : Lab 03
* 				The data structure to save and manage memory bloc.

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
*     1.0   13/11/2017  TC & MN     Create list and first implementation of these methods :
*                                       - struct linkedList linkedList();
*                                       - struct linkedList linkedList(int capacity);
*                                       - int addElement(struct linkedList* list, void* element);
*                                       - int addElementAt(struct linkedList* list, void* element, int index);
*                                       - int removeElementAt(struct linkedList* list, int index);
*                                       - int removeElement(struct linkedList* list, void* element);
*                                       - void* get(struct linkedList* list, int index);
*                                       - int isEmpty(struct linkedList* list);
*                                       - int isFull(struct linkedList* list);
*                                       - int size(struct linkedList* list);
*                                       - void printElement(struct linkedList* list);
* 
* 
*
*/

#include "common.h"
#include "logger.h"

#define SUCCESS 0
#define ERR_OUT_OF_BOUNDS 1
#define ERR_REMOVE_NODE 2
#define ERR_ADD_NODE 3
#define ERR_GET_NODE 3
#define NB_BLOC_SIZE 128

struct node {
    void* element;
    struct node* previous;
    struct node* next;
};

struct linkedList_type{
    int capacity;
    int size;
    struct node* head;
    struct node* tail;
};

struct linkedList_type* linkedListCreator();

struct linkedList_type* linkedListCreatorWithCapacity(int capacity);

int addElement(struct linkedList_type* list, void* element);

int addElementAt(struct linkedList_type* list, void* element, int index);

int removeElementAt(struct linkedList_type* list, int index);

struct node* get(struct linkedList_type* list, int index);

int isEmpty(struct linkedList_type* list);

int isFull(struct linkedList_type* list);

int size(struct linkedList_type* list);
