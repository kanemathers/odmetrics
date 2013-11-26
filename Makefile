PROJECT=rts
SOURCES=src/metrics.c \
		src/server.c \
		src/rts.c
INCFLAGS=-I$(shell pwd)/include
CFLAGS=-Wall \
		-Wextra \
		-Werror \
		-Wno-unused-parameter \
		-pedantic
LDFLAGS=-lpthread -ljansson
OFILES=$(SOURCES:.c=.o)
CC=gcc

.PHONY: clean $(PROJECT)

$(PROJECT): $(OFILES)
	$(CC) $(OFILES) $(LDFLAGS) -o $(PROJECT)

.c.o:
	$(CC) $(INCFLAGS) -c $(CFLAGS) $< -o $@

clean:
	rm $(PROJECT)
