#ifndef PROCESS_UTIL_H
#define PROCESS_UTIL_H

typedef struct{
	int pid;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turnaround_time;
	int remaining_time;
} Process;

void calculate_metrics(Process *processes, int n);
void display_results(Process *processes, int n, const char* algorithm_name);

#endif
