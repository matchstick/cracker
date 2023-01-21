CC=gcc
CFLAGS=-g
PROGS=cracker
LIBS=

$(PROGS): crack.c
	$(CC) $(CFLAGS) -o $(PROGS) crack.c $(LIBS)

clean:
	rm -r -f $(PROGS) $(PROGS).dSYM/

msg:
	./$(PROGS) -d data/binary_msg.bin

response:
	./$(PROGS) -d data/binary_response.bin

all: $(PROGS)
