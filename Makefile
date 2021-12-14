CC = gcc
EXE0 = find
EXE1 = findmmin

$.exe:%.o
	$(CC) -o $@ $^

%.o:%.c
	$(CC) -c -o $@ $^

all: $(EXE0) $(EXE1)

clean:
	rm -f *.exe *.o

