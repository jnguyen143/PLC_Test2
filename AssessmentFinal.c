/* front.c - a lexical analyzer system for integer literals and floating-point literals*/
#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;
char keywords[33][20] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);

/* Character classes */
#define LETTER 0      //[a-zA-Z]
#define DIGIT 1       //[0-9]
#define SINGLEQUOTE 1 //[\']
#define DOUBLEQUOTE 2 //[\"]
#define DECIMAL 3     //[\.]
#define UNDERSCORE 5  // [_]
#define UNKNOWN 99    //[^a-zA-Z0-9]

/* Token codes */
#define FLOAT_LIT 9
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define DECIMAL_POINT 27
#define FOR_CODE 30
#define IF_CODE 31
#define ELSE_CODE 32
#define WHILE_CODE 33
#define DO_CODE 34
#define INT_CODE 35
#define FLOAT_CODE 36
#define SWITCH_CODE 37
#define BOOL_LIT 38

/******************************************************/
/* main driver */
int main(void)
{
    /* Open the input data file and process its contents */
    if ((in_fp = fopen("front.in", "r")) == NULL)
        printf("ERROR - cannot open front.in \n");
    else
    {
        getChar();
        do
        {
            lex();
        } while (nextToken != EOF);
    }
    return 0;
}
/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token */
int lookup(char ch)
{
    switch (ch)
    {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void)
{
    if (lexLen <= 98)
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }
    else
        printf("Error - lexeme is too long \n");
}

/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void)
{
    if ((nextChar = getc(in_fp)) != EOF)
    {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

void getNonBlank(void)
{
    while (isspace(nextChar))
        getChar();
}

int lex(void)
{
    lexLen = 0;
    getNonBlank();
    switch (charClass)
    {
        /* Identifiers */
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT)
        {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
        /* Integer and float literals */
    case DIGIT:
        addChar();
        getChar();
        if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L')
        {
            addChar();
            getChar();
            nextToken = FLOAT_LIT;
            break;
            if (nextChar == 'E' || nextChar == 'e')
            {
                addChar();
                getChar();
                if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L')
                {
                    addChar();
                    getChar();
                    nextToken = FLOAT_LIT;
                    break;
                }
                if (nextChar == '-')
                {
                    addChar();
                    getChar();
                    while (charClass == DIGIT)
                    {
                        addChar();
                        getChar();
                        if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L')
                        {
                            addChar();
                            getChar();
                            nextToken = FLOAT_LIT;
                            break;
                        }
                    }
                    nextToken = FLOAT_LIT;
                    break;
                }
                else if (charClass == DIGIT)
                {
                    while (charClass == DIGIT)
                    {
                        addChar();
                        getChar();
                        if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L')
                        {
                            addChar();
                            getChar();
                            nextToken = FLOAT_LIT;
                            break;
                        }
                    }
                    nextToken = FLOAT_LIT;
                    break;
                }
            }
        }
        if (charClass == UNKNOWN && nextChar == '.')
        {
            addChar();
            getChar();
            while (charClass == DIGIT)
            {
                addChar();
                getChar();
                if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L')
                {
                    addChar();
                    getChar();
                    nextToken = FLOAT_LIT;
                    break;
                }
                if (nextChar == 'E' || nextChar == 'e')
                {
                    addChar();
                    getChar();
                    if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L')
                    {
                        addChar();
                        getChar();
                        nextToken = FLOAT_LIT;
                        break;
                    }
                    if (nextChar == '-')
                    {
                        addChar();
                        getChar();
                        while (charClass == DIGIT)
                        {
                            addChar();
                            getChar();
                            if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L')
                            {
                                addChar();
                                getChar();
                                nextToken = FLOAT_LIT;
                                break;
                            }
                        }
                        nextToken = FLOAT_LIT;
                        break;
                    }
                    else if (charClass == DIGIT)
                    {
                        while (charClass == DIGIT)
                        {
                            addChar();
                            getChar();
                            if (nextChar == 'f' || nextChar == 'F' || nextChar == 'l' || nextChar == 'L')
                            {
                                addChar();
                                getChar();
                                nextToken = FLOAT_LIT;
                                break;
                            }
                        }
                        nextToken = FLOAT_LIT;
                        break;
                    }
                }
            }
            nextToken = FLOAT_LIT;
        }
        else
        {
            nextToken = INT_LIT;
        }
        break;
        /* Parentheses and operators */
    case FOR_CODE:
        addChar();
        getChar();
        if (nextChar == 'f')
        {
            addChar();
            getChar();
            if (nextChar == 'o')
            {
                addChar();
                getChar();
                if (nextChar == 'r')
                {
                    nextToken = FOR_CODE;
                    break;
                }
            }
        }
    case IF_CODE:
        addChar();
        getChar();
        if (nextChar == 'i')
        {
            addChar();
            getChar();
            if (nextChar == 'f')
            {
                nextToken = IF_CODE;
                break;
            }
        }
    case ELSE_CODE:
        addChar();
        getChar();
        if (nextChar == 'e')
        {
            addChar();
            getChar();
            if (nextChar == 'l')
                addChar();
            getChar();
            if (nextChar == 's')
            {
                addChar();
                getChar();
                if (nextChar == 'e')
                {
                    nextToken = ELSE_CODE;
                    break;
                }
            }
        }
    case WHILE_CODE:
        addChar();
        getChar();
        if (nextChar == 'w')
        {
            addChar();
            getChar();
            if (nextChar == 'h')
            {
                addChar();
                getChar();
                if (nextChar == 'i')
                {
                    addChar();
                    getChar();
                    if (nextChar == 'l')
                    {
                        addChar();
                        getChar();
                        if (nextChar == 'e')
                        {
                            nextToken = ELSE_CODE;
                            break;
                        }
                    }
                }
            }
        }
    case DO_CODE:
        addChar();
        getChar();
        if (nextChar == 'd')
        {
            addChar();
            getChar();
            if (nextChar == 'o')
            {
                nextToken = DO_CODE;
                break;
            }
        }
    case SWITCH_CODE:
        addChar();
        getChar();
        if (nextChar == 's')
        {
            addChar();
            getChar();
            if (nextChar == 'w')
            {
                addChar();
                getChar();
                if (nextChar == 'i')
                {
                    addChar();
                    getChar();
                    if (nextChar == 't')
                    {
                        addChar();
                        getChar();
                        if (nextChar == 'c')
                        {
                            addChar();
                            getChar();
                            if (nextChar == 'h')
                            {
                                nextToken = SWITCH_CODE;
                                break;
                            }
                        }
                    }
                }
            }
        }

    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
        /* EOF */
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = '\0';
        break;
    } /* End of switch */
    printf("Next token is: %d, Next lexeme is %s\n",
           nextToken, lexeme);
    return nextToken;
} /* End of function lex */
