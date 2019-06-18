# bulid an executable named adventure

adventure: main.o item.o character.o room.o command.o
	g++ -o adventure main.o item.o character.o room.o command.o

main.o: main.cpp
	g++ -c main.cpp

item.o: item.cpp item.h
	g++ -c item.cpp

character.o: character.cpp character.h
	g++ -c character.cpp

room.o:  room.cpp room.h
	g++ -c room.cpp

command.o: command.cpp command.h
	g++ -c command.cpp

all: adventure

clean:
	rm -f adventure main.o item.o character.o room.o command.o
