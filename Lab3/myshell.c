#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

void execute_command(char **args, char *input_file, char *output_file, int append){
	pid_t pid = fork();

	if (pid == 0){
		if(input_file){
			int fd = open(input_file, O_RDONLY);
			if (fd < 0) {
				perror("input error");
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (output_file){
			int flags = O_WRONLY | O_CREAT | (append ? append : O_TRUNC);
			int fd = open(output_file, flags, 0644);
			if (fd < 0) {
				perror("Output error");
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		execvp(args[0], args);
		printf(stderr, "Command not found: %s\n", args[0]);
		exit(1);
	}else{
		wait(NULL);
	}
}

int main(){
	char line[MAX_LINE];
	char *args[MAX_ARGS];

	while(1){
		printf("myshell > ");
		//Handling EOF
		if (!fgets(line, MAX_LINE, stdin)) break;

		//tokenization
		int i = 0;
		char *input_file = NULL, *output_file = NULL;
		int append = 0;

		char *token = strtok(line, " \n\t");
		while (token != NULL){
			if (strcmp(token, "<") == 0){
				input_file = strtok(NULL, " \n\t");
			}else if (strcmp(token, ">") == 0){
				output_file = strtok(NULL, " \n\t");
				append = 0;
			}else if (strcmp(token, ">>") == 0){
				output_file = strtok(NULL, " \n\t");
				append = 1;
			}else{
				args[i++] = token;
			}
			token = strtok(NULL, " \n\t");
		}
		args[i] = NULL;

		if (args[0] == NULL) continue;

		//built ins
		if (strcmp(args[0], "exit") == 0) break;
		if (strcmp(args[0], "cd") == 0){
			if (chdir(args[1] ? args[1] : getenv("HOME")) !=0) perror("cd failed");
			continue;
		}

		execute_command(args, input_file, output_file, append);
	}
	return 0;
}
