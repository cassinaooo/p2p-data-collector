#ifndef __FILE_READER__
#define __FILE_READER__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <libgen.h>


long slurp(char const* path, char **buf, int add_nul);
void split(char const* filename, char const* slice_bytes, char * splitted_file_regex);
void compress(char const* foldername, char * compressed_filename);
void compressandsplit(char const * folder_path, char * parts_folder);
void listfilesbyregex(char const * regex, char **files);

#endif