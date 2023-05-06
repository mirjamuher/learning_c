CC=clang
CFLAGS=-Wall -Werror -pedantic -g

PROGRAM=program
SOURCES=hash_table.c program.c
HEADERS=hash_table.h

.PHONY: all run clean

all: $(PROGRAM)

$(PROGRAM): $(SOURCES:.c=.o)

run: $(PROGRAM)
	./$(PROGRAM)

clean: 
	rm -f $(PROGRAM) $(SOURCES:.c=.o)
