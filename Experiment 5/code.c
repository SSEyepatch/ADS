#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *headA = NULL, *headB = NULL;
Node **active = &headA;
char active_name = 'A';

Node* make(int x){
    Node *n = (Node*)malloc(sizeof(Node));
    n->data = x; n->next = NULL; return n;
}

void clear_list(Node **h){
    Node *p=*h;
    while(p){ Node *q=p->next; free(p); p=q; }
    *h=NULL;
}

int count(Node *h){
    int c=0; for(Node *p=h;p;p=p->next) c++; return c;
}

void display(Node *h){
    if(!h){ printf("[%c] List: [empty]\n", active_name); return; }
    printf("[%c] List: ", active_name);
    for(Node *p=h;p;p=p->next) printf("%d ", p->data);
    printf("\n");
}

void push_front(Node **h, int x){
    Node *n = make(x);
    n->next = *h; *h = n;
}

void push_end(Node **h, int x){
    Node *n = make(x);
    if(!*h){ *h = n; return; }
    Node *p=*h; while(p->next) p=p->next; p->next = n;
}

void insert_at_pos(Node **h, int x, int pos){
    if(pos<=1 || !*h){ push_front(h,x); return; }
    int i=1; Node *p=*h;
    while(p->next && i<pos-1){ p=p->next; i++; }
    Node *n=make(x); n->next=p->next; p->next=n;
}

void pop_front(Node **h){
    if(!*h) return;
    Node *t=*h; *h=(*h)->next; free(t);
}

void pop_end(Node **h){
    if(!*h) return;
    if(!(*h)->next){ free(*h); *h=NULL; return; }
    Node *p=*h; while(p->next && p->next->next) p=p->next;
    free(p->next); p->next=NULL;
}

void delete_at_pos(Node **h, int pos){
    if(!*h) return;
    if(pos<=1){ pop_front(h); return; }
    int i=1; Node *p=*h;
    while(p->next && i<pos-1){ p=p->next; i++; }
    if(!p->next){ pop_end(h); return; }
    Node *t=p->next; p->next=t->next; free(t);
}

int search_first(Node *h, int key){
    int idx=1; for(Node *p=h;p;p=p->next,idx++) if(p->data==key) return idx; return -1;
}

void reverse(Node **h){
    Node *prev=NULL,*cur=*h,*nxt=NULL;
    while(cur){ nxt=cur->next; cur->next=prev; prev=cur; cur=nxt; }
    *h=prev;
}

void create_list(Node **h){
    int n,x; clear_list(h);
    printf("How many nodes? "); if(scanf("%d",&n)!=1) return;
    for(int i=0;i<n;i++){ printf("Data %d: ", i+1); if(scanf("%d",&x)!=1) return; push_end(h,x); }
}

void concat(Node **ha, Node **hb){
    if(!*hb) return;
    if(!*ha){ *ha = *hb; *hb = NULL; return; }
    Node *p=*ha; while(p->next) p=p->next; p->next=*hb; *hb=NULL;
}

void switch_active(){
    if(active == &headA){ active = &headB; active_name = 'B'; }
    else { active = &headA; active_name = 'A'; }
    printf("Switched to List %c\n", active_name);
}

void display_both(){
    char cur = active_name;
    char save = active_name;
    Node **save_ptr = active;
    active = &headA; active_name = 'A'; display(headA);
    active = &headB; active_name = 'B'; display(headB);
    active = save_ptr; active_name = save;
}

void menu(){
    printf("\n=== Singly Linked List — Active: %c ===\n", active_name);
    printf("1. Create (overwrite active)\n");
    printf("2. Display active\n");
    printf("3. Insert at beginning\n");
    printf("4. Insert at position (middle)\n");
    printf("5. Insert at end\n");
    printf("6. Delete first node\n");
    printf("7. Delete at position (middle)\n");
    printf("8. Delete last node\n");
    printf("9. Count nodes\n");
    printf("10. Reverse active\n");
    printf("11. Search in active\n");
    printf("12. Concatenate: B -> A\n");
    printf("13. Concatenate: A -> B\n");
    printf("14. Switch active list (A/B)\n");
    printf("15. Display A and B\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

int main(){
    int ch,x,pos;
    for(;;){
        menu();
        if(scanf("%d",&ch)!=1) break;
        switch(ch){
            case 1: create_list(active); break;
            case 2: display(*active); break;
            case 3: printf("Value: "); scanf("%d",&x); push_front(active,x); break;
            case 4: printf("Value Pos: "); scanf("%d %d",&x,&pos); insert_at_pos(active,x,pos); break;
            case 5: printf("Value: "); scanf("%d",&x); push_end(active,x); break;
            case 6: pop_front(active); break;
            case 7: printf("Pos: "); scanf("%d",&pos); delete_at_pos(active,pos); break;
            case 8: pop_end(active); break;
            case 9: printf("Count: %d\n", count(*active)); break;
            case 10: reverse(active); break;
            case 11: printf("Key: "); scanf("%d",&x); pos=search_first(*active,x);
                     if(pos==-1) printf("Not Found\n"); else printf("Found at position %d\n",pos); break;
            case 12: concat(&headA,&headB); printf("B concatenated into A\n"); break;
            case 13: concat(&headB,&headA); printf("A concatenated into B\n"); break;
            case 14: switch_active(); break;
            case 15: display_both(); break;
            case 0: clear_list(&headA); clear_list(&headB); return 0;
            default: break;
        }
    }
    clear_list(&headA); clear_list(&headB);
    return 0;
}
