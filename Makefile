CC = gcc
CC_FLAGS = -Wall -Wextra -pedantic -g

parsexp: *.c tokens/*.c
	$(CC) $(CC_FLAGS) -o $@ $^