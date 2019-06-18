#ifndef command_h
#define command_h

#include "character.h"
#include "room.h"

class Command {
public:
    virtual void excute() = 0;
};


// subclasses
// concrete commands

class FightMonster : public Command {
    
private:
    
    Player* player;
    
    
public:
    
    FightMonster(Player* aplayer) : Command()
    {
        player = aplayer;
    }
    
    virtual void excute();
};

class MoveTo :public Command {
    
private:
    
    Player* player;
    Room* room;
    
    
public:
    
    MoveTo(Player* aplayer, Room* aroom) {
        player = aplayer;
        room = aroom;
    }
    
    virtual void excute();
};

class Pickup : public Command {
    
private:
    
    Player* player;
    
    
public:
    
    Pickup(Player* aplayer)
    {
        player = aplayer;
    }
    
    virtual void excute();
};

class Use : public Command {
    
private:
    
    Player* player;
    
public:
    
    Use(Player* aplayer)
    {
        player = aplayer;
    }
    
    virtual void excute();
};

class MyStatus : public Command {
    
private:
    
    Player* player;
    
public:
    
    MyStatus(Player* aplayer)
    {
        player = aplayer;
    }
    
    virtual void excute();
};


// Help

class HelpInfo {
public:
    void printCmdList();
};


class Help : public Command {
    
private:
    
    HelpInfo* helpme;
    
public:
    
    Help(HelpInfo* help)
    {
        helpme = help;
    }
    
    virtual void excute();
};


// extensions

class Drop: public Command {
    
private:
    
    NewPlayer *player;
    
public:
    
    Drop(NewPlayer *player)
	{
        this->player = player;
    }
    
    virtual void excute();
};

#endif /* command_h */
