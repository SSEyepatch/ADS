#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 1024

int is_op(char c){ return c=='+'||c=='-'||c=='*'||c=='/'||c=='^'||c=='$'; }
int prec(char c){ if(c=='^'||c=='$')return 4; if(c=='*'||c=='/')return 3; if(c=='+'||c=='-')return 2; return 0; }
int right_assoc(char c){ return (c=='^'||c=='$'); }

typedef struct { char a[MAX]; int top; } CStack;
void cs_init(CStack* s){ s->top=-1; }
int cs_empty(CStack* s){ return s->top==-1; }
char cs_top(CStack* s){ return s->a[s->top]; }
void cs_push(CStack* s,char c){ s->a[++s->top]=c; }
char cs_pop(CStack* s){ return s->a[s->top--]; }

typedef struct { double a[MAX]; int top; } DStack;
void ds_init(DStack* s){ s->top=-1; }
int ds_empty(DStack* s){ return s->top==-1; }
void ds_push(DStack* s,double v){ s->a[++s->top]=v; }
double ds_pop(DStack* s){ return s->a[s->top--]; }

void trim_newline(char* s){ size_t n=strlen(s); if(n&&s[n-1]=='\n') s[n-1]=0; }

void infix_to_postfix(const char* in, char* out){
    CStack st; cs_init(&st); out[0]=0;
    for(size_t i=0;i<strlen(in);){
        if(isspace((unsigned char)in[i])){ i++; continue; }
        if(isalnum((unsigned char)in[i])){
            char tok[MAX]; int k=0;
            while(i<strlen(in) && (isalnum((unsigned char)in[i])||in[i]=='.')) tok[k++]=in[i++];
            tok[k]=0;
            if(out[0]) strcat(out," ");
            strcat(out,tok);
        } else if(in[i]=='('){
            cs_push(&st,'('); i++;
        } else if(in[i]==')'){
            while(!cs_empty(&st) && cs_top(&st)!='('){
                char op[2]={cs_pop(&st),0};
                if(out[0]) strcat(out," ");
                strcat(out,op);
            }
            if(!cs_empty(&st) && cs_top(&st)=='(') cs_pop(&st);
            i++;
        } else if(is_op(in[i])){
            char o1=in[i++];
            while(!cs_empty(&st) && is_op(cs_top(&st)) &&
                 ( (right_assoc(o1)==0 && prec(o1)<=prec(cs_top(&st))) ||
                   (right_assoc(o1)==1 && prec(o1)< prec(cs_top(&st))) )){
                char op[2]={cs_pop(&st),0};
                if(out[0]) strcat(out," ");
                strcat(out,op);
            }
            cs_push(&st,o1);
        } else {
            i++;
        }
    }
    while(!cs_empty(&st)){
        char c=cs_pop(&st);
        if(c=='('||c==')') continue;
        char op[2]={c,0};
        if(out[0]) strcat(out," ");
        strcat(out,op);
    }
}

void reverse_str(char* s){
    size_t n=strlen(s);
    for(size_t i=0;i<n/2;i++){ char t=s[i]; s[i]=s[n-1-i]; s[n-1-i]=t; }
}

void swap_parens(char* s){
    for(size_t i=0;i<strlen(s);i++){
        if(s[i]=='(') s[i]=')';
        else if(s[i]==')') s[i]='(';
    }
}

void reverse_tokens(char* s){
    char *tokens[MAX]; int n=0;
    char buf[MAX]; strcpy(buf,s);
    char* t=strtok(buf," ");
    while(t){ tokens[n++]=t; t=strtok(NULL," "); }
    s[0]=0;
    for(int i=n-1;i>=0;i--){
        strcat(s,tokens[i]);
        if(i) strcat(s," ");
    }
}

void infix_to_prefix(const char* in, char* out){
    char tmp[MAX]; strcpy(tmp,in);
    for(size_t i=0;i<strlen(tmp);i++){
        if(tmp[i]=='(') tmp[i]=')';
        else if(tmp[i]==')') tmp[i]='(';
    }
    reverse_str(tmp);
    char post[MAX]; infix_to_postfix(tmp,post);
    strcpy(out,post);
    reverse_tokens(out);
}

double apply(double a,double b,char op){
    switch(op){
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return b==0?0:(a/b);
        case '^': case '$': return pow(a,b);
    }
    return 0;
}

int is_number_token(const char* t){
    if(!t||!*t) return 0;
    int i=0, dot=0, sign=0;
    if(t[i]=='+'||t[i]=='-'){ sign=1; i++; if(!t[i]) return 0; }
    for(; t[i]; i++){
        if(t[i]=='.'){ if(dot) return 0; dot=1; }
        else if(!isdigit((unsigned char)t[i])) return 0;
    }
    return 1;
}

double eval_postfix(const char* exp){
    DStack st; ds_init(&st);
    char buf[MAX]; strcpy(buf,exp);
    for(char* t=strtok(buf," "); t; t=strtok(NULL," ")){
        if(is_number_token(t)){ ds_push(&st, atof(t)); }
        else if(strlen(t)==1 && is_op(t[0])){
            double b=ds_pop(&st), a=ds_pop(&st);
            ds_push(&st, apply(a,b,t[0]));
        }
    }
    return ds_pop(&st);
}

double eval_prefix(const char* exp){
    DStack st; ds_init(&st);
    char* tokens[MAX]; int n=0;
    char buf[MAX]; strcpy(buf,exp);
    for(char* t=strtok(buf," "); t; t=strtok(NULL," ")) tokens[n++]=t;
    for(int i=n-1;i>=0;i--){
        char* t=tokens[i];
        if(is_number_token(t)) ds_push(&st, atof(t));
        else if(strlen(t)==1 && is_op(t[0])){
            double a=ds_pop(&st), b=ds_pop(&st);
            ds_push(&st, apply(a,b,t[0]));
        }
    }
    return ds_pop(&st);
}

double eval_infix(const char* infix){
    char post[MAX]; infix_to_postfix(infix,post);
    return eval_postfix(post);
}

int main(){
    for(;;){
        printf("\n1) Infix->Postfix\n2) Infix->Prefix\n3) Evaluate Infix\n4) Evaluate Postfix\n5) Evaluate Prefix\n6) Demo (ii)\n7) Demo (iv)\n0) Exit\nChoice: ");
        int ch; if(scanf("%d",&ch)!=1) return 0;
        getchar();
        if(ch==0) return 0;
        if(ch==1){
            char in[MAX], out[MAX];
            printf("Infix: "); fgets(in,MAX,stdin); trim_newline(in);
            infix_to_postfix(in,out);
            printf("Postfix: %s\n", out);
        } else if(ch==2){
            char in[MAX], out[MAX];
            printf("Infix: "); fgets(in,MAX,stdin); trim_newline(in);
            infix_to_prefix(in,out);
            printf("Prefix: %s\n", out);
        } else if(ch==3){
            char in[MAX];
            printf("Infix (numbers, use spaces for tokens if multi-digit): "); fgets(in,MAX,stdin); trim_newline(in);
            double v=eval_infix(in);
            printf("Value: %.10g\n", v);
        } else if(ch==4){
            char pf[MAX];
            printf("Postfix (space-separated): "); fgets(pf,MAX,stdin); trim_newline(pf);
            double v=eval_postfix(pf);
            printf("Value: %.10g\n", v);
        } else if(ch==5){
            char pr[MAX];
            printf("Prefix (space-separated): "); fgets(pr,MAX,stdin); trim_newline(pr);
            double v=eval_prefix(pr);
            printf("Value: %.10g\n", v);
        } else if(ch==6){
            char in[]="A+(B*C-(D/E^F)*G)*H";
            char pre[MAX];
            infix_to_prefix(in,pre);
            printf("Infix: %s\nPrefix: %s\n", in, pre);
        } else if(ch==7){
            char pr[]="+ - * + 1 2 / 4 2 1 $ 4 2";
            double v=eval_prefix(pr);
            printf("Prefix: %s\nValue: %.10g\n", pr, v);
        }
    }
    return 0;
}
