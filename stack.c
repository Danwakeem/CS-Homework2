#include "stack.h"
char charStack[SIZE];
int stack[SIZE];
int stackIndex;
void initStack()
{
	stackIndex = 0;
}
void push(int c)    	// add int to top of stack
{
	assert(stackIndex <= SIZE);
	stack[stackIndex++] = c;
}
int pop()           	// remove the top of stack and return it.
{
	int c;
	assert(stackIndex > 0);
	c = stack[stackIndex-1];
	stack[stackIndex-1] = -1;
	stackIndex--;
	return c;
}
void printStack()   	// just for debugging purposes.
{
	int i = stackIndex-1;
	printf("The Int Stack is\n");
	while( i >= 0 )
	{
    	printf("%d\n",stack[i--]);
	}
}
void initCharStack()
{
	stackIndex = 0;
}
void pushChar(char c)   // add character to top of stack
{
	assert(stackIndex <= SIZE);
	charStack[stackIndex++] = c;
}
char popChar()      	// remove the top of stack and return it.
{
	char c;
	assert(stackIndex > 0);
	c = charStack[stackIndex-1];
	charStack[stackIndex-1] = '\0';
	stackIndex--;
	return c;
}
void printCharStack()   // just for debugging purposes.
{
	int i = stackIndex-1;
	printf("The Character Stack is\n");
	while( i >= 0 )
	{
    	printf("%c\n",charStack[i--]);
	}
}

