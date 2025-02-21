CC = gcc
CC_FLAGS = -Wall -Wextra -g -I./include

bin/evalex: *.c tokens/*.c parser/*.c calc/*.c
	$(CC) $(CC_FLAGS) -o $@ $^

clean:
	rm -rf bin/*