#include "item.h"

string Item::getName()
{
    return name;
}


// Food (Item)

void Food::beUsed(Player* player)
{
    int effect = player->gethp() + value;
    int a = player->gethp();
    player->sethp(effect);
    int b = player->gethp();
    cout << "you ate " << this->name << "\n";
    if (a > b)
        cout << "hp down! now you have " << player->gethp() << "hp" << endl;
    else
        cout << "hp up! now you have " << player->gethp() << "hp" << endl;
}


// Weapon (Item)

void Weapon::beUsed(Player *player)
{
    int effect = player->getpwr() + value;
    player->setpwr(effect);
    cout << "you equipped " << this->name << "\n";
    cout << "power up! now you have " << player->getpwr() << "power" << endl;
}

