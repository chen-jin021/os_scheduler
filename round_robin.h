#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "queue.h"

// first row report
void row_report(int n) {
    printf("Cycle\t");
    int i;
    for (i = 0; i < n; i++) {
        printf("P%d State\t\t", i + 1);
    }
    printf("Comment\n");
}
// if instruction is rr
void rr_scheduling(p* processes, int n, int q) {
    row_report(n);
    int cycle = 0;
    int isDone = 0;
    int beforeP = -1;
    while (isDone != n) {
        int pos = -1;
        if (start != end) {
            pos = queue[start] - 1;
            processes[pos].state = RUNNING;
            pop();
            switcher[pos] = 0;
        }

        int newCycle = 0;
        int t, i;
        for (t = 1; t <= q; t++) {
            cycle += 1;
            printf("%d\t", cycle);
            for (i = 0; i < n; i++) {
                if (processes[i].state == RUNNING) {
                    processes[i].counter++;
                    if (processes[i].current == 0 || processes[i].current == 2) {  // R
                        printf("Run (%d of %d)\t\t", processes[i].counter, processes[i].time[processes[i].current]);
                    } else if (processes[i].current == 1 || processes[i].current == 3) {  // B
                        printf("Blocked  (%d of %d)\t", processes[i].counter, processes[i].time[processes[i].current]);
                    } else if (st[i] == 0) {  // neither running nor blocking (terminating)
                        printf("Terminate\t\t");
                        isDone++;
                        st[i] = 1;
                        processes[i].state = DONE;
                    } else if (st[i] == 1) {  // terminated
                        printf("\t\t\t");
                    }
                    // once the R/B process has been completed, move to the next R/B [not terminating]
                    if (processes[i].current != 4 && processes[i].counter == processes[i].time[processes[i].current]) {
                        processes[i].counter = 0;
                        processes[i].current++;
                    }
                    if (processes[i].current == 1 || processes[i].current == 3 || processes[i].current == 4) {
                        newCycle = 1;
                    }
                } else if (processes[i].state == READY) {
                    printf("Ready\t\t\t");
                } else if (processes[i].state == BLOCKED) {
                    processes[i].counter++;
                    printf("Blocked  (%d of %d)\t", processes[i].counter, processes[i].time[processes[i].current]);
                    if (processes[i].counter == processes[i].time[processes[i].current]) {
                        // reset and move to next
                        processes[i].counter = 0;
                        processes[i].current++;
                        processes[i].state = READY;
                    }
                } else if (processes[i].state == DONE)
                    printf("\t\t\t");
            }
            // processes[beforeP].time[processes[beforeP].current] != 1 for not terminating
            if (pos != -1 && beforeP != -1 && t == 1 && processes[beforeP].state == READY && processes[beforeP].time[processes[beforeP].current] != 1) {
                printf("P%d preempted\t", beforeP + 1);
            }
            if (pos == -1) {
                printf("CPU idle\t");
                beforeP = -1;
            } else {
                beforeP = pos;
            }
            if (cycle == 1) {
                printf("Both created; P1 wins tiebreak\t");
            }
            printf("\n");

            if (newCycle || pos == -1)
                break;
        }
        if (pos != -1 && processes[pos].state != DONE) {
            // new cycle if current is RUNNING, turn into READY
            if (processes[pos].current == 0 || processes[pos].current == 2) {
                processes[pos].state = READY;
            } else if (processes[pos].current == 1 || processes[pos].current == 3)
                processes[pos].state = BLOCKED;  // if BLOCKED, then BLOCKED
        }
        for (i = 0; i < n; i++) {
            if (processes[i].state == READY && switcher[i] == 0) {
                push(i + 1);
                switcher[i] = 1;
            }
        }
    }
}