#ifndef _DEFINITIONS_H
#define _DEFINITIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READY 1
#define RUNNING 2
#define BLOCKED 3
#define TERMINATE 4
#define DONE 5

struct process {
    int state;  // matching the above state for processess
    int time[6];
    int counter;  // counts cur ele's elapsed time in each state (R or B) reset when it goes to the next state
    int current;  // which element of time is it running
} typedef p;

#endif