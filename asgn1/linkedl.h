#ifndef __LL_H__
#define __LL_H__

#ifndef NIL
#define NIL (void *)0
#endif

#include <stdbool.h>

// If flag is set, ListNodes that are queried are moved to the front


typedef struct ListNode ListNode;

//
// Struct definition of a ListNode.
//
// word: contains word of node
// freq: contains the number of times the word appears in the text
//
struct ListNode {
  char *word;
  int freq;
  ListNode *next;
};

//
// Constructor for a ListNode
//
//
ListNode *ll_node_create();


//
// Destructor for a ListNode
//
// n: The ListNode to free
//
void ll_node_delete(ListNode *n);


//
// Destructor for a linked list of ListNodes
//
// head: The head of the linked list
//
void ll_delete(ListNode *head);

//
// Creates and inserts a ListNode into a linked list
//
// head: The head of the linked list to insert in
// inword: word to insert in the linked list
//
ListNode *ll_insert(ListNode *head, char *inword);

//
// Searches for a specific key in a linked list
// Returns the ListNode if found and NULL otherwise
//
// head: The head of the linked list to search in
// inword: The word to search for
//
ListNode *ll_lookup(ListNode *head, char *inword);

#endif
