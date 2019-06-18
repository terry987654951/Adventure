#ifndef character_h
#define character_h

#include <string>
#include <iostream>
#include <list>

#include "room.h"
using namespace std;

class Item;
class Room;

typedef list<Item*> LISTITEM;

class Charactor {
protected:
    int       hp, power;
    string    name;
    
public:
    // constructor
    Charactor(int ahp, int apower, string aname)
    {
        hp = ahp;
        power = apower;
        name = aname;
    }
    
    // charactor informations
    string     getName();
    int        gethp();
    int        getpwr();
    
    // charactor status
    void    sethp(int newhp);
    void    printme();
    bool    isalive();
};


// subclasses

class Player : public Charactor {
protected:
    Room*       position;
    LISTITEM    package;
    
public:
    
    // constructor
    Player(int hp, int power, string name) : Charactor(hp, power, name) {};
    
    // player status
    void    setpwr(int newpwr);
    void    setPos(Room* pos);
    void    addItem(Item* anitem);
    void    delItem();
    
    // player informations
    string    getName();
    Room*   getPos();
    void    printme();
    
    // player commands
    bool    meet(Room* aroom);
    bool    meet(Charactor* amonster);
    void    moveto(Room* aroom);
    void    pickUp();
    void    fight();
    void    use();
};

class Monster : public Charactor {
public:
    Monster(int hp, int power, string name) : Charactor(hp, power, name) {};
};


// extensions:

class NewPlayer : public Player {
public:
    
    NewPlayer(int hp, int power, string name) : Player(hp, power, name) {};
    
    void drop();
};


#endif /* character_h */
