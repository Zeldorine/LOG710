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

#define SUCCESS 0
#define ERR_OUT_OF_BOUNDS 1
#define ERR_REMOVE_NODE 2
#define ERR_ADD_NODE 3
#define ERR_GET_NODE 3

struct node {
    void* element;
    struct node* previous;
    struct node* next;
};

struct linkedList_type{
    int size;
    struct node* head;
    struct node* tail;
    struct node* lastInserted;
    int lastInsertedIndex;
};

/**
 * @brief create a linkedlist
 * @return a pointer on the new linkedlist
 */
struct linkedList_type* linkedListCreator();

/**
 * @brief Inserts the specified element in this list. Shifts the element currently at that position (if any) and any subsequent elements to the right (adds one to their indices)
 * @param list - The list to add an element
 * @param element - element to be inserted
 * @return Return true is success, otherwise, false
 */
int addElement(struct linkedList_type* list, void* element);

/**
 * @brief Inserts the specified element at the specified position in this list. Shifts the element currently at that position (if any) and any subsequent elements to the right (adds one to their indices)
 * @param list - The list to add an element
 * @param element - element to be inserted
 * @param index - index at which the specified elements is to be inserted
 * @return Return true is success, otherwise, false
 */
int addElementAt(struct linkedList_type* list, void* element, int index);

/**
 * @brief Removes the element at the specified position in this list. Shifts any subsequent elements to the left (subtracts one from their indices).
 * @param list - The list to add an element
 * @param index - the index of the element to be removed
 * @return Return true is success, otherwise, false
 */
int removeElementAt(struct linkedList_type* list, int index);

/**
 * @brief Returns the element at the specified position in this list
 * @param list - The list to get an element
 * @param index - index of the element to return
 * @return the element at the specified position in this list
 */
struct node* get(struct linkedList_type* list, int index);

/**
 * @brief Returns true if this collection contain no elements. This implementation returns list->size == 0
 * @param list - the list to verify if it's empty
 * @return true if this collection contains no element
 */
int isEmpty(struct linkedList_type* list);

/**
 * @brief Returns the number of elements in this list
 * @param list - The list to get the size
 * @return the number of elements in this list
 */
int size(struct linkedList_type* list);
