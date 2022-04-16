#ifndef _DEFINITIONS_Q
#define _DEFINITIONS_Q
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #define MAX 1000

int queue[1000];

int start, end = 0;
// insert at the back
void push(int index) {
    queue[end] = index;
    end++;
}
void pop() {
    start++;
}
#endif