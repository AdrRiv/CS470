#include "Adrian_libFS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512
#define FILENAME "Adrian_introduction.txt"

void handle_file_operations();
void press_enter_to_continue();

int main(){
	printf("---LibFS Test---\n");
	handle_file_operations();
	printf("---Complete---\n");
	return 0;
}


void handle_file_operations(){
	FILE* file = NULL;
	char buffer[BUFFER_SIZE];
	int choice;

	const char* introduction =
		"Hello, my name is Adrian and this is my introduction.\n"
		"I am working on implementing a basic file system library in C]n"
		"\n"
		"This exercise will help me understand system-level file operations.\n"
		"Robust error handling is a key component to this lab.";

	while (1){
		printf("\nMenu:\n");
		printf("1. Create file (%s) \n", FILENAME);
		printf("2. Open file\n");
		printf("3. Write introduction to file\n");
		printf("4. Read file content\n");
		printf("5. Close file\n");
		printf("6. Delete file\n");
		printf("7. Exit\n");
		printf("Enter numeric choice: ");

		if (scanf("%d", &choice) != 1){
			printf("Invalid input. Please enter a number between 1 and 7.\n");
			//Clearing input

			while (getchar() != '\n');
			press_enter_to_continue();
			continue;
		}

		switch (choice){
			case 1:
				if (file) fileClose(file);
				file = fileCreate(FILENAME);
				if (file) printf("File created successfully.\n");
				fileClose(file);
				file = NULL;
				break;

			case 2:
				if (file) fileClose(file);
				file = fileOpen(FILENAME, "r+");
				if (file) printf("File opened successfully.\n");
				break;

			case 3:
				if (!file){
					printf("Please open a file first.\n");
					break;
				}

				//Write operation

				size_t written = fileWrite(file, introduction, 1, strlen(introduction));
				if (written == strlen(introduction)){
					printf("Data written successfully. Wrote %zu bytes.\n", written);
				}else{
					printf("Error writing data.\n");
				}
				fileClose(file);
				file = NULL;
				break;

			case 4:
				//reopen in read mode

				if (file) fileClose(file);
				file = fileOpen(FILENAME, "r");
				if (!file) break;

				//Read operation

				size_t read_count = fileRead(file, buffer, 1, BUFFER_SIZE - 1);
				if (read_count > 0){
					buffer[read_count] = '\0';
					printf("---File contents---\n%s\n---End Contents---\n", buffer);
				}else{
					printf("No data read or error occured.\n");
				}
				fileClose(file);
				file = NULL;
				break;

			case 5:
				if (file){
					fileClose(file);
					file = NULL;
					printf("File closed.\n");
				}else{
					printf("No file is currently open.\n");
				}
				break;

			case 6:
				if (file) fileClose(file);
				if (fileDelete(FILENAME) == 0){
					printf("File deleted successfully.\n");
				}
				file = NULL;
				break;

			case 7:
				if (file) fileClose(file);
				return;

			default:
				printf("Invalid choice. Please try again.\n");
		}
		press_enter_to_continue();
	}
}

void press_enter_to_continue(){
	printf("\nPress Enter to continue...");
	while (getchar() != '\n');
	getchar();
}
