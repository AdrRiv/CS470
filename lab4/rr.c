#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <process_util.h>

void rr_scheduling(Process *processes, int n, int quantum){
	//Creating an array for simplicity
	
	int current_time = 0;
	int completed = 0;
	int *execution_order = (int*)malloc(100 * sizeof(int));
	int order_index = 0;
	int ready_queue[100];
	int head = 0, tail = 0;

	//sorting based on arrival time first for initial queue
	
	qsort(processes, n, sizeof(Process), compareProcesses);

	//Adding first process into queue
	
	ready_queue[tail++] = 0;

	while (completed < n){
		//queue is empty
		if (head == tail){
			current_time++;
			for (int i = 0; i < n; i++){
				if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0){
					break;
				}
			}
			continue;
		}

		int current_process_index = ready_queue[head++];
		Process *p =&processes[current_process_index];
		int execution_slice = (p->remaining_time < quantum) ? p->remaining_time : quantum;
		current_time += execution_slice;
		p->remaining_time -= execution_slice;
		execution_order[order_index++] = p->pid;

		//Adding new process

		for (int i = 0; i < n; i++){
			if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && i != current_process_index) {
			}
		}
		if (p->remaining_time == 0){
			completed++;
			p->turnaround_time = current_time - p->arrival_time;
			p->waiting_time = p->turnaround_time - p->burst_time;
		}else{
		}
	}

	printf("\nExecution Order: ");
	for (int i = 0; i < n; i++){
		printf("P%d ", execution_order[i];
				}
				printf("\n");
				free(execution_order);
				calculate_metircs(processes, n);
				}

				int main(){
				int quantum = 2;
				//sample data
				
				Process processes[] = {
				{1, 0, 10, 0, 0, 10},
				{2, 0, 5, 0, 0, 5},
				{3, 0, 8, 0, 0, 8}
				};

				int n = sizeof(processes) / sizeof(Process);
				rr_scheduling(processes, n, quantum);
				display_results(processes, n, "Round Robin");
				return 0;
				}
