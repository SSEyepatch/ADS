#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node *head = NULL;

void clear_list() {
    Node *cur = head;
    while (cur) {
        Node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    head = NULL;
}

int count() {
    int c = 0;
    for (Node *p = head; p; p = p->next) c++;
    return c;
}

void display() {
    if (!head) { printf("List: [empty]\n"); return; }
    Node *p = head;
    printf("List: ");
    while (p) { printf("%d ", p->data); p = p->next; }
    printf("\n");
}

Node* make(int x) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->data = x; n->prev = n->next = NULL;
    return n;
}

void push_front(int x) {
    Node *n = make(x);
    n->next = head;
    if (head) head->prev = n;
    head = n;
}

void push_back(int x) {
    Node *n = make(x);
    if (!head) { head = n; return; }
    Node *p = head;
    while (p->next) p = p->next;
    p->next = n; n->prev = p;
}

void insert_at_pos(int x, int pos) {
    if (pos <= 1 || !head) { push_front(x); return; }
    int i = 1;
    Node *p = head;
    while (p && i < pos-1) { p = p->next; i++; }
    if (!p || !p->next) { push_back(x); return; }
    Node *n = make(x);
    n->next = p->next; n->prev = p;
    p->next->prev = n; p->next = n;
}

void pop_front() {
    if (!head) return;
    Node *t = head;
    head = head->next;
    if (head) head->prev = NULL;
    free(t);
}

void pop_back() {
    if (!head) return;
    if (!head->next) { free(head); head = NULL; return; }
    Node *p = head;
    while (p->next) p = p->next;
    p->prev->next = NULL;
    free(p);
}

void delete_at_pos(int pos) {
    if (!head) return;
    if (pos <= 1) { pop_front(); return; }
    int i = 1;
    Node *p = head;
    while (p && i < pos) { p = p->next; i++; }
    if (!p) { pop_back(); return; }
    if (p->next) p->next->prev = p->prev;
    if (p->prev) p->prev->next = p->next;
    if (p == head) head = p->next;
    free(p);
}

Node* search(int key) {
    for (Node *p = head; p; p = p->next) if (p->data == key) return p;
    return NULL;
}

void reverse() {
    Node *p = head, *tmp = NULL;
    while (p) {
        tmp = p->prev;
        p->prev = p->next;
        p->next = tmp;
        p = p->prev;
    }
    if (tmp) head = tmp->prev;
}

void create_list() {
    int n, x;
    clear_list();
    printf("How many nodes? ");
    if (scanf("%d", &n) != 1) return;
    for (int i = 0; i < n; i++) {
        printf("Data %d: ", i+1);
        if (scanf("%d", &x) != 1) return;
        push_back(x);
    }
}

int main() {
    int ch, x, pos;
    for (;;) {
        printf("\n1.Create 2.Display 3.Insert-Beg 4.Insert-End 5.Insert-Pos ");
        printf("6.Delete-Beg 7.Delete-End 8.Delete-Pos 9.Search 10.Count 11.Reverse 0.Exit\n");
        printf("Choice: ");
        if (scanf("%d", &ch) != 1) break;
        switch (ch) {
            case 1: create_list(); break;
            case 2: display(); break;
            case 3: printf("Value: "); scanf("%d", &x); push_front(x); break;
            case 4: printf("Value: "); scanf("%d", &x); push_back(x); break;
            case 5: printf("Value Pos: "); scanf("%d %d", &x, &pos); insert_at_pos(x, pos); break;
            case 6: pop_front(); break;
            case 7: pop_back(); break;
            case 8: printf("Pos: "); scanf("%d", &pos); delete_at_pos(pos); break;
            case 9: printf("Key: "); scanf("%d", &x); printf(search(x) ? "Found\n" : "Not Found\n"); break;
            case 10: printf("Count: %d\n", count()); break;
            case 11: reverse(); break;
            case 0: clear_list(); return 0;
            default: break;
        }
    }
    clear_list();
    return 0;
}
