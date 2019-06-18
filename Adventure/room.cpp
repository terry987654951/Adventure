#include "room.h"

void Room::setName(string aname)
{
    name = aname;
}

void Room::addRoom(Room *aroom)
{
    roomlist.push_back(aroom);
}

void Room::delRoom()
{
    roomlist.pop_back();
}

void Room::addItem(Item *anitem)
{
    itemlist.push_back(anitem);
}

void Room::delItem()
{
    itemlist.pop_front();
}

void Room::addCharac(Charactor* achar)
{
    charlist.push_back(achar);
}

void Room::delChars()
{
    charlist.pop_front();
}

string Room::getName()
{
    return name;
}

LISTROOM Room::getConnection()
{
    return roomlist;
}

LISTCHAR Room::getMonster()
{
    return charlist;
}

LISTITEM Room::getItem()
{
    return itemlist;
}

void Room::printme()
{
    int counter = 0;
    
    cout << name << " connects with: ";
    if (!roomlist.empty())
    {
        for (LISTROOM::iterator iter = roomlist.begin(); iter != roomlist.end(); iter++)
        {
            counter++;
            if (counter > 1)
            {
                cout << ", ";
            }
            cout << (*iter)->getName();
        }
    }
    
    counter = 0;
    
    if (!itemlist.empty())
    {
        cout << "\n" << name << " has: ";
    for (LISTITEM::iterator iter = itemlist.begin(); iter != itemlist.end(); iter++)
    {
        counter++;
        if (counter > 1)
        {
            cout << ", ";
        }
        cout << (*iter)->getName();
        }
    }
    
    counter = 0;
    
    if (!charlist.empty())
    {
        cout << "\n" << name << " has monster(s): ";
        for (LISTCHAR::iterator iter = charlist.begin(); iter != charlist.end(); iter++)
        {
            counter++;
            if (counter > 1)
            {
                cout << ", ";
            }
            cout << (*iter)->getName();
        }
    }
    cout << "\n------------------------------------------------" << endl;
}

