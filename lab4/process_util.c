#include <stdio.h>
#include <process_util.h>

void calculate_metrics(Process *processes, int n){
	float total_waiting_time = 0;
	float total_turnaround_time = 0;
	for (int i = 0; i < n; i++){
		total_waiting_time += processes[i].waiting_time;
		total_turnaround_time += processes[i].turnaround_time;
	}
	printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
	printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void display_results(Process *processes, int n, const char* algorithm_name){
	printf("\n -Results for %s - \n", algorithm_name);
	printf("|Process ID|Arrival Time|Burst Time|Waiting Time|Turnaround Time|\n");
	printf("-----------------------------------------------------------------\n");
	for (int i = 0; i < n; i++){
		printf("|P%-9d|%-12d|%-11d|%-13d|%-16d|\n", processes[i].pid, processes.arrival_time, processes[i].burst_time. processes[i].waiting_time, processes[i].turnaround_time);
	}
	printf("-----------------------------------------------------------------\n");
