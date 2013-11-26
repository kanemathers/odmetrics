PROJECT=odmetrics
SOURCES=src/metrics.c \
		src/server.c \
		src/odm.c
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

docs:
	rm -rf docs
	doxygen $(PROJECT).doxygen

clean:
	rm $(PROJECT)
