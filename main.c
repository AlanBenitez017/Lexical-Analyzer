/***************************************************************
  Student Name: Alan Benitez
  File Name: main.c
  Project 2

  This is the main file where I do the needed calls to run the program
***************************************************************/
#include "lexer.h"
#include "parser.h"
#include "symbol.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  
    fp = fopen(argv[1], "r");
    initSymbolTable();  
    initLexer();
    initRegisters();
    printf("\nCompiling %s\n", argv[1]);
    parse();
    printf("%s\n", buffer);

    char fileName[8] = {0};
    int i = 0;
    while (*(argv[1]) != '.') {
        fileName[i] = *(argv[1]);
        i++;
        argv[1]++;
    }

    sprintf(fileName + strlen(fileName), ".out");
    FILE * outputFile = fopen(fileName, "w");
    fwrite(buffer, sizeof(char), strlen(buffer), outputFile);
    fclose(outputFile);
    return 0;
    
}
