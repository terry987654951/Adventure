#ifndef item_h
#define item_h

#include <string>

#include "character.h"
using namespace std;

class Player;

class Item {
protected:
    string    name;
    int       value;
    
public:
    // constructor
    Item(string aname, int avalue)
    {
        name = aname;
        value = avalue;
    }
    
    // item informations
    string    getName();
    
    // item status
    virtual void beUsed(Player* aplayer) {}
};


// subclasses

class Food : public Item {
public:
    Food(string aname, int avalue) : Item(aname, avalue) {}
    void beUsed(Player* player);
};

class Weapon : public Item {
public:
    Weapon(string aname, int avalue) : Item(aname, avalue) {}
    void beUsed(Player* player);
};

#endif /* item_h */
