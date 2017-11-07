CFLAGS ?= -O3 -pipe -march=native -flto
LDFLAGS ?= -Wl,-O1 -Wl,--as-needed -Wl,-z,now -Wl,-z,relro
PREFIX ?= /usr/local

.PHONY: ALL clean install
OBJECTS = obj/cli.o obj/main.o obj/tictactoe.o
MYFLAGS = -std=c99 -Wall

ALL: tictactoe

tictactoe: $(OBJECTS)
	$(CC) $(CFLAGS) $(MYFLAGS) $(OBJECTS) -o tictactoe $(LDFLAGS)

obj/main.o: src/main.c src/cli.h src/tictactoe.h
	@ mkdir -p obj
	$(CC) $(CFLAGS) $(MYFLAGS) -c src/main.c -o obj/main.o

obj/cli.o: src/cli.c src/cli.h src/tictactoe.h
	@ mkdir -p obj
	$(CC) $(CFLAGS) $(MYFLAGS) -c src/cli.c -o obj/cli.o

obj/tictactoe.o: src/tictactoe.c src/tictactoe.h
	@ mkdir -p obj
	$(CC) $(CFLAGS) $(MYFLAGS) -c src/tictactoe.c -o obj/tictactoe.o

clean:
	$(RM) tictactoe $(OBJECTS)

install:
	install tictactoe $(DESTDIR)/$(PREFIX)/bin/
