CC=gcc
CFLAGS=-g
PROGS=cracker
LIBS=

$(PROGS): crack.c
	$(CC) $(CFLAGS) -o $(PROGS) crack.c $(LIBS)

clean:
	rm -r -f $(PROGS) $(PROGS).dSYM/

decrypt:
	./$(PROGS) -d data/binary_msg.bin

all: $(PROGS)
