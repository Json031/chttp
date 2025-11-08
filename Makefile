PREFIX ?= /usr/local
INCDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

SRC = src/chttp.c
OBJ = $(SRC:.c=.o)
LIB = libchttp.a

CFLAGS = -O2 -Wall $(shell pkg-config --cflags libcurl cjson 2>/dev/null)
LDFLAGS = $(shell pkg-config --libs libcurl cjson 2>/dev/null)

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $^

test: all
	gcc -o test test.c $(LIB) $(LDFLAGS)

install: $(LIB)
	mkdir -p $(INCDIR)
	mkdir -p $(LIBDIR)
	cp src/chttp.h $(INCDIR)/
	cp $(LIB) $(LIBDIR)/

clean:
	rm -f $(OBJ) $(LIB) test
