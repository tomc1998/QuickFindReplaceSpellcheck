#ifndef IO_H
#define IO_H

/**
   Reads a file from disk.
   @param[in] path The path to read the dictionary file from
   @param[out] data_len The length of the returned data
   @return Pointer to the dictionary in memory
*/
char* read_file(const char* path, int* data_len);

/**
   Writes a file to disk.
   @param[in] path The path to write the data to
   @param[in] data_len The length of the data
   @param[in] data The data
*/
void write_file(const char* path, char* data, int data_len);

/**
    Gets the directory name that this executable is running in. 
    Currently only works on win32.
    @return The path of the directory
*/
char* get_curr_dir_name();

#endif
