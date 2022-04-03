/***************************************************************
  Student Name: Alan Benitez
  File Name: parser.h
  Project 2

  This is the header file where I declare the variables needed for the parser.c file
***************************************************************/
#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "symbol.h"
#include <stdio.h>

int registerr;
char * operatorr;
char buffer[1000];
char variables[600][600];
int variablesNum;

void printPostfix();
void initRegisters();
void process();
void declaration();
void variable();



void parse();
void assignmentStatement();
void expression();
void term();
void factor();
void match(int id);

#endif
