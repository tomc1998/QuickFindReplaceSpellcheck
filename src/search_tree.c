#include "search_tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void free_search_tree(Search_Tree_Node* node) {
  if (node == NULL) return;
  int ii = 0;
  for (; ii < 26; ++ii) {
    free_search_tree(node->next[ii]);
  }
  free(node);
}

void init_stn_next_pointers(Search_Tree_Node* stn) {
  int ii = 0;
  for (; ii < 26; ++ii) {
    stn->next[ii] = 0;
  }
}

char* replace_word(Search_Tree_Node* root_node, char* str) {
  int ii = 0;
  unsigned ord;
  char* replacement = 0;
  Search_Tree_Node* curr_node = root_node;
  while(str[ii] != 0) {
    if (str[ii] < 65 ||
        (str[ii] > 90 && str[ii] < 97) ||
        str[ii] > 122) {
      // Not an ascii char
      ++ii;
      continue;
    }
    if (str[ii] < 97) { // UCase
      ord = (int)str[ii] - 65;
    }
    else { // LCase
      ord = (int)str[ii] - 97;
    }
    if (curr_node->next[ord] == NULL) {
      return 0;
    }
    curr_node = curr_node->next[ord];
    ++ii;
  }
  if (curr_node->correct_spelling) {
    // So we found a correct spelling, now we need to convert
    // characters to uppercase / lowercase in the same pattern as the
    // input string.
    int input_string_len = strlen(str);
    replacement = (char*)malloc(input_string_len);
    // First, copy the replacement string into replacement
    memcpy(replacement, curr_node->correct_spelling, input_string_len);
    // Now loop over the original characters and modify replacement
    // based on case
    int ii = 0;
    char c;
    for (; ii < input_string_len; ++ii) {
      c = str[ii];
      if (str[ii] <= 90) { // UCase
        replacement[ii] -= 32;
      }
      // No need to convert to lowercase, all dictionary entries are
      // assumed to be lcase already.
    }
  }
  return replacement;
}
