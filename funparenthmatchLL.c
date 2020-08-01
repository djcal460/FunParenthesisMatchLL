#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct Node
{
    char data;
    struct Node *next;
} *top = NULL;

//GLOBAL LIST
//don't need a ptr because we are changing a global list ptr
void push(int x)
{

    //create new node
    struct Node *t;
    t = (struct Node *)malloc(sizeof(struct Node));

    if (t == NULL)
        printf("Stack is Full\n"); //this just means no space was allocated b/c resources
    else
    {
        t->data = x;   //save data to new node
        t->next = top; //old top is now t->next (insert on left)
        top = t;       //top is now t
    }
}
//need a ptr because we are changing the stack
int pop()
{
    int x;
    //create new node ptr to use as top
    struct Node *t;

    if (top == NULL)
        printf("Stack is Empty\n"); //this just means no space was allocated b/c resources
    else
    {
        t = top;         //temp ptr to pt to top of stack
        top = top->next; // move top to next node on stack
        x = t->data;     //temp ptr save data
        free(t);         //free node pted to by t
    }
    return x;
} //don't need to pass anything to display globals list
void display()
{

    //need a reference to it, so we aren't actually moving global ptr
    struct Node *p;
    p = top;

    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
int stackTop()
{
    if (top == NULL)
    {
        printf("List is Empty\n");
        return -1;
    }
    else
        return top->data;
}
int isEmpty()
{
    if (top == NULL)
    {
        printf("The stack is empty.\n");
        return 1;
    }
    else
    {
        printf("The stack is not empty.\n");
        return 0;
    }
}
void isFull()
{
    struct Node *p;
    p = (struct Node *)malloc(sizeof(struct Node));
    if (p == NULL)
        printf("The stack is full.\n");
    else
        printf("The stack is not full.\n");
}
int peek(int pos)
{

    int x = -1;
    struct Node *t = top; //temp ptr

    //pos 1 is top of stack, so should fail loop statement
    for (int i = 1; i < pos; i++)
    {
        t = t->next;
    }
    //if t is not assigned then not a position
    if (t == NULL)
    {
        printf("Invalid Position\n");
    }
    else
    {
        x = t->data;
    }
    return x;
}
int isBalanced(char *exp)
{

    //iterate until null terminator
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
        { //opening push it
            push(exp[i]);
            printf("pushed %c\n", exp[i]);
        }
        else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}')
        {
            if (top == NULL)
                return 0;
            char x = pop(); //pop it
            printf("popped %c\n", x);
            //check if it closes the same kind of char on current stack
            // if it doesn't then no match return 0
            if (!((x == '{' && exp[i] == '}') || (x == '(' && exp[i] == ')') || (x == '[' && exp[i] == ']')))
            {
                return 0;
            }
        }
    }
    return isEmpty() ? 1 : 0; //if true return 1, else 0
}

int reprompt()
{
    int fixin, input, ret = 0;
    //check valid size
    while (ret != 1 || input > 11 || input < 1)
    {
        printf("Enter a valid size: ");
        while ((fixin = getchar()) != EOF && fixin != '\n')
            ; // fix stdin
        fflush(stdin);
        ret = scanf("%d", &input);
    }
    return input;
}

void resolve(char *infix)
{
    //Here we use our stack structure to test for balance in parenth
    printf("Checking the parenthesis on this equation: %s", infix);
    printf("\n");
    //check if balanced statment
    if (isBalanced(infix))
        printf("This is a balanced infix problem.\n");
    else
        printf("It is not a balanced infix problem.\n");
    printf("Press Any Key to Continue: ");
    getchar();
    getchar();
    fflush(stdin);
    printf("\n");
}

int main()
{
    printf("Welcome to the parenthesis checking program.\n");
    printf("Use a linked list stack to check if parenthesis are balanced.\n");

    int ret, input;
    //prompt user to choose an equation
    do
    {
        printf("\nBelow are some simple infix math equations.\n");
        printf("Parenthesis can be a pain to look at.\n");
        printf("Let the program check to see if the parenthesis are balanced.\n");
        printf("1.  (8 + (3 * 9) - 6)\n");
        printf("2.  (5 * ((4) / (9)) + 1)\n");
        printf("3.  ((6 + 6) + (7 * (2))\n");
        printf("4.  (8 / (2)) / ((2) + 9) \n");
        printf("5.  ((2) * (2) * 2) / (2 + 2 + 2)\n");
        printf("6.  (7 / 3) * (2) + ((5 / (2)))\n");
        printf("7.  ((3) * (9 + 3) / ((3 + 3)\n");
        printf("8.  ((4) * (4) * (4)) / ((4) + (8))\n");
        printf("9.  (9 / 1 / 1) + (9 / 9))\n");
        printf("10.  (9 + 8) + ((7) / 6) - ((5) + (4) + 3))\n");
        printf("11. Exit Program.\n");

        //validate
        printf("\nEnter your choice: ");
        ret = scanf("%d", &input);
        if (ret != 1 || input > 11 || input < 1)
            input = reprompt();

        //set the infix string
        switch (input)
        {
        case 1:
            printf("\n");
            char *infix1 = "(8 + (3 * 9) - 6)";
            resolve(infix1);
            break;
        case 2:
            printf("\n");
            char *infix2 = "(5 * ((4) / (9)) + 1)";
            resolve(infix2);
            break;
        case 3:
            printf("\n");
            char *infix3 = "((6 + 6) + (7 * (2))";
            resolve(infix3);
            break;
        case 4:
            printf("\n");
            char *infix4 = "(8 / (2)) / ((2) + 9)";
            resolve(infix4);
            break;
        case 5:
            printf("/n");
            char *infix5 = "((2) * (2) * 2) / (2 + 2 + 2)";
            resolve(infix5);
            break;
        case 6:
            printf("\n");
            char *infix6 = "(7 / 3) * (2) + ((5 / (2)))";
            resolve(infix6);
            break;
        case 7:
            printf("\n");
            char *infix7 = "((3) * (9 + 3) / ((3 + 3)";
            resolve(infix7);
            break;
        case 8:
            printf("\n");
            char *infix8 = "((4) * (4) * (4)) / ((4) + (8))";
            resolve(infix8);
            break;
        case 9:
            printf("\n");
            char *infix9 = "(9 / 1 / 1) + (9 / 9))";
            resolve(infix9);
            break;
        case 10:
            printf("\n");
            char *infix10 = "(9 + 8) + ((7) / 6) - ((5) + (4) + 3))";
            resolve(infix10);
            break;
        case 11:
            printf("Exiting Program\n");
            exit(0);
        default:
            printf("Invalid option.\n");
        }
    } while (input != 11);

    return 0;
}
