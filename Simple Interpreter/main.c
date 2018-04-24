#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define Typei 1000

float evaluate_postfix(char *postfix );
void infixTopostfix(char *infix, char *postfix,int x);

typedef struct stack
{
    int top;
    float X[Typei];
} stack;

typedef struct Node
{
    float data;
    char variable[Typei];
    struct Node *next;
} Node;

typedef struct LinkedList

{
    Node *head, *tail;
} LinkedList;

void initLinkedList(LinkedList *list)

{
    list->head=NULL;
    list->tail=NULL;
}

LinkedList list;

int isEmpty(Node * n)

{
    if (n==NULL)
        return 1;
    else
        return 0;
}

Node * newNode(float val,char * var)
{
    Node* n=(Node*)malloc(sizeof(Node));
    n->data = val;
    strcpy(n->variable, var);
    n->next = NULL;
    return n;
}
void addHead(LinkedList *list, float value,char var[])

{

    Node *n=newNode(value,var);
    n->next=list->head;
    list->head=n;
    if(list->tail==NULL)
        list->tail=n;

}
void addTail(LinkedList *list,float value,char * var)

{
    Node *n=newNode(value,var);
    if(list->head==NULL)
        list->head=list->tail=n;
    else
    {

        Node *OldTail=list->tail;
        list->tail=n;
        OldTail->next=n;
        n->next=NULL;
    }
}
float  search(LinkedList *list,char *c)
{
    Node * n = list->head;
    while(n!=NULL)
    {
        if(strcmp(n->variable,c)==0)
            return n->data;
        n = n->next;
    }
    return 0;
}

Node * SearchForNode(LinkedList *list,char *c)
{
    Node * n = list->head;
    while(n!=NULL)
    {
        if(strcmp(n->variable,c)==0/*n->variable=c*/)
            return n;
        n = n->next;
    }
    return NULL;
}
void intialize (stack *s)
{
    s->top = 0;
}

float pop(stack *s)
{
    return s->X[--s->top];
}

void push (stack *s, float value)
{
    s->X[s->top++]=value;
}

float top (stack *s)
{
    int x=s->top-1;
    return s->X[x];
}

int isempty(stack*s)
{
    return s->top==0? 1:0;

}

int isfull(stack *s)
{
    return s->top==20? 1:0;
}
void printlinkedlist(Node *n)
{
    while(n)
    {
        printf("%f\n",n->data);
        printf("%s\n",n->variable);
        n = n->next;
    }
}
float evaluate(char *infix)
{
    char *postfix = malloc(strlen(infix)*2*sizeof(char));
    int x=strlen(infix);
    infixTopostfix(infix,postfix,x);
    return evaluate_postfix(postfix);
}

int value(char x)
{
    if(x=='*'||x=='/')
        return 2;
    else if(x=='+'||x=='-')
        return 1;
    return 0;
}

void infixTopostfix(char *infix, char *postfix,int x)
{
    int i,j=0;
    stack s;
    intialize(&s);
    for(i=0,j=0; i<x ; i++)
    {
        if(infix[i]>='0')
        {
            postfix[j]='(';
            j++;
            for(; (!value(infix[i]))&&(infix[i]!=')')&&(infix[i]!='\0'); i++)
            {
                postfix[j]=infix[i];
                j++;
            }
            postfix[j]=')';
            j++;
            i--;
        }
        else if(infix[i]=='(')
        {
            push(&s,infix[i]);
        }
        else if(infix[i]==')')
        {
            while(top(&s)!='(')
            {
                postfix[j]=pop(&s);
                j++;
            }
            pop(&s);
        }
        else if(infix[i]<'0')
        {
            while((value(infix[i])<=value(top(&s)))&&(!isempty(&s)))
            {
                postfix[j]=pop(&s);
                j++;
            }
            push(&s,infix[i]);
        }
    }
    while(!isempty(&s))
    {
        postfix[j]=pop(&s);
        j++;
    }
    postfix[j]=0;
}

float evaluate_postfix(char postfix[])
{
    int i,j;
    float p,r;
    char number[10];
    stack s;
    intialize(&s);
    for(i=0; postfix[i]!='\0'; i++)
    {
        switch (postfix[i])
        {
        case '+':
            r=pop(&s);
            p=pop(&s);
            push(&s,r+p);
            break;
        case '/':
            r=pop(&s);
            p=pop(&s);
            push(&s,p/r);
            break;
        case '*':
            r=pop(&s);
            p=pop(&s);
            push(&s,r*p);
            break;
        case '-':
            r=pop(&s);
            p=pop(&s);
            push(&s,p-r);
            break;
        default:
            i++;
            for(j=0; (postfix[i]!=')')&&(postfix[i]!='\0'); i++)
            {
                number[j]=postfix[i];
                j++;
            }
            number[j]='\0';
            push(&s,atof(number));
        }
    }
    return pop(&s);
}
int main()
{
    LinkedList Tempo;
    initLinkedList(&list);
    initLinkedList(&Tempo);
    char x[Typei];
    char Value[Typei];
    char variable[Typei];
    char ch[Typei];
    char chk[Typei];
    int i,j,k,m,flag=0;
GT :
    while(1)
    {
        puts("Enter the expression (or (end) to exit):");
        gets(x);

        if(strcmp(x,"end")==0 || strcmp(x,"END")==0)
            exit(0);

        else if (2 == sscanf(x,"%s = %s",variable,Value))
        {

            for (i=0; x[i]!='='&&i<strlen(x); i++)
            {
                if(ispunct(x[i]))
                {
                    puts("Error : Left hand side should one variable!");
                    goto GT;
                }
            }
            char c[strlen(Value)+1],var[10];
            strcpy(c,Value);
            for(i=0,j=0,k=0; c[i]!='\0'; i++)
            {
                if(isalpha(c[i]))
                {
                    for(m=0; (!ispunct(c[i])&&(c[i]!='\0')); i++,m++)
                        var[m]=c[i];
                    var[m]='\0';
                    i--;
                    if (SearchForNode(&list,var)==NULL) {
                        puts("Error : Invalid Symbol!");
                    goto GT;
                    }

                    float val = search(&list,var);
                    sprintf(var,"%.2f",val);
                    for(m=0; m<strlen(var);)
                        if (var[0]!='-')
                        chk[k++] = var[m++];
                    else
                    {
                    m++;
                    chk[k++]='(';
                    chk [k++]='0';
                    chk [k++]='-';
                    for (; var[m]!='+' && var[m]!='/' && var[m]!='-' && var[m]!='*' && var[m]!='\0' && var[m]!=')' && var[m]!='(' ;)
                    chk[k++]=var[m++];
                    chk[k++]=')';
                    }
                }
                else if (c[i]=='-'&&!isdigit(c[i-1])) {
                    chk[k++]='(';
                    chk [k++]='0';
                    chk [k++]='-';
                    i++;
                    for (; c[i]!='+' && c[i]!='/' && c[i]!='-' && c[i]!='*' && c[i]!='\0' && c[i]!=')' && c[i]!='(' ;)
                   chk[k++]=c[i++];
                   chk[k++]=')';
                   i--;
                }
                else
                {
                    chk[k] = c[i];
                    k++;
                }
                if(c[i]=='(')
                    flag++;
                if(c[i]==')')
                    flag--;

            }
            if(flag)
            {
                puts("Error : Invalid Expression");
                goto GT;
            }
                for (i=0;i<strlen(c);i++) {
            if (c[i]=='+'||c[i]=='*'||c[i]=='/'||c[i]=='-') // Invalid Operations
                if (c[i+1]=='+'||c[i+1]=='*'||c[i+1]=='/'||(c[i+1]=='-'&&!isdigit(c[i+2]))||c[i+1]=='\0') {
                    puts("Invalid Expression!");
                    goto GT;
                }
            }
            for (i=0;i<strlen(c);i++){
                if (!isdigit(c[i])&&!isalnum(c[i])&&c[i]!='+'&&c[i]!='-'&&c[i]!='/'&&c[i]!='*'&&c[i]!='('&&c[i]!=')'&&c[i]!='.'&&c[i]!='~') {
                    puts("Invalid Expression!!");
                    goto GT;
                }
            }
            float e=evaluate(chk);
            printf("%f\n",e);
            if (SearchForNode(&list,variable))
                SearchForNode(&list,variable)->data = e;

            addTail(&list,e,variable);
            for (i=0;i<strlen(chk);i++)
            chk[i]='\0';
        }
        else {
            puts("Invalid!");
            goto GT;
        }
    }
    return 0;
}
