#ifndef _DEFINITIONS_Q
#define _DEFINITIONS_Q
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// automatically initialized to 0s
int queue[1000];
int start, end = 0;

int switcher[1000];
int st[1000];
// insert at the back
void push(int index) {
    queue[end] = index;
    end++;
}
void pop() {
    start++;
}
#endif