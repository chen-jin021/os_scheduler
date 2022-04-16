#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fifo.h"
#include "round_robin.h"

#define MAX 1025

int main() {
    int n;
    int sa;
    int q = MAX;
    printf("q is %d", MAX);
    // ask for processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // ask for scheduling algo
    printf("Enter the scheduling algorithm: ");
    scanf("%d", &sa);

    switch (sa) {
        case 1:
            fifo_scheduling(n);
            break;
        case 2:
            printf("Enter the time quantum: ");
            scanf("%d", &q);
            rr_scheduling(n, q);
            break;
        default:
            printf("INVALID ARGUMENT for scheduling");
    }
    return 0;
}