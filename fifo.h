#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "queue.h"

void report_row(int n) {
    printf("Cycle\t");
    int i;
    for (i = 0; i < n; i++) {
        printf("P%d State\t\t", i + 1);
    }
    printf("Comment\n");
}

// if instruction is fifo
void fifo_scheduling(p* processes, int n) {
    report_row(n);
    int isDone = 0;
    int cycle = 0;
    int i;
    int firstCycle = 1;

    while (isDone != n) {
        int pos = queue[start];
        processes[pos - 1].state = RUNNING;
        // next cycle
        cycle++;
        printf("%d\t", cycle);
        for (i = 0; i < n; i++) {
            // total_time of the current time element
            int process_current = processes[i].current;
            int current_counter = processes[i].counter;
            int total_time = processes[i].time[process_current];
            int process_state = processes[i].state;
            // running and the state is not terminating
            if (process_state == RUNNING && process_current != 4) {
                processes[i].counter++;
                printf("Run (%d of %d)\t\t", current_counter + 1, total_time);
                // check if the current state has reached (turn to next state)
                if (current_counter == total_time - 1) {
                    // reset counter, add current + 1
                    // change the state from running to blocking
                    processes[i].counter = 0;
                    processes[i].current++;
                    processes[i].state = BLOCKED;
                    pop();
                }
            } else if (process_state == READY) {
                printf("Ready\t\t\t");
            } else if (process_state == BLOCKED) {
                processes[i].counter++;
                printf("Blocked (%d of %d)\t", current_counter, total_time);
                if (current_counter == total_time - 1) {  // change state
                    processes[i].counter = 0;             // reset counter
                    processes[i].state = READY;
                    processes[i].current++;
                    push(i + 1);
                }
            } else if (process_state == RUNNING && process_current == 4) {
                // this process turn to run and ready to terminate
                printf("Terminate\t\t");
                isDone++;  // add one process to done list
                processes[i].state = DONE;
                pop();
            } else {  // done
                printf("\t\t\t");
            }
        }
        // comment
        if (firstCycle) {
            firstCycle = 0;
            printf("Processes Created; P1 wins tiebreak");
        } else if (pos == 0) {
            printf("CPU IDLE");
        }
        printf("\n");
    }
}