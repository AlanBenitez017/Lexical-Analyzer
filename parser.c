/***************************************************************
  Student Name: Alan Benitez
  File Name: parser.c
  Project 2

  In this file I implement the parser as well as other helper methods for the lexical analysis
  Also, in this file I print the error statements.
***************************************************************/
#include "parser.h"

//Initialize the registers
void initRegisters(){
    registerr = 0;
    operatorr = NULL;
    variablesNum = 0;
}

//Will parse the lexemas from the beginning to the end of the file, and will print a syntax error
//if the file does not start with begin.
void parse() {

    if(lookahead != BEGIN){
        printf("Line: %d syntax error expected 'begin'\n", lineNum);
        deallocate();
        fclose(fp);
        exit(1);
    }else{
        match(BEGIN);
        while(lookahead != END){
            if(lookahead == INT){
                declaration();
            }
            else if(lookahead == ID){
                assignmentStatement();
            }
        }
        printf("Success\n");
        deallocate();
        fclose(fp);
    }
}

// Will process the declaration of the integer
void declaration(){
    match(INT);
    variable();
    match(';');
}

// Will process the variables after the declaring an integer and will insert to the symbol table
void variable(){
    while (lookahead == ID) {
        if (lookup(idLexeme)) {
            printf("Line %d - variable '%s' already defined \n",
                   lineNum, idLexeme);
            deallocate();
            fclose(fp);
            exit(1);
        }
        insertToTable(idLexeme, lineNum, idSize);
        match(ID);
    }
}

//Will do a lookup in the symbol table and will check for errors of redeclaration, undefined variables, and also will process the term
void assignmentStatement(){

    char tempVar[50];
    strcpy(tempVar, idLexeme);

    if (lookahead == INT) {
        match(INT);
        if (lookup(idLexeme) == true) {
            printf("Error - line %d - Redeclaration of %s\n", lineNum, idLexeme);
            deallocate();
            fclose(fp);
            exit(1);
        }
    }
    if (lookahead == ID && lookup(idLexeme) == false) {
        printf("Error - line %d - Variable %s is undefined\n", lineNum, idLexeme);
        deallocate();
        fclose(fp);
        exit(1);
    }

    match(ID);
    if (lookahead != '=') {
        printf("Line: %d syntax error expected '='\n", lineNum);
        deallocate();
        fclose(fp);
        exit(1);
    }

    match('=');
    term();
    match(';');

    registerr -= 1;
    sprintf(buffer + strlen(buffer), "%s = R%d\n", tempVar, registerr);
    printPostfix();
}

//If the identifier is correct, it will go on onto the next character, if it is incorrect
//it will print the error
void match(int t) {
  if (lookahead == t)
      lookahead = lexan();
  else{
    if (t == '(') {
      printf("Line: %d syntax error expected '%c'\n", lineNum, t);
    } else if (t == ')') {
      printf("Line: %d syntax error expected '%c'\n", lineNum, t);
    } else if (t == ';') {
      printf("Line: %d syntax error expected '%c'\n", lineNum, t);
    } else if (lookahead == UNDERSCORE_FRONT) {
      printf("Line: %d Identifier cannot start with underscore\n", lineNum);
    } else if (lookahead == UNDERSCORE_LAST) {
      printf("Line: %d Identifier cannot end with underscore\n", lineNum);
    } else if (lookahead == UNDERSCORE_SEQUENCE) {
      printf("Line: %d Identifier has underscore followed by other underscore\n",
           lineNum);
    }
    deallocate();
    fclose(fp);
    exit(1);
  }
}

//Will check if the expression is correct
void expression() {
    term();
    while (lookahead == '+' || lookahead == '-') {
        match(lookahead);
        term();
    }
}

//Will check if the term is correct
void term() {

    factor();
    while (lookahead == '+' || lookahead == '-' || lookahead == '*' ||
           lookahead == '/') {
        char * operatorr;
        if(lookahead == '+'){
            operatorr = "+";
        } else if(lookahead == '-'){
            operatorr = "-";
        } else if(lookahead == '*'){
            operatorr = "*";
        }else{
            operatorr = "/";
        }
        match(lookahead);
        factor();
        sprintf(buffer + strlen(buffer), "R%d = R%d %s R%d\n",
                registerr - 2, registerr - 2, operatorr, registerr - 1);
        registerr -= 1;
        strcpy(variables[variablesNum], operatorr);
        variablesNum++;
    }
}


void factor() {

    if (lookahead == '(') {
        match('(');
        if (lookahead == ')') {
            printf("Error - line %d - Expected identifier but got ')'\n", lineNum);
            deallocate();
            fclose(fp);
            exit(1);
        }
        term();
        match(')');
    } else if (lookahead == ID) {
        if (!lookup(idLexeme)) {

            printf("Error - line %d - Variable %s not declared\n", lineNum, idLexeme);
            deallocate();
            fclose(fp);
            exit(1);
        }
        sprintf(buffer + strlen(buffer), "R%d = %s\n", registerr++, idLexeme);
        strcpy(variables[variablesNum], idLexeme);
        variablesNum++;
        match(lookahead);
    } else if (lookahead == NUM) {
        sprintf(buffer + strlen(buffer), "R%d = %s\n", registerr++, numLexeme);
        strcpy(variables[variablesNum], numLexeme);
        variablesNum++;
        match(lookahead);
    }
}

//Prints the postfix
void printPostfix() {
    int i;
    sprintf(buffer + strlen(buffer), "*****[");
    for (i = 0; i < variablesNum - 1; i++) {
        sprintf(buffer + strlen(buffer), "%s", variables[i]);
        sprintf(buffer + strlen(buffer), ",");
    }
    sprintf(buffer + strlen(buffer), "%s", variables[i]);
    sprintf(buffer + strlen(buffer), "]*****\n");
    variablesNum = 0;
}