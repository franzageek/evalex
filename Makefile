CC = gcc
CC_FLAGS = -Wall -Wextra -pedantic -g -I./include

bin/parsexp: *.c tokens/*.c parser/*.c
	$(CC) $(CC_FLAGS) -o $@ $^

clean:
	rm -rf bin/*