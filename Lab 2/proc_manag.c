#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define NUM_CHILDREN 15

int main() 
{
	pid_t childPids[NUM_CHILDREN];
	int status;
	int normalExit0 = 0, normalExitNon0 = 0, signaled = 0;

	printf("Parent Process PID: %d\n\n", getpid());

	//Creating parent process
	for (int i = 0; i < NUM_CHILDREN; i++){
		childPids[i] = fork();

		if (childPids[i] < 0){
			perror("Failed to use Fork");
			exit(1);
		}
		
		//Creating child process
		else if (childPids[i] == 0){
			printf("[Child %d] PID: %d - ", i + 1, getpid());

			//Echoing "Hello Adrian
			if (i == 0){
				printf("Executing - echo \"Hello Adrian\"\n");
				char *args[] = {"echo", "Hello Adrian", NULL};
				execvp(args[0], args);
			}

			//Intentional Invalid Commands
			else if (i <= 2){
				printf("Executing invalid command - nonexist\n");
				char *args[] = {"nonexist", NULL};
				execvp(args[0], args);

				//returns -1 if fails
				exit(127);
			}

			//Abnormal termination
			else if (i < 4) {
				printf("Abnormal termination requiring abort()\n");
				abort();
			}

			//If execvp is successful exit (0) is unused
			exit(0);
		}
	}

	//Synchronization of processes
	printf("\nWaiting for children\n");
	for (int i = 0; i < NUM_CHILDREN; i++){
		waitpid(childPids[i], &status, 0);
		printf("[Parent] Child %d (PID: %d) ", i + 1, childPids[i]);

		if (WIFEXITED(status)){
			int exitCode = WEXITSTATUS(status);
			printf("exited normally with status %d\n", exitCode);
			if (exitCode == 0) normalExit0++;
			else normalExitNon0++;
		}else if (WIFSIGNALED(status)){
			printf("Terminated by the signal %d\n", WTERMSIG(status));
			signaled++;
		}
	}

	//Summary
	printf("\nSummary\n");
	printf("Normal Exit (0): %d\n", normalExit0);
	printf("Normal Exit (non-zero): %d\n", normalExitNon0);
	printf("Terminated via signal: %d\n", signaled);
	return 0;
}
