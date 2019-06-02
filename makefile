CC = gcc


all: p1 p2
p1: chengyua.buildrooms.c
	$(CC) -o chengyua.buildrooms chengyua.buildrooms.c
	./chengyua.buildrooms
p2: chengyua.adventure.c
	$(CC) -o chengyua.adventure chengyua.adventure.c


run:
	./chengyua.adventure

clean:
	rm -rf chengyua.rooms.*
	rm chengyua.buildrooms chengyua.adventure currentTime.txt
