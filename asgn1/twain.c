#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "linkedl.h"
#include "linkedl.c"

#define TWAINFILE "twain-cleaned.txt"

void sort(ListNode *head, int length);
void sort_begin(ListNode *head, int length);

int main(int argc, char **argv) {

  if (argc != 3) {
    printf("enter three arguments\n");
    return 0;
  }

  FILE *twainfile = fopen(TWAINFILE, "r");      // opens twain file for reading
  if (twainfile == NULL) {
    printf("failed to open twain file\n");
    return 0;
  }
  
  char *word = (char *)malloc(128 * sizeof(char));
  if (!word) {
    return 0;
  }

  // https://www.cs.cmu.edu/~ab/15-123S09/lectures/Lecture%2011%20%20-%20%20Array%20of%20Linked%20Lists.pdf
  // ^ I used the link above to understand how to declare an array of alphabet heads for the linked list
  // Creating an array of heads
  ListNode *heads[26];
  for (int i = 0; i < 26; i++) {
    heads[i] = NULL;
    heads[i] = ll_node_create();
  }
  
  

  while(fscanf(twainfile, "%s", word) != EOF) {
    bool in_alph = false;
    int index = 0;
    char letter = word[0];
    if ((97 <= letter) && (letter <= 122)) {
      index = letter - 97;
      in_alph = true;
    } 

    if (in_alph == true) {
      ListNode *inc_or_ins = ll_lookup(heads[index], word);
      if (inc_or_ins == NULL) {
        ll_insert(heads[index], word);
        heads[index]->freq += 1;
      } else {
        inc_or_ins->freq += 1;
      }
    }
  }

  
  
  // for loop to sort all 26 linked lists;
  for (int i = 0; i < 26; i++) {
    int head_length = heads[i]->freq;
    sort_begin(heads[i], head_length);
  }


  FILE *infile = fopen(argv[1], "r");      // opens input file for reading
  if (infile == NULL) {
    printf("failed to open input file\n");
    return 0;
  }

  FILE *outfile = fopen(argv[2], "w");
  if (outfile == NULL) {
    printf("failed to open output file\n");
    return 0;
  }

  char *input_let = (char *)malloc(128 * sizeof(char));
  if (!input_let) {
    return 0;
  }
  
  int index_search;

  

  while (fscanf(infile, "%s %d", input_let, &index_search) != EOF) {
    int head_index = input_let[0] - 97;
    ListNode *print_node = heads[head_index]->next;
    if (index_search < heads[head_index]->freq) {
      for (int i = 0; i < index_search; i++) {
        print_node = print_node->next;
      }
      fprintf(outfile, "%s %d\n", print_node->word, print_node->freq);
    } else {
      fprintf(outfile, "-\n");
    }
  }

  free(input_let);
  free(word);
  fclose(twainfile);
  fclose(infile);

}

// This sort method is almost identical to the void sort() function
// Except this method starts the sorting at the beginning of the list instead of the end

void sort_begin(ListNode *head, int length) {
  ListNode *swap_node = ll_node_create();

  for (int i = 0; i < length; i++) {

    ListNode *prev_node = head->next;
    ListNode *curr_node = prev_node->next;
    int j = length-1;

    while (j > i) {
      if (curr_node->freq > prev_node->freq) {
        swap_node->freq = curr_node->freq;
        strcpy(swap_node->word, curr_node->word);
        curr_node->freq = prev_node->freq;
        strcpy(curr_node->word, prev_node->word);
        prev_node->freq = swap_node->freq;
        strcpy(prev_node->word, swap_node->word);
      }
      
      if (curr_node->freq == prev_node->freq) {
        // if curr node appears before prev node lexographically
        if (strcmp(curr_node->word, prev_node->word) < 0) {
          swap_node->freq = curr_node->freq;
          strcpy(swap_node->word, curr_node->word);
          curr_node->freq = prev_node->freq;
          strcpy(curr_node->word, prev_node->word);
          prev_node->freq = swap_node->freq;
          strcpy(prev_node->word, swap_node->word);
        }
      }
      

      // check if they are equal
      j -= 1;
      // subtract j
      // loop to calculate the NEW previous node.
      prev_node = curr_node;
      curr_node = curr_node->next;
      
    }

  }

  free(swap_node->word);
  free(swap_node);

}

// THIS SORT METHOD WORKS but takes TOO long . 
// starts from the end of the list and works it's way up to the beginning
void sort(ListNode *head, int length) {
  printf("inside sort\n");
  ListNode *prev_node = head->next;
  ListNode *curr_node = prev_node->next;
  ListNode *swap_node = ll_node_create();

  for (int i = 0; i < length; i++) {
    printf("i: %d\n", i);
    //printf("i = %d\n", i);

    int j = length-1;

    while (j > i) {
      int j_min = j-1;
    
      prev_node = head->next;
      // loop to get to end:
      for (int x = 0; x < j_min; x++) {
        prev_node = prev_node->next;
      }
      curr_node = prev_node->next;
      
      if (curr_node->freq > prev_node->freq) {
        swap_node->freq = curr_node->freq;
        strcpy(swap_node->word, curr_node->word);
        curr_node->freq = prev_node->freq;
        strcpy(curr_node->word, prev_node->word);
        prev_node->freq = swap_node->freq;
        strcpy(prev_node->word, swap_node->word);
      }
      
      if (curr_node->freq == prev_node->freq) {
        // if curr node appears before prev node lexographically
        if (strcmp(curr_node->word, prev_node->word) < 0) {
          swap_node->freq = curr_node->freq;
          strcpy(swap_node->word, curr_node->word);
          curr_node->freq = prev_node->freq;
          strcpy(curr_node->word, prev_node->word);
          prev_node->freq = swap_node->freq;
          strcpy(prev_node->word, swap_node->word);
        }
      }
      

      // check if they are equal
      j -= 1;
      // subtract j
      // loop to calculate the NEW previous node.
      
    }

  }

  free(swap_node->word);
  free(swap_node);

}
