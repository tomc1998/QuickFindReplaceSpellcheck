#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "search_tree.h"
#include "search_tree_parser.h"

Search_Tree_Node* parse_dictionary(const char** words,
                                   char** corrections,
                                   const int num_words) {
  Search_Tree_Node* root = (Search_Tree_Node*)malloc(sizeof(Search_Tree_Node));
  Search_Tree_Node* curr_node = root;
  unsigned ii = 0;
  unsigned jj = 0;
  unsigned ord = 0;

  init_stn_next_pointers(root);
  root->correct_spelling = 0;
  for(; ii < num_words; ++ii) {
    curr_node = root;
    const char* w = words[ii];
    jj = 0;
    while(w[jj] != 0) {
      ord = (int)w[jj] - 97;
      if (curr_node->next[ord] == NULL) {
        curr_node->next[ord] =
          (Search_Tree_Node*) malloc(sizeof(Search_Tree_Node));
        init_stn_next_pointers(curr_node->next[ord]);
        curr_node->next[ord]->correct_spelling = 0;
      }
      curr_node = curr_node->next[ord];
      ++jj;
    }
    curr_node->correct_spelling = corrections[ii];
  }
  return root;
}

void lex_dictionary(char* dict_data, char** words,
                    char** corrections) {
  char* token = strtok(dict_data, "\n");
  int ii = 0;
  int jj = 0;
  while(token != NULL) {
    if (token[0] == '\n') continue;
    words[ii] = token;
    jj = 0;
    while(token[jj] != 0 && token[jj] != '|') {
      ++jj;
    }
    token[jj] = 0;
    corrections[ii] = token + jj+1;
    
    token = strtok(NULL, "\n");
    ++ii;
  }
}

unsigned count_num_words(const char* dict_data, int data_len) {
  unsigned num_words = 0;
  int ii = 0;
  for (; ii < data_len; ++ii) {
    if (dict_data[ii] == '\n') {++num_words;}
  }
  return num_words;
}
