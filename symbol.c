/***************************************************************
  Student Name: Alan Benitez
  File Name: symbol.c
  Project 2

  In this file I implement a linked list used to do the symbol table.
  Furthermore, I insert values to the symbol table, print the content of it,
  and look into the symbol table if the values passed are in the table.

***************************************************************/
#include "symbol.h"

//Will initialize the symbol table, inserting an element to the linked list
void initSymbolTable() {
  insertToTable(".", 0, 0);
}

//Will insert the lexemas in the symbol table
int insertToTable(char * lexema, int line, int idSize) {
  newInsertion = (node_t *)malloc(sizeof(node_t));
  tokenType = getTokenType(lexema, line, idSize);
  strncpy(newInsertion->value, lexema, sizeof(newInsertion->value) - 1);
  newInsertion->data = tokenType;
  newInsertion->next = NULL;
  newInsertion->line = line;

  if (head != NULL) {
    node_t * lastEntry = head;
    while (lastEntry->next != NULL) {
      lastEntry = lastEntry->next;
    }
    lastEntry->next = newInsertion;
  } else {
    head = newInsertion;
  }
  return tokenType;
}




//Will lookup if the lexema is in the symbol table
bool lookup(char * lexeme) {
    node_t * current = head;
    while (strcmp(current->value, lexeme) != 0) {
        if (current->next != NULL) {
            current = current->next;
        } else {
            return false;
        }
    }
    return true;
}

//Will print the linked list
void printLexemas() {
  node_t * current = head;
  while (current != NULL) {
    if (current->data == ID) {
      if (current->next->next == NULL)
        printf("%s\n", current->value);
      else
        printf("%s, ", current->value);
    }
    current = current->next;
  }
}

//Helper method that will return the token type
int getTokenType(char * lexeme, int line, int idSize) {
	if (strcmp(lexeme, ".") == 0) {
 		return 0;
	}
    if (strcmp(lexeme, "begin") == 0) {
        return BEGIN;
    } else if (strcmp(lexeme, "end.") == 0) {
        return END;
    } else if (lexeme[0] == '_') {
        return UNDERSCORE_FRONT;
    } else if (lexeme[idSize - 1] == '_') {
        return UNDERSCORE_LAST;
    } else if(strcmp(lexeme, "int") == 0){
        return INT;
    } else {
        for (int i = 0; i < MAX - 1; i++) {
            if (lexeme[i] == '_' && lexeme[i + 1] == '_') {
                return UNDERSCORE_SEQUENCE;
            }
        }
    }

    return ID;
}

//Will deallocate the space allocated
void deallocate() {
  node_t * temp = head;
  node_t * tempNext;

  while (temp != NULL) {
    tempNext = temp->next;
    free(temp);
    temp = tempNext;
  }
  head = NULL;
}
