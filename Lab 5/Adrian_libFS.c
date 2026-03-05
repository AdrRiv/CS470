#include "Adrian_libFS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creating new file
//returns file pointer on success

FILE* fileCreate(const char* filename){
	FILE* file = fopen(filename, "w+");
	if (!file){
		perror("Error creating file");
	}
	return file;
}

//Opening existing file

FILE* fileOpen(const char* filename, const char* mode){
	FILE* file = fopen(filename, mode);
	if (!file){
		perror("Error opening file");
	}
	return file;
}

//Reading data from file

size_t fileRead(FILE* file, void* buffer, size_t size, size_t count){
	return fread(buffer, size, count, file);
}

//Writing to file

size_t fileWrite(FILE* file, const void* buffer, size_t size, size_t count){
	return fwrite(buffer, size, count, file);
}

//Closing the file

void fileClose(FILE* file){
	if (file){
		if (fclose(file) != 0){
			perror("Error closing file");
		}
	}
}

//Deleting file

int fileDelete(const char* filename){
	int status = remove(filename);
	if (status != 0){
		perror("Error deleting file");
	}
	return status;
}
