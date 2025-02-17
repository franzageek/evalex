CC = gcc
CC_FLAGS = -Wall -Wextra -pedantic -g -I./include

parsexp: *.c tokens/*.c parser/*.c
	$(CC) $(CC_FLAGS) -o $@ $^