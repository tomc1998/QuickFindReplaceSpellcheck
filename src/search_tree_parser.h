#ifndef SEARCH_TREE_PARSER_H
#define SEARCH_TREE_PARSER_H

struct Search_Tree_Node;
typedef struct Search_Tree_Node Search_Tree_Node;

/**
   Splits the dictionary into words. Dict_data must be kept intact as
   no memory is copied.
   @param[in] dict_data The dictionary data
   @param[out] words The list of words split out of the dictionary
   @param[out] words The list of corrections split out of the dictionary
*/
void lex_dictionary(char* dict_data, char** words,
                    char** corrections);

/**
   Parses the dictionary into a tree. Must keep dict_data intact
   still, but words may be freed after this operation. 
   @param[in] words The words, obtain from lex_dictionary
   @param[in] words The corresponding correction to the word, from lex_dictionary
   @param[out] num_words The number of words there are in the words array.
*/
Search_Tree_Node* parse_dictionary(const char** words,
                                   char** corrections,
                                   const int num_words);


/**
   Counts the words separated by \n 
*/
unsigned count_num_words(const char* dict_data, int data_len);

#endif
