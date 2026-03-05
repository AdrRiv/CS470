#ifdef LIBFS_H
#define LIBFS_H

#include <stdio.h>

//declaratations
FILE* fileCreate(const char* filename);
FILE* fileOpe(const char* filename, const char* mode);
size_t fileRead(FILE* file, void* buffer, size_t size, size_t count);
size_t fileWrite(FILE* file, const void* buffer, size_t size, size_t count);
void fileClose(FILE* file);
int fileDelete(const char* filename);

#endif
