#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "linkedl.h"

//
// Constructor for a ListNode
//
//

ListNode *ll_node_create() {

  // malloc space for ListNode
  ListNode *l = (ListNode *)malloc(sizeof(ListNode));

  if (!l) {                                      // Check if malloc succeeded
    free(l);
    l = NULL;
    return (ListNode *)NIL;
  }

  l->word = (char *)malloc(128 * sizeof(char));  // malloc space for *word
  // Check if malloc succeeded
  if (!l->word) {
    return 0;
  }

  l->freq = 0;            // set frequency to 0

  l->next = NULL;         // set next node to NULL

  return l;

}


//
// Destructor for a ListNode
//
// n: The ListNode to free
//
void ll_node_delete(ListNode *n) {

  free(n->word);
  free(n);

}


//
// Destructor for a linked list of ListNodes
//
// head: The head of the linked list
//
void ll_delete(ListNode *head) {
  int len = head->freq;
  ListNode *to_delete = head->next;
  ListNode *delete_next = to_delete->next;
  for (int i = 0; i < len; i++) {
    ll_node_delete(to_delete);
    to_delete = delete_next;
    delete_next = delete_next->next;
  }
}

//
// Creates and inserts a ListNode into a linked list
//
// head: The head of the linked list to insert in
// inword: word to insert in the linked list
//
ListNode *ll_insert(ListNode *head, char *inword) {
  
  ListNode *to_add = ll_node_create();      // create a listnode to add
  strcpy(to_add->word, inword);             // copy inword to listnode->word
  to_add->freq += 1;                        // increase frequency to 1

  if (head->next == NULL) {                 // if there are no words in head, set head->next = newest node
    head->next = to_add;
    return to_add;                          // return node created
  } else {
    ListNode *curr_node = head->next;       // if words exist in the list, iterate through the list until
    while (curr_node != NULL) {             // the last node is reached
      if (curr_node->next != NULL) {
        curr_node = curr_node->next;
      } else {
        break;
      }
    }
    curr_node->next = to_add;               // add node after last node in list
    return to_add;                          // return the node
  }
  
}

//
// Searches for a specific key in a linked list
// Returns the ListNode if found and NULL otherwise
//
// head: The head of the linked list to search in
// inword: The word to search for
//

ListNode *ll_lookup(ListNode *head, char *inword) {
  
  ListNode *curr_node = head->next;         // set current node to first node in list
  if (curr_node == NULL) {
    return NULL;                            // if no words in list, return NULL
  } else {
    while (curr_node != NULL) {             // loop through linked list and compare each word to inword
      if (strcmp(curr_node->word, inword) == 0) {
        return curr_node;                   // if word is found, return node
      } 
      curr_node = curr_node->next;
    }
    return NULL;                            // else return NULL
  }
  
}

