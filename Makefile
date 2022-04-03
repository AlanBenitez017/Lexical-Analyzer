#Alan Benitez
main: main.o symbol.o parser.o lexer.o
		gcc -Wall -o $@ $^
main.o: main.c
		gcc -Wall -c main.c
symbol.o: symbol.h symbol.c
		gcc -Wall -c symbol.c
parser.o: parser.h parser.c
		gcc -Wall -c parser.c
lexer.o: lexer.h lexer.c
		gcc -Wall -c lexer.c
clean:
	rm -rf *.dSYM
	$(RM) *.out *.o *.gc* test/*.o core main

