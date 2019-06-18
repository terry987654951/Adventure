#ifndef room_h
#define room_h

#include <list>
#include <string>

#include "item.h"
#include "character.h"
using namespace std;

class Room;
class Item;
class Charactor;

typedef list<Item*> LISTITEM;
typedef list<Charactor*> LISTCHAR;
typedef list<Room*> LISTROOM;

class Room {
protected:
    string        name;
    LISTITEM    itemlist;
    LISTCHAR    charlist;
    LISTROOM    roomlist;
public:
    // constructor
    Room() {}
    
    void    setName(string aname);
    
    // room connections
    void    addRoom(Room* aroom);
    void    delRoom();
    
    // room items
    void    addItem(Item* anitem);
    void    delItem();
    
    // room monsters
    void    addCharac(Charactor* achar);
    void    delChars();
    
    // room informations
    string      getName();
    LISTROOM    getConnection();
    LISTCHAR    getMonster();
    LISTITEM    getItem();
    void        printme();
};


#endif /* room_h */
