/* Aldrin Gordon 18340587
COMP1000 UNIX AND C PROGRAMMING: SEMESTER 1, 2018 - ASSIGNMENT

linkedList.c file, contains functions to create / destroy / manipulate / access a generic linked list, defined in list.h

based off Worksheet 06: Structs Question 2: Linked Lists
code found in linked_list.c */
#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "list.h"
#include "io.h"

/* Create an empty linked list with default fields
@param LinkedList** list - a pointer to the linkedlist pointer to create */
void createLinkedList(LinkedList** list)
{
	*list = (LinkedList*)malloc(sizeof(LinkedList));
	(*list)->head = NULL;
	(*list)->size = 0;
}

/* Insert an element at the start of the list
@param LinkedList** list - the list to insert the element into
@param GuideEntry* entry - the data to insert into the linked list*/
void insertStartElement(LinkedList** list, GuideEntry* entry)
{
/*	Create new Node and allocate it memory
	Create new TVGuideEntry struct that Node points to and allocate it memory
	Copy contents of imported entry into new TVGuideEntry */

	LinkedListNode* newNode;
	GuideEntry* newEntry;
	newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	newEntry = (GuideEntry*)malloc(sizeof(GuideEntry));
	*newEntry = *entry;
	newNode->data = newEntry;

/*	Point newNode to first element of list */
	if((*list)->head == NULL)
	{
		newNode->next = NULL;
	}
	else
	{
		newNode->next = (*list)->head;
	}

/* 	Update list head and increment size */
	(*list)->head = newNode;
	(*list)->size++;
}

/* Recursively free the nodes of a linked list and their data
@param LinkedListNode* node - the node to be freed */
void freeNode(LinkedListNode* node)
{
	if(node != NULL)
	{
		freeNode(node->next);
		free(node->data);
		free(node);
	}
}

/* Free the linked list after freeing all nodes of the list
@param LinkedList* list - the list to be freed */
void freeList(LinkedList* list)
{
	freeNode(list->head);
	free(list);
}

void printNode(LinkedListNode* node)
{
	if(node != NULL)
	{
		printNode(node->next);
		printf("***\nName: %sDay: %s\nTime: %d:%d\n", getName(node->data), getDay(node->data), getHour(node->data), getMin(node->data));
/*		printf("Node Memory Location: %d\n", node);
		printf("Data Memory Location: %d\n", node->data); */
	}
}

void printList(LinkedList* list)
{
	if((list->head) != NULL)
	{
		printNode(list->head);
	}
}

void printSingleNode(LinkedListNode* node)
{
	printf("Name: %sDay: %s\nTime: %d:%d\n***\n", getName(node->data), getDay(node->data), getHour(node->data), getMin(node->data));
}
