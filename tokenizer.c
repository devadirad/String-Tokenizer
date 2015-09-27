/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */


struct TokenizerT_ {
    char* tokeninput;			// stores the string
    char* nextToken;			// stores the final token to be outputted, obtained after each iteration
    int ptrInput;				// current position in the string
    char currentState;			// stores the type of current token for swtch case
    char prevState;				// stores the type of previous token for switch case
    int tokenLengthCounter;		// stores the length of each token
    char tokenChecker;			// stores current character
    
};

typedef struct TokenizerT_ TokenizerT;

const char *symbols[49][2] = {			//Symbol table
    {"(","round left brace"},
    {")","round right brace"},
    {"[","square left brace"},
    {"]","square right brace"},
    {"{","left curly brace"},
    {"}","right curly brace"},
    {"~","tilde"},
    {"!","not"},
    {"@","at"},
    {"#","hash"},
    {"$","dollar"},
    {"%","mod"},
    {"^","raised to"},
    {"&","and"},
    {"*","star"},
    {"-","dash"},
    {"+","plus"},
    {"++","increment"},
    {"_","underscore"},
    {"=","equal to"},
    {"==","is equal to"},
    {"--","decrement"},
    {"`","backtick "},
    {":","colon"},
    {";","semi-colon"},
    {"\"","quotes"},
    {"'","single quote"},
    {"<","less than"},
    {"<=","less than equal to"},
    {">","greater than"},
    {">=","greater than equal to"},
    {"<<","left shift"},
    {">>","right shift"},
    {".","dot"},
    {"/","forward slash"},
    {"|","or"},
    {"||","logical or"},
    {"&&","logical and"},
    {"!=","not equal to"},
    {"+=","plus equal"},
    {"-=","minus equal"},
    {"*=","star equal"},
    {"/=","divide equal"},
    {"%=","mod equal"},
    {"&=","and equal"},
    {"|=","or equal"},
    {"->","pointer"},
    {"?","question mark"},
    {",","comma"}
};

const char *esc[11][2] = {		//Escape sequences with their hex value in ASCII
    {"\\a","[0x07]"},
    {"\\b","[0x08]"},
    {"\\f","[0x0C]"},
    {"\\n","[0x0A]"},
    {"\\r","[0x0D]"},
    {"\\t","[0x09]"},
    {"\v","[0x0B]"},
    {"\\","[0x5C]"},
    {"\\'","[0x27]"},
    {"\\\"","[0x22]"},
    {"\\\?","[0x3F]"},
};
/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *ts) {
    
    //creates variable sized inputcopy string
    
    
    //creates a tokenizer
    TokenizerT *tk = malloc(sizeof(TokenizerT));
    
    //sets the value of the tokeninput in tokenizer as inputcopy, initialize other variables as well
    
    tk->tokeninput =malloc(strlen(ts)); 			    			//allocate the string no more than length of paramter to save memory
    strncpy(tk->tokeninput,ts,strlen(ts));
    tk->nextToken = (char*)malloc(strlen(ts));						//token can have max size equal to the whole string
    tk->ptrInput = 0;
    tk->currentState = 'd';
    tk->prevState = 'd';
    tk->tokenLengthCounter = 0;
    tk->tokenChecker = tk->tokeninput[tk->ptrInput];
    
    //checks if tokeninput is null
    if(tk->tokeninput != NULL){
        return tk;
    }
    else  return NULL;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    
    free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */
void tokenReturn(TokenizerT *tk){
    memset(tk->nextToken,0,strlen(tk->nextToken)); //erases any previous values
    strncpy(tk->nextToken, tk->tokeninput+tk->ptrInput, tk->tokenLengthCounter+tk->ptrInput);
    tk->nextToken[tk->tokenLengthCounter] = '\0';
    
    //move ptr to next character
    tk->ptrInput = tk->ptrInput+tk->tokenLengthCounter;
    //tk->prevState = tk->currentState;
    tk->currentState = 'd'; //reset case to default after token is returnend
}

int isSymbol(char sym)			//function that checks if token is symbol
{
    int i=0;
    for (i=0;i<49;i++)
        if(*symbols[i][0]==sym)
            return i;				//return the index i that will enable to fetch both the key-value pair
    return 0;
}

/*
 this function is made similar to isSymbol but checks symbols of length=2. Although this has repitition of code, storing each character as
 a string to check if its a 2-length symbol and then freeing it will take more time
 */
int iscombinedSymbol(char *sym)			//check for symbol of length 2
{
    int i=0;
    for (i=0;i<49;i++)
        if(strncmp(symbols[i][0],sym,3)==0)
            return i;
    return 0;
}

int isEscape(char *seq)			//check escape sequence
{
    int i=0;
    for(i=0;i<11;i++) {
        if(esc[i][0][1]==seq[1]) {
            return i;
        }
    }
    return 0;
}

char *TKGetNextToken( TokenizerT * tk ) {
    
    int Mcheck= 0;
    if (tk->tokeninput == NULL) {
        return NULL;
    }
    
    //get first character of string into tk->tokenChecker, start counting the length of the input
    tk->tokenLengthCounter = 0;
    tk->tokenChecker = tk->tokeninput[tk->ptrInput];
    //see if token checker is NULL symbol
    while (tk->tokenChecker != '\0') {
        
        switch (tk->currentState) {
                /**/       case 'd':     //default case
                
                if (tk->tokenChecker=='0') {    //string starts with a 0, octal possibly
                    tk->currentState = '0';
                    break;
                }
                
                else if (isdigit(tk->tokenChecker)) {    //string starts with a digit
                    tk->currentState = '1';
                    break;
                }
                
                else if (isalpha(tk->tokenChecker)) {    //string starts with a letter
                    tk->currentState = 'w';
                    break;
                }
                
                else if (isspace(tk->tokenChecker)) {    //string starts with a whitespace
                    tk->currentState = 's';
                    break;
                }
                
                else if((isSymbol(tk->tokenChecker))>0) {	// string starts with a operator
                    if(isSymbol(tk->tokeninput[tk->ptrInput+1])>0) {
                        char *test;
                        test=malloc(3*sizeof(char));
                        test[0]=tk->tokenChecker;
                        test[1]=tk->tokeninput[tk->ptrInput+1];
                        test[2]='\0';
                        if(iscombinedSymbol(test)==0) {
                            Mcheck=1;
                            tk->prevState=tk->currentState;
                            tk->currentState='m';
                            tk->tokenLengthCounter++;
                            tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                            break;
                        }
                        else {
                            tk->ptrInput++;
                            tk->tokenLengthCounter++;
                            tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                            tk->prevState='r';
                            tk->currentState='d';
                            tokenReturn(tk);
                            return test;
                        }
                				}
                    else{
                        tk->currentState= 'r';
                        break;}
                    
                }
                
                else if(tk->tokenChecker=='\\')
                {
                    int index=0;
                    char *seq=malloc(3*sizeof(char));
                    seq[0]='\\';
                    if(tk->tokeninput[tk->ptrInput+1]=='\\')
                        seq[1]='\\';
                    else
                        seq[1]=tk->tokeninput[tk->ptrInput+1];
                    seq[2]='\0';
                    if(isEscape(seq)>0)
                    {
                        tk->ptrInput=tk->ptrInput+2;
                        tk->tokenLengthCounter++;
                        tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                        tk->prevState='q';
                        tk->currentState='d';
                        tokenReturn(tk);
                        return seq;
                        break;
                				}
                    else {
                        Mcheck=1;
                        tk->prevState=tk->currentState;
                        tk->currentState='m';
                    }
                    break;
                }
                
                else tk->currentState = 'c';                  //string starts with other character
                break;
                
                /**/       case 'w':     //word case
                while(isalnum((int)tk->tokenChecker) && tk->tokenChecker != '\0'){      //loop until non-alphanumeric
                    tk->tokenLengthCounter++;
                    tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                }
                tk->prevState = tk->currentState;
                tokenReturn(tk);
                return tk->nextToken;
                
                /**/       case 's':      //whitespace case
                
                //go to next char
                tk->tokenLengthCounter++;
                tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                tk->tokenLengthCounter=0;
                tk->ptrInput++;
                tk->prevState = tk->currentState;
                tk->currentState = 'd'; //reset case to default after whitespace is skipped
                break;
                
                /**/       case '0':       //begins with a zero, possibly octal
                //see next digit
                tk->tokenLengthCounter++;
                tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                
                //if x is seen, go to hex
                if (tk->tokenChecker=='x' || tk->tokenChecker=='X') {
                    tk->prevState = tk->currentState;
                    tk->currentState = 'h'; //set case to hex
                    break;
                }
                
                //if 8 or 9 is seen, go to integer
                if (tk->tokenChecker=='8' || tk->tokenChecker=='9') {
                    printf("Please format floats and integers without extraneous zeroes or letters\n");
                    tk->prevState = tk->currentState;
                    tk->currentState = 'm'; //set case to malfunction
                    break;
                }
                
                //if . is seen, go to float
                if (tk->tokenChecker=='.') {
                    tk->prevState = tk->currentState;
                    tk->currentState = 'f'; //set case to float
                    break;
                }
                
                //if next character is not alphanumeric, token is zero, return it
                if (!isalnum((int)tk->tokenChecker)) {
                    tk->prevState = 'i';
                    tk->currentState = 'd'; //set case to default after token is returned
                    tokenReturn(tk);
                    return tk->nextToken;
                }
                //otherwise, character is octal
                tk->prevState = tk->currentState;
                tk->currentState = 'o'; //set case to default after token is returned
                break;
                
                /**/       case '1':       //begins with a 1, decimal integer or float
                
                Mcheck=0;
                tk->tokenLengthCounter++;
                tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                
                while(1){      //loop until non-numeric
                    
                    //if it has a decimal point, send it to float
                    if (tk->tokenChecker=='.') {
                        tk->prevState = tk->currentState;
                        tk->currentState = 'f'; //set case to float
                        break;
                    }
                    
                    //if its a alphanumeric, keep going
                    if (!isalnum((int)tk->tokenChecker)) {
                        break;
                    }
                    
                    //but make sure it's not null
                    if (tk->tokenChecker == '\0') {
                        break;
                    }
                    
                    //if there is an E, move to exponential float type
                    if (tk->tokenChecker == 'e' || tk->tokenChecker == 'E') {
                        tk->prevState = tk->currentState;
                        tk->currentState = 'e'; //set case to exp float
                        break;
                    }
                    
                    
                    //if it is alpha, give error to correctly format numbers
                    if (isalpha((int)tk->tokenChecker)) {
                        Mcheck= 1;
                        printf("Please format floats and integers without extraneous zeroes or letters\n");
                        break;
                    }
                    
                    tk->tokenLengthCounter++;
                    tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                }
                
                if (tk->currentState == 'f' || tk->currentState == 'e') {
                    break;
                }
                if (Mcheck == 1) {
                    tk->prevState = tk->currentState;
                    tk->currentState = 'm'; //set case to malfunction
                    break;
                }
                else{
                    tk->prevState = tk->currentState;
                    tokenReturn(tk);
                    return tk->nextToken;
                }
                
                
                
                
                
                /**/       case 'h':       //hexadecimal case
                
                Mcheck=0;
                //skip past 'x'
                tk->tokenLengthCounter++;
                tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                
                //checks if there exists a digit after decimal point
                if (!isdigit((int)tk->tokenChecker)) {
                    tk->prevState = tk->currentState;
                    tk->currentState = 'm'; //set case to malfunction
                    printf("Invalid input, please format hexadecimals with values after the 0x");
                    break;
                }
                
                while(1){      //loop until non-numeric
                    
                    if (tk->tokenChecker == '.') {
                        printf("Please provide valid hex values, and format floats without extraneous zeroes or letters\n");
                        Mcheck= 1;
                        break;
                    }
                    
                    //if its a alphanumeric, keep going
                    if (!isalnum((int)tk->tokenChecker)) {
                        break;
                    }
                    //but make sure it's not null
                    if (tk->tokenChecker == '\0') {
                        break;
                    }
                    
                    //if it is alpha, give error to correctly format octals/numbers
                    if (!isxdigit((int)tk->tokenChecker)) {
                        Mcheck= 1;
                        printf("Please provide valid hex values, and do not begin words with 0\n");
                        break;
                    }
                    
                    
                    tk->tokenLengthCounter++;
                    tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                }
                
                
                if (Mcheck == 1) {
                    tk->prevState = tk->currentState;
                    tk->currentState = 'm'; //set case to malfunction
                    break;
                }
                else{
                    tk->prevState = tk->currentState;
                    tokenReturn(tk);
                    return tk->nextToken;
                }
                
                /**/       case 'o':       //octal case
                Mcheck=0;
                while(1){      //loop until non-numeric
                    
                    if (tk->tokenChecker == '.') {
                        printf("Please provide valid octals (0-7), and format floats without extraneous zeroes\n");
                        Mcheck= 1;
                        break;
                    }
                    
                    //if its a alphanumeric, keep going
                    if (!isalnum((int)tk->tokenChecker)) {
                        break;
                    }
                    //but make sure it's not null
                    if (tk->tokenChecker == '\0') {
                        break;
                    }
                    
                    //if it is alpha, give error to correctly format octals/numbers
                    if (isalpha((int)tk->tokenChecker)) {
                        Mcheck= 1;
                        printf("Please provide valid octals (0-7), and do not begin words with 0\n");
                        break;
                    }
                    
                    // if there are invalid numbers, give error for correct format
                    if (tk->tokenChecker == '8' || tk->tokenChecker == '9') {
                        Mcheck= 1;
                        printf("Please provide valid octals (0-7), and do not begin non-octal/hex numerical values with 0\n");
                        break;
                    }
                    
                    tk->tokenLengthCounter++;
                    tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                }
                
                
                if (Mcheck == 1) {
                    tk->prevState = tk->currentState;
                    tk->currentState = 'm'; //set case to malfunction
                    break;
                }
                else{
                    tk->prevState = tk->currentState;
                    tokenReturn(tk);
                    return tk->nextToken;
                }
                
                /**/       case 'f':       //float case
                Mcheck=0;
                //skip past '.'
                tk->tokenLengthCounter++;
                tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                
                //checks if there exists a digit after decimal point
                if (!isdigit((int)tk->tokenChecker)) {
                    tk->prevState = tk->currentState;
                    tk->currentState = 'm'; //set case to malfunction
                    break;
                }
                
                while(1){      //loop until non-numeric
                    
                    //if its a alphanumeric, keep going
                    if (!isalnum((int)tk->tokenChecker)) {
                        break;
                    }
                    //but make sure it's not null
                    if (tk->tokenChecker == '\0') {
                        break;
                    }
                    
                    //if there is an E, move to exponential float type
                    if (tk->tokenChecker == 'e' || tk->tokenChecker == 'E') {
                        tk->prevState = tk->currentState;
                        tk->currentState = 'e'; //set case to exp float
                        break;
                    }
                    
                    //if it is alpha still, give error to correctly format octals/numbers
                    if (isalpha((int)tk->tokenChecker)) {
                        Mcheck= 1;
                        printf("Please provide valid floats with numbers and one exponential only\n");
                        break;
                    }
                    
                    
                    tk->tokenLengthCounter++;
                    tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                }
                
                
                if (Mcheck == 1) {
                    tk->prevState = tk->currentState;
                    tk->currentState = 'm'; //set case to malfunction
                    break;
                }
                else if(tk->currentState != 'e'){
                    tk->prevState = tk->currentState;
                    tokenReturn(tk);
                    return tk->nextToken;
                }
                
                /**/       case 'e':       //exponential float
                Mcheck=0;
                //skip past 'e'
                tk->tokenLengthCounter++;
                tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                
                //if first character is a positive or negative sign, skip past it and see if there's a number afterwards
                if (tk->tokenChecker=='-'||tk->tokenChecker=='+') {
                    tk->tokenLengthCounter++;
                    tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                }
                if (!isdigit((int)tk->tokenChecker)) {
                    printf("Please provide valid floats with numbers and ONE exponential only, followed by an integer value\n");
                    tk->prevState = tk->currentState;
                    tk->currentState = 'm'; //set case to malfunction
                    break;
                }
                
                
                while(1){      //loop until non-numeric
                    
                    
                    //if its a alphanumeric, keep going
                    if (!isalnum((int)tk->tokenChecker)) {
                        break;
                    }
                    //but make sure it's not null
                    if (tk->tokenChecker == '\0') {
                        break;
                    }
                    
                    //if it is alpha still, give error to correctly format octals/numbers
                    if (isalpha((int)tk->tokenChecker)) {
                        Mcheck= 1;
                        printf("Please provide valid floats with numbers and ONE exponential only, followed by an integer value\n");
                        break;
                    }
                    
                    
                    tk->tokenLengthCounter++;
                    tk->tokenChecker = tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                }
                
                
                if (Mcheck == 1) {
                    tk->prevState = tk->currentState;
                    tk->currentState = 'm'; //set case to malfunction
                    break;
                }
                else{
                    tk->prevState = tk->currentState;
                    tokenReturn(tk);
                    return tk->nextToken;
                }
                
                /**/ 		case 'r': 		// operators case
                tk->tokenLengthCounter++;
                tk->tokenChecker=tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                tk->prevState=tk->currentState;
                tokenReturn(tk);
                return tk->nextToken;
                break;
                
            case 'q':		// Escape sequences
                tk->tokenLengthCounter++;
                tk->tokenChecker=tk->tokeninput[tk->ptrInput+tk->tokenLengthCounter];
                tk->prevState=tk->currentState;
                tokenReturn(tk);
                return tk->nextToken;
                break;
                /**/       case 'm':       //malfunction, bad input case
                tk->prevState = tk->currentState;
                tokenReturn(tk);
                return tk->nextToken;
                break;
                
        }
        
    }
    
    return NULL;
}



void printTokens(TokenizerT *tk){
    int index=0;										// variable that stores the array index of a symbol from the symbol table
    while(tk->tokeninput[tk->ptrInput] != '\0'){		// until End of string
        char* temp = TKGetNextToken(tk);				// store the token obtained in temp
        if (temp != NULL) {
            
            if (tk->prevState == 'm') {
                printf("Invalid input\n");
                break;
            }
            
            //switch statement to print out type
            switch (tk->prevState) {
                case 'w':
                    printf("word ");
                    break;
                case '1':
                    printf("integer ");
                    break;
                case 'f':
                    printf("float ");
                    break;
                case 'e':
                    printf("float ");
                    break;
                case 'h':
                    printf("hex constant ");
                    break;
                case 'o':
                    printf("octal constant ");
                    break;
                case 'r':
                    index=iscombinedSymbol(temp);
                    printf("%s ",symbols[index][1]);
                    break;
                case 'q':
                    index=isEscape(temp);
                    printf("%s",esc[index][1]);
                    break;
            }
            
            printf("\"%s\"\n",temp); //print out token
        }
        else break;
        
    }
    
    //function here to figure out what type the token is
    
    //print type and then "token"
    
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char * argv[]) {
    
    if (argc != 2) {
        //print error statement
        printf("please enter exactly one string for tokenizing.");
    }
    else{
        char *inputstring = argv[1];
        
        TokenizerT *tk = TKCreate(inputstring);
        
        printTokens(tk);
        TKDestroy(tk);
        
        
    }
    return 0;
}

