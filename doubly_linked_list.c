#include <stdio.h>
#include <string.h>

#define MAX_N 250000
#define MAX_PPL (2 * MAX_N)
#define MAX_NAME_LEN 21

char name[MAX_PPL] [MAX_NAME_LEN];
int partner[MAX_PPL];
int prev[MAX_PPL];
int next[MAX_PPL];
int head = -1;
int tail = -1;
int mic = -1;
int P;

void insertTail(int x) {
    prev[x] = tail;
    next[x] = -1;
    if (tail != -1) {
        next[tail] = x;
    }
    tail = x;
    if (head == -1) {
        head = x;
    }
}

void removeNode(int x) {
    int L = prev[x];
    int R = next[x];
    
    if (L != -1) {
        next[L] = R;
    } else {
        head = R;
    }
    
    if (R != -1) {
        prev[R] = L;
    } else {
        tail = L;
    }
    prev[x] = next[x] = -1;
}

void insertAfterPos(int pos, int x) {
    int R = next[pos];
    next[pos] = x;
    prev[x] = pos;
    next[x] = R;
    if (R != -1) {
        prev[R] = x;
    } else {
        tail = x;
    }
}

int main() {
    int N, Q;
    scanf("%d", &N);
    scanf("%d", &Q);
    P = 2 * N;
    
    for (int i = 0; i < N; ++i) {
        int a = 2 * i;
        int b = 2 * i + 1;
        scanf("%20s", name[a]);
        scanf("%20s", name[b]);
        partner[a] = b;
        partner[b] = a;
        insertTail(a);
        insertTail(b);
    }
    
    mic = head;
    
    for (int i = 0; i < Q; ++i) {
        char c;
        scanf(" %c", &c);
        
        if (c == 'P') {
            printf("%s\n", name[partner[mic]]);
        } else if (c == 'F') {
            mic = prev[mic];
        } else if (c == 'B') {
            mic = next[mic];
        } else if (c == 'R') {
            int temp = mic;
            if (temp == tail) {
                mic = head;
            } else {
                mic = next[temp];
                removeNode(temp);
                insertTail(temp);
            }
        } else if (c == 'C') {
            int temp = mic;
            if (temp == tail) {
                mic = head;
            } else {
                mic = next[temp];
            }
            int pIdx = partner[temp];
            if (next[pIdx] != temp) {
                removeNode(temp);
                insertAfterPos(pIdx, temp);
            }
        }
    }
    printf("\n");
    for (int x = head; x != -1; x = next[x]) {
        printf("%s\n", name[x]);
    }
    
    return 0;
}
