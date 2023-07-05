#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Policy {
    long long date;
    long long price;
} Policy;

typedef struct Child {
    long long id;
    struct Child *next;
} Child;

Child* new_child(long long id, Child* next) {
    Child* temp = (Child*)malloc(sizeof(Child));
    temp->id = id;
    temp->next = next;
    return temp;
}

typedef struct Node {
    Policy *heap;
    long long heapsize;
    Child *head;
} Node;

void init_node(long long M, Node *node) {
    node->heap = (Policy*)malloc((M + 5) * sizeof(Policy));
    node->head = NULL;
    node->heapsize = 0;
}

void insert(Policy *heap, long long price, long long date, long long *heapsize) {
    (*heapsize)++;
    heap[*heapsize].price = price;
    heap[*heapsize].date = date;
    long long now = *heapsize;
    while ((heap[now/2].price > price) && (now > 1)) {
        heap[now] = heap[now/2];
        now /= 2;
    }
    heap[now].price = price;
    heap[now].date = date;
}

void popmin(Policy *heap, long long *heapsize) {
    Policy temp = heap[1];
    heap[1] = heap[*heapsize];
    heap[*heapsize] = temp;
    (*heapsize)--;
    long long now = 1;
    while ((2 * now + 1 <= *heapsize) && ((heap[now].price > heap[2 * now].price) || (heap[now].price > heap[2 * now + 1].price))) {
        if ((heap[now].price > heap[2 * now].price) && (heap[now].price > heap[2 * now + 1].price)) {
            if (heap[2 * now].price < heap[2 * now + 1].price) {
                temp = heap[now];
                heap[now] = heap[2 * now];
                heap[2 * now] = temp;
                now = 2 * now;
            } else {
                temp = heap[now];
                heap[now] = heap[2 * now + 1];
                heap[2 * now + 1] = temp;
                now = 2 * now + 1;
            }
        } else if (heap[now].price > heap[2 * now].price) {
            temp = heap[now];
            heap[now] = heap[2 * now];
            heap[2 * now] = temp;
            now = 2 * now;
        } else if (heap[now].price > heap[2 * now + 1].price) {
            temp = heap[now];
            heap[now] = heap[2 * now + 1];
            heap[2 * now + 1] = temp;
            now = 2 * now + 1;
        }
    }
    if ((2 * now + 1 > *heapsize) && (2 * now <= *heapsize)) {
        if (heap[now].price > heap[2 * now].price) {
            temp = heap[now];
            heap[now] = heap[2 * now];
            heap[2 * now] = temp;
            now = 2 * now;
        }
    }
}

void popmin2(Policy *heap, long long *heapsize) {
    long long minElement, minElementdate, lastElement, lastElementdate, child, now;
minElement = heap[1].price;
minElementdate = heap[1].date;
lastElement = heap[*heapsize].price;
lastElementdate = heap[*heapsize].date;
(*heapsize)--;
for (now = 1; now * 2 <= *heapsize; now = child) {
    child = now * 2;
    if ((child != *heapsize) && (heap[child + 1].price < heap[child].price)) {
        child++;
    }
    if (lastElement > heap[child].price) {
        heap[now] = heap[child];
    } else {
        break;
    }
}
heap[now].price = lastElement;
heap[now].date = lastElementdate;
}

Node *arr;
long long *melon;
long long C;
long long max;

long long DFS(long long idx) {
if (arr[idx].head == NULL) {
if (arr[idx].heap[1].price <= C) {
if (melon[idx] > max) {
max = melon[idx];
}
}
return arr[idx].heap[1].price;
}
Child *temp = arr[idx].head;
long long sum = arr[idx].heap[1].price;
while (temp != NULL) {
sum += DFS(temp->id);
temp = temp->next;
}
if (sum <= C) {
if (melon[idx] > max) {
max = melon[idx];
}
}
return sum;
}

long long Countnode(long long idx) {
if (arr[idx].head == NULL) {
melon[idx] = 1;
return 1;
}
Child *temp = arr[idx].head;
long long sum = 1;
while (temp != NULL) {
sum += Countnode(temp->id);
temp = temp->next;
}
melon[idx] = sum;
return sum;
}

void Clean(long long N, long long date) {
for (long long i = 1; i <= N; i++) {
while (arr[i].heap[1].date < date) {
popmin2(arr[i].heap, &arr[i].heapsize);
}
}
}

int main() {
long long N, M, x, c, d;
scanf("%lld %lld %lld", &N, &M, &C);
arr = (Node*)malloc(sizeof(Node) * (N + 5));
melon = (long long*)malloc(sizeof(long long) * (N + 5));
for (long long i = 1; i <= N; i++) {
init_node(M, &arr[i]);
}
for (long long i = 2; i <= N; i++) {
scanf("%lld", &x);
arr[x].head = new_child(i, arr[x].head);
}
Countnode(1);
for (long long j = 1; j <= M; j++) {
for (long long i = 1; i <= N; i++) {
scanf("%lld %lld", &c, &d);
insert(arr[i].heap, c, d + j, &arr[i].heapsize);
}
Clean(N, j);
max = 0;
DFS(1);
printf("%lld\n", max);
}
return 0;
}
