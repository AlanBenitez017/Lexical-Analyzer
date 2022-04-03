/***************************************************************
  Student Name: Alan Benitez
  File Name: lexer.h
  Project 2

  This is the header file where I declare the variables needed for the lexer.c file
***************************************************************/
#ifndef LEXER_H
#define LEXER_H
#include "symbol.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAX 600

FILE * fp;
char ch;
int lineNum;
int type;
int lookahead;
int idSize;
char idLexeme[MAX];
char numLexeme[MAX];

int lexan();
void initLexer();


#endif
