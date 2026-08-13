#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAP 1000000

typedef struct {
    int *data;
    int front;
    int size;
    int capacity;
} Deque;

void initDeque(Deque *d) {
    d->capacity = INITIAL_CAP;
    d->data = malloc(INITIAL_CAP * sizeof(int));
    d->front = 0;
    d->size = 0;
}

int sizeDeque(Deque *d) {
    return d->size;
}

void pushFrontDeque(Deque *d, int x) {
    d->front = (d->front - 1 + d->capacity) % d->capacity;
    d->data[d->front] = x;
    d->size++;
}

void pushBackDeque(Deque *d, int x) {
    int back = (d->front + d->size) % d->capacity;
    d->data[back] = x;
    d->size++;
}

int popFrontDeque(Deque *d) {
    int x = d->data[d->front];
    d->front = (d->front + 1) % d->capacity;
    d->size--;
    return x;
}

int popBackDeque(Deque *d) {
    d->size--;
    int back = (d->front + d->size) % d->capacity;
    return d->data[back];
}

int getDeque(Deque *d, int i) {
    return d->data[(d->front + i) % d->capacity];
}

Deque left, right;

void rebalance() {
    int leftSize = sizeDeque(&left);
    int rightSize = sizeDeque(&right);
    
    if (leftSize > rightSize + 1) {
        int x = popBackDeque(&left);
        pushFrontDeque(&right, x);
        leftSize--;
        rightSize++;
    }
    
    if (rightSize > leftSize) {
        int x = popFrontDeque(&right);
        pushBackDeque(&left, x);
        rightSize--;
        leftSize++;
    }
}

void pushFront(int x) {
    pushFrontDeque(&left, x);
    rebalance();
}

void pushBack(int x) {
    pushBackDeque(&right, x);
    rebalance();
}

void pushMid(int x) {
    if (sizeDeque(&left) > sizeDeque(&right)) {
        pushFrontDeque(&right, x);
    } else {
        pushBackDeque(&left, x);
    }
    rebalance();
}

int get(int i) {
    if (i < sizeDeque(&left)) {
        return getDeque(&left, i);
    } else {
        return getDeque(&right, i - sizeDeque(&left));
    }
}

int main() {
    initDeque(&left);
    initDeque(&right);
    
    int n;
    scanf("%d", &n);
    
    while (n--) {
        char cmd[12];
        int x;
        scanf("%11s", cmd);
        scanf("%d", &x);
        
        if (strcmp(cmd, "get") == 0) {
            printf("%d\n", get(x));
        } else if (strcmp(cmd, "push_front") == 0) {
            pushFront(x);
        } else if (strcmp(cmd, "push_back") == 0) {
            pushBack(x);
        } else if (strcmp(cmd, "push_middle") == 0) {
            pushMid(x);
        }
    }
    
    free(left.data);
    free(right.data);
    
    return 0;
}
