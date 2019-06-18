#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <type_traits>
#include <cassert>

#include "item.h"
#include "character.h"
#include "room.h"
#include "command.h"

using namespace std;

int roomsNum;

// main functions

void showStory() 
{
	cout <<  "only a clever guy can see this story:\n" 
		<< "You went back to Wuhan, China, for summer vacation, and you heard that your school OSU appears some monsters. So you decide to save your University. You need to go to the place called FINAL, defeating the queen and the king."
		<< endl;
}


Room** initRooms()
{
	roomsNum = 6;

	//declare rooms
	Room* roomA = new Room(), 
		* roomB = new Room(), 
		* roomC = new Room(), 
		* roomD = new Room(), 
		* roomE = new Room(), 
		* roomF = new Room();

	static Room* rooms[] = { roomA, roomB, roomC, roomD, roomE, roomF };

	//creat weapons
	Weapon* weapon1 = new Weapon("Glock17(pistol)", 30);
	Weapon* weapon2 = new Weapon("Yi Tian(sword)", 80);
	Weapon* weapon3 = new Weapon("knife", 10);
	Weapon* weapon4 = new Weapon("Gatling(gun)", 100);
	Weapon* weapon5 = new Weapon("basketball", 5);
	Weapon* weapon6 = new Weapon("Tu Long(sword)", 50);

	//creat foods
	Food* food1 = new Food("apple", 100);
	Food* food2 = new Food("rice", 200);
	Food* food3 = new Food("kung pao chicken", 300);
	Food* food4 = new Food("milk", 125);
	Food* food5 = new Food("rotten beef", -110);
	Food * food6 = new Food("amazing food", 800);

	//creat monsters
	Monster * cat = new Monster(1000, 50, "Cat");
	Monster * dog = new Monster(2000, 70, "Dog");
	Monster * king = new Monster(5000, 120, "King");
	Monster * queen = new Monster(8000, 150, "Queen");

	//init rooms
	roomA->setName("wuhan");
	roomA->addItem(weapon5);
	roomA->addItem(food1);
	roomA->addRoom(roomB);
	roomA->addRoom(roomC);
	roomA->addRoom(roomD);

	roomB->setName("shenzhen");
	roomB->addItem(weapon3);
	roomB->addItem(food3);
	roomB->addItem(food2);
	roomB->addCharac(cat);
	roomB->addRoom(roomA);

	roomC->setName("tainan");
	roomC->addItem(weapon4);
	roomC->addItem(weapon6);
	roomC->addItem(food4);
	roomC->addRoom(roomA);
	roomC->addRoom(roomD);
	roomC->addRoom(roomE);

	roomD->setName("CORVALLIS");
	roomD->addItem(weapon2);
	roomD->addCharac(dog);
	roomD->addRoom(roomA);
	roomD->addRoom(roomC);

	roomE->setName("OSU");
	roomE->addItem(weapon1);
	roomE->addItem(food5);
	roomE->addCharac(cat);
	roomE->addRoom(roomC);
	roomE->addRoom(roomF);

	roomF->setName("final");
	roomF->addItem(weapon4);
	roomF->addItem(food6);
	roomF->addCharac(king);
	roomF->addCharac(queen);
	roomF->addRoom(roomE);

	return rooms;
}


NewPlayer* initPlayer(int hp, int power, const char* name, Room** rooms)
{
	NewPlayer* player = new  NewPlayer(hp, power, name);
	player->setPos(rooms[0]);

	return player;
}


MoveTo** initMovement(NewPlayer* player, Room** rooms)
{
	MoveTo** movements = new MoveTo*[roomsNum];

	for (int i = 0; i < roomsNum; i++)
	{
		MoveTo * movement = new MoveTo(player, rooms[i]);
		movements[i] = movement;
	}

	return movements;
}


// main

int main(){
	// init rooms
	Room** rooms = initRooms();

	// init player
	NewPlayer* player = initPlayer(100, 50, "shuhan", rooms);
	
	// init help info
	HelpInfo* printHelp = new HelpInfo();

	// init fighting command
	FightMonster* fighting = new FightMonster(player);

	// init move command
	MoveTo** movements = initMovement(player, rooms);

	// init other command
	Use* use		= new Use(player);
	MyStatus* info	= new MyStatus(player);
	Pickup* pick	= new Pickup(player);
	Drop* drop		= new Drop(player);
	Help* help		= new Help(printHelp);

	help->excute();
	cout << "----------------------------------------------" << endl;
	showStory();
	info->excute();
	char cmd;

	bool play = true;

	while (play) {
		cout << "please input a command: ";
		cin >> cmd;
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		switch (cmd)
		{
		case 'm':
		case 'M':
		{
			string destination;
			cout << "please input your destination: ";
			cin >> destination;

			for (int i = 0; i < roomsNum; i++)
			{
				Room* room = rooms[i];
				string roomName_lower = room->getName();
				string roomName_upper = room->getName();
				transform(roomName_upper.begin(), roomName_upper.end(), roomName_upper.begin(), ::toupper);

				if (destination == roomName_lower || destination == roomName_upper)
				{
					MoveTo* movement = movements[i];
					movement->excute();
					break;
				}

				if (i == roomsNum)
				{
					cout << "not a valid place!" << endl;
				}
			}
		}
		break;
		case 'd':
		case 'D':
			drop->excute();
			break;
		case 'u':
		case 'U':
			use->excute();
			break;
		case 'p':
		case 'P':
			pick->excute();
			break;
		case 'f':
		case 'F':
			fighting->excute();
			break;
		case 's':
		case 'S':
			info->excute();
			break;
		case 'h':
		case 'H':
			help->excute();
			break;
		case 'q':
		case 'Q':
			play = !play;
			break;
		default:
			cout << "not a valid command!" << endl;
			break;
		}

		if (!player->isalive()) {
			cout << "You're dead. Your University is down! Game end!\n";
			play = false;
		}
		if (player->getPos()->getName() == "final" && player->getPos()->getMonster().empty()) {
			cout << "Congratulations! You save your University!\n";
			play = false;
		}

		cin.ignore(10, '\n');
	}
	cout << "thanks for playing" << endl;

	system("pause");
	return 0;
}
