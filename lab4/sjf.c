#include <stdio.h>
#include <stdlib.h>
#include <process_util.h>

//comparing sorting processes by arrical and then burst time
int compareProcesses(const void* a, const void* b){
	Process* p1 = (Process*)a;
	Process* p2 = (Process*)b;
	if (p1->arrival_time != p2->arrival_time){
		return p1->arrival_time - p2->arrival_time;
	}
	return p1->burst_time - p2->burst_time;
}

void sjf_scheduling(Process *processes, int n){
	//sorting by arrival time
	qsort(processes, n, sizeof(Process), compareProcesses);

	int current_time = 0;
	int completed = 0;
	int *execution_order = (int*)malloc(n * sizeof(int));
	int order_index = 0;

	while (completed < n){
		int best_job_index = -1;
		int min_burst = 999999;

		for (int i = 0; i < n; i++){
			if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0){
				if (processes[i].burst_time < min_burst){
					min_burst = processes[i].burst_time;
					best_job_index = i;
				}
			}
		}

		if (best_job_index == -1){
			current_time++;
		}else{
			//executing processes
			processes[best_job_index].wait_time = current_time - processes[best_job_index].arrival_time;
			current_time += processes[best_job_index].burst_time;
			processes[best_jobindex].turnaround_time = current_time - processes[best_job_index].arrival_time;
			processes[best_job_index].remaining_time = 0;
			execution_order[order_index++] = processes[best_job_index].pid;
			completed++;
		}
	}

	printf("\nExecution Order: ");
	for (int i = 0; i < n; i++){
		printf("P%d ", execution_order[i]);
				}
	printf("\n");
	free(execution_order);
	calculate_metrics(processes, n);
}

int main(){
	//sample data
	Process processes[] = {
		{1, 0, 6, 0, 0, 6},
		{2, 1, 8, 0, 0, 8},
		{3, 2, 7, 0, 0, 7},
		{4, 3, 3, 0, 0, 3}
	};
	int n = sizeof(processes) / sizeof(Process);
	sjf_scheduling(processes, n);
	display_results(processes, n, "SJF");
	return 0;
}
