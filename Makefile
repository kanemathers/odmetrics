PROJECT = odmetrics

CFILES := $(wildcard src/*.c)
OFILES := $(CFILES:.c=.o)

INCFLAGS += -I$(shell pwd)/include
LDFLAGS  += -lpthread -ljansson
CFLAGS   += -fPIC -g -pedantic

# extra debug output for development purposes
ifeq ($(DEBUG), 1)
	CFLAGS += -Wall -Wextra -Werror -Wno-unused-parameter
endif

CC ?= gcc

PREFIX 		?= /usr/local
INSTALL_INC  = $(PREFIX)/include
INSTALL_LIB  = $(PREFIX)/lib

$(PROJECT): $(OFILES)
	$(CC) $(OFILES) -shared $(LDFLAGS) -o lib$(PROJECT).so
	ar rcs lib$(PROJECT).a $(OFILES)

.c.o:
	$(CC) $(INCFLAGS) -c $(CFLAGS) $< -o $@

install:
	@mkdir -p $(INSTALL_LIB)
	@mkdir -p $(INSTALL_INC)

	cp -r ./include/* $(INSTALL_INC)

	install lib$(PROJECT).so $(INSTALL_LIB)
	install lib$(PROJECT).a $(INSTALL_LIB)

clean:
	rm lib$(PROJECT).*

docs:
	rm -rf docs
	doxygen $(PROJECT).doxygen
