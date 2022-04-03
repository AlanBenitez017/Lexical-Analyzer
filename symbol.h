/***************************************************************
  Student Name: Alan Benitez
  File Name: symbol.h
  Project 2

  This is the header file where I declare the variables needed for the symbol.c file
***************************************************************/
#ifndef SYMBOL_H
#define SYMBOL_H
#include "lexer.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID 300
#define NUM 301
#define BEGIN 400
#define END 401
#define NOT_FOUND -1
#define INT 500
#define MAX 600
#define DONE 700
#define UNDERSCORE_FRONT 800
#define UNDERSCORE_LAST 801
#define UNDERSCORE_SEQUENCE 802
#define SEMICOLON 900
#define ADD_OP 901
#define SUB_OP 902
#define MULT_OP 903
#define DIV_OP 904

typedef struct linkedList {
  char value[MAX];
  int data;
  int line;
  struct linkedList * next;
  
}node_t;


node_t * head;
node_t * newInsertion;
int tokenType;


void initSymbolTable();
int insertToTable(char * lexeme, int line, int idSize);
bool lookup(char * lexeme);
int getTokenType(char * lexeme, int line, int idSize);
void printSmall();
bool putSmall(char * lexema, int line, int idSize);
bool lookupForRegisters(char * lexeme);

void deallocate();
void printLexemas();

#endif
