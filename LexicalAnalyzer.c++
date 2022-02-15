#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define r(name) 
#define append   


int characterClasses;
char lexeme[100];
char nextCharacter;
int lexLength;
int token;
int nextToken;
FILE *in_fp;


int search(char ch);
void addChar(void);
void retrieve(void);
void whiteSpace(void);
int lex(void);



#define SINGLE_CHAR 0
#define DIGIT 1
#define UNKNOWN 99


#define MINUS 1
#define STAR  2
#define SLASH 3
#define LPAR  4
#define RPAR  5
#define PERCENT 6
#define INT 7
#define DEC 8
#define BOOL 9
#define IDENT 10
#define EQUAL 11
#define PLUS 12
#define STRING 13



int main(void) {

	 if ((in_fp = fopen("input.txt", "r")) == NULL)
	 	printf("file error \n");
	 else {
	 	retrieve();
	 do {
	 	lex();
	 } while (nextToken != EOF);
	 }
	 return 0;
}


int search(char ch) {
	 switch (ch) {
		 case '(':
			 addChar();
			 nextToken = LPAR;
			 break;
    case '=':
			 addChar();
			 nextToken = EQUAL;
			 break;
		 case ')':
			 addChar();
			 nextToken = RPAR;
			 break;
  
    case '%':
			 addChar();
			 nextToken = PERCENT;
			 break;
		 case '+':
			 addChar();
			 nextToken = PLUS;
			 break;
		 case '-':
			 addChar();
			 nextToken = MINUS;
			 break;
		 case '*':
			 addChar();
			 nextToken = STAR;
			 break;
		 case '/':
			 addChar();
			 nextToken = SLASH;
			 break;
		 default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}


void addChar(void) {
	if (lexLength <= 100) {
		lexeme[lexLength++] = nextCharacter;
		lexeme[lexLength] = '\0';
	} else
	printf("THIS LEXEME HAS TOO MANY LETTERS \n");
}
//typedef enum {
//    String_Lit
///} OUR_TOKEN;
//typedef structure {
  //  OUR_TOKEN
  //   token;
 //   int error_line, error_column;
 //   union {
  //      int n;              
  ////      char *text;         
   // };
//} STRING_TOKENS_;
//static STRING_TOKENS_ string_lit(int start, int error_line, int error_column) { 
 //  
 
 //   while (next_ch() != start) {
 //       if (the_ch == '\n') error(error_line, error_column, "End of Line");
 //       if (the_ch == EOF)  error(error_line, error_column, "EOF");
 //       append(text, (char)the_ch);
 //   }
 //   append(text, '\0');
 
//    next_ch();
//    return (STRING_TOKENS_){String, error_line, error_column, {.text=text}};
//}
 


void retrieve(void) {
	 if ((nextCharacter = getc(in_fp)) != EOF) {
		 if (isalpha(nextCharacter))
		 	characterClasses = SINGLE_CHAR;
		 else if (isdigit(nextCharacter))
		 	characterClasses = DIGIT;
		 else
		 	characterClasses = UNKNOWN;
	 } else
	 	characterClasses = EOF;
}


/******************************************************/

void whiteSpace(void) {
	while (isspace(nextCharacter))
	retrieve();
}


int lex(void) {
	 lexLength = 0;
	 whiteSpace();
	 switch (characterClasses) {

		 case SINGLE_CHAR:
			 addChar();
			 retrieve();
			 while (characterClasses == SINGLE_CHAR || characterClasses == DIGIT) {
				 addChar();
				 retrieve();
			 }
			 nextToken = IDENT;
			 break;
	
		 case DIGIT:
			 addChar();
			 retrieve();
			 while (characterClasses == DIGIT) {
				 addChar();
				 retrieve();
			 }
			 nextToken = INT;
		 	break;
		
		 case UNKNOWN:
			search(nextCharacter);
			 retrieve();
			 break;
		
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 }
	 printf("analyzer read: %s, The token for this is %d\n",
	  lexeme,nextToken);
	 return nextToken;
} 