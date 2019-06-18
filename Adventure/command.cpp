#include "command.h"

// Fight Monster (Command)

void FightMonster::excute()
{
    player->fight();
}


// Move to (Command)

void MoveTo::excute()
{
    player->moveto(room);
}


// Pick up (Command)

void Pickup::excute()
{
    player->pickUp();
}


// Use (Command)

void Use::excute()
{
    player->use();
}


// My Status (Command)

void MyStatus::excute()
{
    player->printme();
}


// Help (Command)

void Help::excute()
{
    helpme->printCmdList();
}


// Help Info

void HelpInfo::printCmdList()
{
	cout << "comamnd list" << endl;
	cout << "M/m: go to input where you want to move\n" 
		<< "U/u: use the first thing in you package\n"
		<< "F/f: fight with the first monster in the room\n" 
		<< "P/p: pick up one item in the room\n" 
		<< "D/d: drop one item in the room\n"
		<< "H/h: check help information\n" 
		<< "S/s: check your status\n"
		<< "Q/q: end the game\n" << endl;
}


// Drop (Command) (extension)

void Drop::excute()
{
    player->drop();
}
