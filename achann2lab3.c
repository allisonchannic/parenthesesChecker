/* ----------------------------------------------------------------------------
 * Allison Channic
 * CS 211, Fall 2014
 * Lab time: Wed. 1:00
 * Project 3: Balanced symbol checker
 * ----------------------------------------------------------------------------
 * 
 * This program takes an expression (stored as c string) from user input and
 * checks it for balanced symbols ('()', '[]', '{}' and '<>'). A set of
 * symbols is defined as balanced if for each instance of an opening symbol 
 * ('(', '[', '{', '<'), there is a matching closing symbol (')', ']', '}', '>')
 * The user can also add other text characters which are irrelevant. The program
 * checks for balance by pushing each opening symbol onto a stack array, then
 * popping it once its matching closing symbol is encountered. If the expression
 * is not balanced, an arrow indicating where the error was found and what should
 * be there instead is printed to the user. The user can enter as many expressions
 * as he/she likes, the program resetting and initializing the stack each time.
 *
 * As per project instructions, this program also allows for debug mode
 * via the corresponding command line argument 
 *
 * Running the program looks like this:
 *
 * This program looks at different expressiosn to check if they have both an
 * opening mark ('<', '(', '{', '[') and a closing mark ('>', ')', '}', ']');
 * Press enter when you are finished with each expression. Enter 'q' or 'Q'
 * on a new expression line to quit.
 *
 * Enter a new expression:
 * []
 * This expression is balanced
 *
 * Enter a new expression:
 * [>
 *  ^ expecting ]
 *
 * Enter a new expression:
 * []>
 *   ^ missing <
 *
 * Enter a new expression:
 * <
 * ^ missing >
 */

//Include necessary C libraries
#include <stdio.h>
#include <stdlib.h>


/* Define the stack struct
 * Contains a pointer to a char array for the brackets, the size of the stack
 * and the element at the top of the stack
 */
typedef struct
{
	char *pStack;
	int size;
	int top;
}stack;


/* Function to initialize the stack
 * Contains a pointer to a stack struct as its parameter
 * Dynamically allocates a char array of size 2 for the stack
 * Sets the new size of the stack to 2 and initializes the top to -1
 */
void initializeStack(stack *theStack)
{
	//Allocate memory for the array pointer
	theStack->pStack = (char*)malloc(2*sizeof(char));

	//Initialize the size and top
	theStack->size = 2;
	theStack->top = -1;
}


/* Function to reset the stack
 * Takes a pointer to a stack struct as its parameter
 * Frees the array contained within the stack
 * Resets the size to 0 and the top to -1
 */
void resetStack(stack *theStack)
{
	//Free the array
	free(theStack->pStack);

	//Reset the size to zero and set top to -1
	theStack->size = 0;
	theStack->top = -1;

}


/* Function to check if the stack is empty
 * Takes a pointer to a stack struct as its parameter
 * Checks if the top element is less than 0
 * If so, the top element is -1 indicating that the stack is empty
 * Return 1 to represent true (the stack is empty)
 * Else teh stack is not empty so return 0 for false
 */
int stackIsEmpty(stack *theStack)
{
	//Check if the top element is less than 0
	//If so, stack is empty, so return 1 for true
	if (theStack->top < 0)
		return 1;
	//Else stack is not empty so return 0 for false
	else
		return 0;
}


/* Function to push an element to the top of the stack
 * Takes a pointer to a stack struct and the character to push onto the stack
 * as its parameters
 * Creates a temporary array of the size of the current array plus two
 * Copies the data from the original array to the temporary array
 * Sets the old array to the temporary array
 * Increases the top element and sets that value to the char to be pushed
 */
void push(stack *theStack, char toPush)
{
	//Initialize the temporary array for the new size
	char *tempArray = NULL;

	//Variables for the top and size of the stack for simplicity
	int top = theStack->top;
	int size = theStack->size;

	//Loop counter
	int i;

	//Check if the stack is full
	if (top == size-1)
	{
		//Allocate memory for the new array with two extra elements
		tempArray = (char*)malloc((size+2)*sizeof(char));

		//Copy the data from the old array to the new array
		for(i = 0; i < size; i++)
		{
			tempArray[i] = theStack->pStack[i];
		}

		//Free the memory
		free(theStack->pStack);

		//Set the stack array to the new array with the new size
		theStack->pStack = tempArray;

		//Increase the new size by 2
		theStack->size += 2;
	}

	//Increase the top element by one
	top++;

	//Set the top element of the stack to the character to be pushed
	theStack->pStack[top] = toPush;

	//Set the new top element
	theStack->top = top;
}


/* Function to retrieve the value at the top of the stack
 * Takes an instance of a stack as its paramter
 * Returns the value at the top element of the stack
 */
char getTop(stack theStack)
{
	return theStack.pStack[theStack.top];
}


/* Function to pop an element off of the stack
 * Takes a pointe to a stack struct as its parameter
 * Checks if the stack is empty and if so, indicates this to the user
 * If the stack is not empty, the top element of the stack is changed to the
 * one below it.
 */
void pop(stack *theStack)
{
	//Top element of the stack
	int top = theStack->top;

	//Check if the stack is empty and if so, tell the user
	int isEmpty = stackIsEmpty(theStack);
	if (isEmpty == 1)
		printf("Stack is empty. No values to delete/pop.");
	
	//Else there is something to be deleted. Change the top element to the
	//one afther the current top.
	else
		theStack->top = top-1;
}


/* Function to print spaces
 * Takes the number of spaces to be printed as an integer
 * Prints that number of spaces using a for loop
 * Used in main() to indicate where the error of balance was to hte user
 */
void printSpaces(int numSpaces)
{
	int i;
	for(i = 0; i < numSpaces; i++)
		printf(" ");
}

/* Main method
 * Takes the command line argument count and their values as parameters
 * to allow for debug mode
 * Gets an expression from user input and checks for balance among symbols
 * using an instance of a stack
 * Prints any errors, what they are, and where they're found to the user
 * or if the expression was balanced
 * Process repeats until the user enters 'q' or 'Q' to quit the program
 */
int main(int argc, char **argv)
{
	//Print program details to the user	
	printf("\n\nThis program looks at different expressions to check if they have");
	printf(" both an \nopening mark ('<', '(', '{', '[') and a closing mark ");
	printf("('>', ')', '}', ']').");
	
	//Prompt the user for their expression(s);
	printf("\nPress enter when you ");
	printf("are finished with each expression. Enter 'q' or 'Q' on a ");
	printf("\nnew expression line to quit.\n");

	//Instantiate the stack to hold the symbols
	stack expressionMarks;

	//Initialize char array/c string for user input
	char expression[301];

	//Character to represent what's on the top of the stack
	char charTop;

	//Boolean variable if the stack is empty
	int isEmpty;

	//Boolean variables for wrong or missing symbol
	int wrongSymbol = 0;
	int missingSymbol = 0;

	//Variable for string length
	int stringLength = 0;

	//Boolean variable for debug mode
	int debugMode = 0;

	//Get the command line argument values, see if any call for debug mode
	int i;
	for(i = 0; i < argc; i++)
	{
		//If so, set debug mode to truw (1)
		if (strcmp(argv[i], "-d") == 0)
			debugMode = 1;
	}


	do
	{
		//Initialize the stack
		initializeStack(&expressionMarks);

		//Prompt the user for his/her input and store it in the string
		printf("\n\nEnter a new expression:\n");
		fgets(expression, 301, stdin);

		//Get the string length
		stringLength = strlen(expression);

		//Go through the entire string
		for(i = 0; i < stringLength; i++)
		{
			//Get the character at the top of the stack
			charTop = getTop(expressionMarks);

			//Check if the stack is empty or not
			isEmpty = stackIsEmpty(&expressionMarks);

			//If there's an opening symbol, push it to the stack
			if(expression[i] == '(' || expression[i] == '{' || 
				expression[i] == '[' || expression[i] == '<')
			{
			   		push(&expressionMarks, expression[i]);

			   		//If debug mode is on, print this value to the user
			   		if(debugMode == 1)
			   		{
			   			printf("\nCharacter pushed: %c", expression[i]);
			   		}

			}
			
			//Else if a closing symbol was encountered
			else if(expression[i] == ')')
			{
				//Check if the top is its corresponding opening symbol
				if (charTop == '(')
				{
					//Pop the opening symbol from the stack
					pop(&expressionMarks);

					//If debug mode is on, print this value to the user
					if (debugMode == 1)
						printf("\nCharacter popped: %c", charTop);
					continue;
				}

				//Else, check if an opening symbol was found, just not
				//the one corresponding to that closing mark
				//Indicate the error to the user
				else if (charTop == '{')
				{
					printSpaces(i);
					printf("^ expecting }");
					wrongSymbol = 1;
					break;
				}

				else if(charTop == '[')
				{
					printSpaces(i);
					printf("^ expecting ]");
					wrongSymbol = 1;
					break;
				}

				else if(charTop == '<')
				{
					printSpaces(i);
					printf("^ expecting >");
					wrongSymbol = 1;
					break;
				}

				//Else, check if the stack is empty, indicating there is no
				//corresponding opening bracket
				//Indicate the error to the user
				else if(isEmpty == 1)
				{
					printSpaces(i);
					printf("^ missing (");
					missingSymbol = 1;
					break;
				}

				//Same as above, only account for the user inputing only one
				//Character
				else if(isEmpty == 1 && stringLength == 1)
				{
					printf("^ missing (");
					missingSymbol = 1;
					break;
				}	
			}

			//Repeat the above process for all closing symbols
			else if(expression[i] == ']')
			{
				if (charTop == '[')
				{
					pop(&expressionMarks);
					if (debugMode == 1)
						printf("\nCharacter popped: %c", charTop);
					continue;
				}

				else if (charTop == '{')
				{
					printSpaces(i);
					printf("^ expecting }");
					wrongSymbol = 1;
					break;
				}

				else if(charTop == '(')
				{
					printSpaces(i);
					printf("^ expecting )");
					wrongSymbol = 1;
					break;
				}

				else if(charTop == '<')
				{
					printSpaces(i);
					printf("^ expecting >");
					wrongSymbol = 1;
					break;
				}

				else if(isEmpty == 1)
				{
					printSpaces(i);
					printf("^ missing [");
					missingSymbol = 1;
					break;
				}

				else if(isEmpty == 1 && stringLength == 1)
				{
					printf("^ missing [");
					missingSymbol = 1;
					break;
				}
			}

			else if(expression[i] == '}')
			{
				if (charTop == '{')
				{
					pop(&expressionMarks);
					if (debugMode == 1)
						printf("\nCharacter popped: %c", charTop);
					continue;
				}

				else if (charTop == '(')
				{
					printSpaces(i);
					printf("^ expecting )");
					wrongSymbol = 1;
					break;
				}

				else if(charTop == '[')
				{
					printSpaces(i);
					printf("^ expecting ]");
					wrongSymbol = 1;
					break;
				}

				else if(charTop == '<')
				{
					printSpaces(i);
					printf("^ expecting >");
					wrongSymbol = 1;
					break;
				}

				else if(isEmpty == 1)
				{
					printSpaces(i);
					printf("^ missing {");
					missingSymbol = 1;
					break;
				}

				else if(isEmpty == 1 && stringLength == 1)
				{
					printf("^ missing {");
					missingSymbol = 1;
					break;
				}
			}

			else if(expression[i] == '>')
			{
				if (charTop == '<')
				{
					pop(&expressionMarks);
					if (debugMode == 1)
						printf("\nCharacter popped: %c", charTop);
					continue;
				}

				else if (charTop == '{')
				{
					printSpaces(i);
					printf("^ expecting }");
					wrongSymbol = 1;
					break;
				}

				else if(charTop == '[')
				{
					printSpaces(i);
					printf("^ expecting ]");
					wrongSymbol = 1;
					break;
				}

				else if(charTop == '(')
				{
					printSpaces(i);
					printf("^ expecting )");
					wrongSymbol = 1;
					break;
				}

				else if(isEmpty == 1)
				{
					printSpaces(i);
					printf("^ missing <");
					missingSymbol = 1;
					break;
				}

				else if(isEmpty == 1 && stringLength == 1)
				{
					printf("^ missing <");
					missingSymbol = 1;
					break;
				}
			}
			
		}

		//Check if hte stack is now empty and get thew new top of the stack
		isEmpty = stackIsEmpty(&expressionMarks);
		charTop = getTop(expressionMarks);

		//If the stack is empty, there are no missing symbols, and the user
		//does not want to quit, the expression is balanced.
		//Print this to the user
		if(isEmpty == 1 && missingSymbol != 1 && expression[0] != 'q' 
			&& expression[0] != 'Q')
		{
			printf("\nThe expression is balanced");
		}

		//Else there is a missing closing symbol
		//Find the missing symbol, where it is, and print the error to the user
		else if (isEmpty == 0)
		{
			if (charTop == '(' && wrongSymbol != 1)
			{
				printSpaces(stringLength-1);
				printf("^ missing )");
			}

			else if (charTop == '[' && wrongSymbol != 1)
			{
				printSpaces(stringLength-1);
				printf("^ missing ]");
			}

			else if (charTop == '{' && wrongSymbol != 1)
			{
				printSpaces(stringLength-1);
				printf("^ missing }");
			}

			else if(charTop == '<' && wrongSymbol != 1)
			{
				printSpaces(stringLength-1);
				printf("^ missing >");
			}

		}

		//Reset the stack for the next expression
		resetStack(&expressionMarks);

		//Reset boolean variables
		missingSymbol = 0;
		wrongSymbol = 0;
		isEmpty = 0;

	//Repeat this process until the user quits the program
	}while(expression[0] != 'q' && expression[0] != 'Q');

	//Let the user know the program is exiting.
	printf("\nNow exiting.");
}