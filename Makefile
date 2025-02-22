CONFIG_DEBUG = -g -O0 -DDEBUG -pedantic -v
CONFIG_RELEASE = -O2 -DNDEBUG

CC = gcc
CC_FLAGS = -Wall -Wextra $(CONFIG_RELEASE)

lib/libevalex.a: lib/calc.o lib/rpn.o lib/tokens.o lib/parser.o
	ar rcs $@ $^
	cp include/evalex.h lib/
	rm -rf $^

lib/calc.o: src/calc.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

lib/rpn.o: src/rpn.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

lib/tokens.o: src/tokens.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

lib/parser.o: src/parser.c
	$(CC) $(CC_FLAGS) -c $^ -o $@

clean:
	rm -rf lib/*