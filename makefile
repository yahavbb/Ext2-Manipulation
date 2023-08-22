CC = gcc
CFLAGS = -Wall -Wextra -pedantic

SOURCES = ext2.c
HEADERS = ext2.h ext2_structs.h
EXECUTABLE = ext2_tool

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

clean:
	rm -f $(EXECUTABLE)