/***************************************************************
  Student Name: Alan Benitez
  File Name: lexer.c
  Project 2

  In this file, I initialize and implement the lexan method for the lexical analyzer.
  Furthermore, I insert values to the symbol table
***************************************************************/
#include "lexer.h"

//Initialize the lexer
void initLexer() {
    lineNum = 1;
    idSize = 0;
    lookahead = lexan();
}


//lexan method for the lexical analyzer that does all the magic
int lexan() {
    memset(idLexeme, 0, MAX);
    memset(numLexeme, 0, MAX);
    while (1) {
        ch = fgetc(fp);
        if (ch == ' ' || ch == '\t' || ch == ',') {
            ; //Do nothing
        } else if (ch == '\n') {
        //Increment line number
            lineNum++;
        } else if (ch == '~') {
            while (ch != '\n') {
                //Read the comment until finding a new line and do nothing
                ch = fgetc(fp);
            }
            ungetc(ch, fp);
        } else if (isdigit(ch)) {
            while (isdigit(ch)) {
                //Get the number into numLexeme
                strncat(numLexeme, &ch, 1);
                ch = fgetc(fp);
            }
            ungetc(ch, fp);
            return NUM;
        } else if (isalpha(ch)) {
            while (isalpha(ch) || isdigit(ch) || ch == '.' || ch == '_') {
            // insert into idLExeme
                strncat(idLexeme, &ch, 1);
                idSize++;
                ch = fgetc(fp);
            }
            // check if it is already in the table
          //  type = lookup(idLexeme);
           type = getTokenType(idLexeme, lineNum, idSize);
           /*if (type == NOT_FOUND) {
            // insert value into symbol table
                type = insertToTable(idLexeme, lineNum, idSize);
            }*/
            ungetc(ch, fp);
            return type;
        } else if (ch == EOF) {
            return DONE;
        } else {
            return ch;
        }
    }
}