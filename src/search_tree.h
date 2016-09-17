#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

/**
   Search tree node, contains a correct spelling (if one exists!) and
   26 pointers to the next nodes in the tree.
 */
struct Search_Tree_Node {
  char* correct_spelling;
  struct Search_Tree_Node* next[26];
};
typedef struct Search_Tree_Node Search_Tree_Node;

/**
    Recursively frees all the nodes in the tree.
    @param[in] node The root of the tree to free.
*/
void free_search_tree(Search_Tree_Node* node);

/**
   Sets all the pointers in the next[] array to 0 
   @param[in] stn The Search_Tree_Node to init
*/
void init_stn_next_pointers(Search_Tree_Node* stn);

/**
    Replace a given word with the correction found in the dictionary.
    @param[in] root_node The dictionary to use
    @param[int] The string to check
    @return The replaced string, or NULL if no correction was found
*/
char* replace_word(Search_Tree_Node* root_node, char* str);


#endif
