
#ifndef _DEFINITIONS_MAIN
#define _DEFINITIONS_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fifo.h"
#include "round_robin.h"
#endif

#define MAX 1025
#define READY 1

void initializer() {
    int n;
    int sa;
    int q = MAX;
    // ask for processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // ask for scheduling algo
    printf("Enter the scheduling algorithm: ");
    scanf("%d", &sa);

    // define an array of processes
    int i, j;
    p processes[n];
    for (i = 0; i < n; i++) {
        // initialize each process
        processes[i].counter = 0;
        processes[i].state = READY;
        for (j = 0; j < 4; j++) {
            if (j % 2 == 0) {
                processes[i].time[j] = 3;
            } else {
                processes[i].time[j] = 2;
            }
        }
        processes[i].time[5] = 1;  // termination 1 milisec
    }

    switch (sa) {
        case 1:
            fifo_scheduling(processes, n);
            break;
        case 2:
            printf("Enter the time quantum: ");
            scanf("%d", &q);
            rr_scheduling(processes, n, q);
            break;
        default:
            printf("INVALID ARGUMENT for scheduling");
    }
}
int main() {
    initializer();

    return 0;
}