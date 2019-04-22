/* Aldrin Gordon 18340587
COMP1000 UNIX AND C PROGRAMMING: SEMESTER 1, 2018 - ASSIGNMENT

list.h

contains structures for a generic linked list as well as the functions for creating / destroying / manipulating / accessing the list */

#ifndef LIST_H
#define LIST_H
typedef struct Node
{
	void* data;
	struct Node* next;
} LinkedListNode;

typedef struct
{
	int size;
	LinkedListNode* head;
} LinkedList;
#endif

void createLinkedList(LinkedList** list);
void insertStartElement(LinkedList** list, GuideEntry* entry);
void freeList(LinkedList* list);
void printList(LinkedList* list);
void printSingleNode(LinkedListNode* node);
