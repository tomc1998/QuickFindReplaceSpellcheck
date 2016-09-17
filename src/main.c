#include "search_tree.h"
#include "search_tree_parser.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
   Corrects a given text using a dictionary.
   @param[in] root The dictionary to use.
   @param[in] text The text to process, must be NUL terminated.
   @return The corrected text
 */
char* correct_text(Search_Tree_Node* root, char* text) {
  unsigned corrected_text_len = strlen(text);
  char* corrected_text = (char*) calloc(corrected_text_len, 1);
  char* word_boundaries = " \t\"\'\n.,:;?!";
  char* curr_text_pos  = text; // Position in text to correct
  char* curr_ctext_pos = corrected_text; // Position in corrected text
  char* next_wb; // next word boundary
  char* tmp;
  int ii = 0;
  while(1) {
    // Find first word boundary char
    for(ii = 0;;++ii) {
      // Are we at a word boundary?
      if (strrchr(word_boundaries, curr_text_pos[ii]) != 0
          || curr_text_pos[ii] == 0) {
        next_wb = curr_text_pos + ii;
        break;
      }
    }
    
    // Allocate space for word temporarily, then correct it
    unsigned size = ii+1;
    if (size > 1) {
      tmp = (char*) malloc(size);
      memcpy(tmp, curr_text_pos, size-1);
      tmp[size-1] = 0;
      char* replacement = replace_word(root, tmp);
      if (!replacement) {
        replacement = tmp;
      }
      unsigned replacement_len = strlen(replacement);
      // Resize buffer if necessary
      if ((unsigned) (curr_ctext_pos + replacement_len + 1 - corrected_text) <
          corrected_text_len) {
        unsigned diff = (unsigned) (curr_ctext_pos - corrected_text);
        corrected_text_len = diff + 256;
        char* new_corrected_text = (char*)calloc(corrected_text_len, 1);
        memcpy(new_corrected_text, corrected_text, corrected_text_len);
        free(corrected_text);
        corrected_text = new_corrected_text;
        curr_ctext_pos = new_corrected_text + diff;
      }
      // Copy word into corrected text buffer
      memcpy(curr_ctext_pos, replacement, replacement_len);
      curr_ctext_pos += replacement_len;
      if (replacement != tmp) {
        free(replacement);
      }
      free(tmp);
    }
    // Set the WB char
    curr_ctext_pos[0] = next_wb[0];
    ++curr_ctext_pos;
    // Update curr text pos
    if (next_wb[0] == 0) break;
    curr_text_pos = next_wb+1;
  }
  return corrected_text;
}

/**
   Main method
*/
int main(int argc, char** argv) {
  printf("\n");
  if (argc < 2) {
    printf("\
Please enter an input file!\n \
\n \
spellcheck [input file]\n");
    return 1;
  }
  // Load in dictionary from disk
  char* dir_name = get_curr_dir_name();
  char* filename = "dictionary.txt";
  char* path = malloc(strlen(dir_name) + strlen(filename) + 1);
  strcpy(path, dir_name);
  strcat(path, filename);
  printf("%s\n", path);
  free(dir_name);
  int data_len;
  char* dict_data = read_file(path, &data_len);

  // Count the word/correction pairs in the dictionary
  unsigned num_words = count_num_words(dict_data, data_len);

  // Lex the pairs into arrays
  printf("Parsing words from file...\n");
  char** words = (char**) malloc(sizeof(char*)*num_words);
  char** corrections = (char**) malloc(sizeof(char*)*num_words);
  lex_dictionary(dict_data, words, corrections);

  // Parse the pairs into a search tree
  printf("Generating search tree\n");
  Search_Tree_Node* root = parse_dictionary((const char**) words, corrections, num_words);

  // Free the word / correction pointers, we don't need these anymore
  free(words);
  free(corrections);

  printf("\n");
  // Read some text...
  printf("Reading text...\n");
  int text_len;
  char* file = read_file(argv[1], &text_len);
  // This is really messy & slow, but realloc for 1 extra byte's space
  // and add a NUL to the end
  char* text = (char*)malloc(text_len+1);
  memcpy(text, file, text_len);
  text[text_len] = 0;
  free(file);
  // Correct the text!
  printf("Correcting text...\n");
  char* corrected = correct_text(root, text);
  // Write text to file
  printf("Writing text to file\n\n");
  // Gen filename
  const char* corrected_extension = ".corrected";
  char* out_filename = (char*)malloc(strlen(argv[1])+strlen(corrected_extension));
  strcpy(out_filename, argv[1]);
  strcat(out_filename, corrected_extension);
  write_file(out_filename, corrected, strlen(corrected));

  free(corrected);
  free(text);

  free_search_tree(root);
  free(dict_data);
  return 0;
}
