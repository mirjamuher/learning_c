CC=clang
CFLAGS=-Wall -Werror -pedantic

PROGRAM=program
SOURCES=books.c linked_list.c program.c
HEADERS=books.h linked_list.h

.PHONY: all run

all: $(PROGRAM)

$(PROGRAM): $(SOURCES:.c=.o)

run: $(PROGRAM)
	./$(PROGRAM)
