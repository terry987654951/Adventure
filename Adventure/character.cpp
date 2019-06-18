#include "character.h"

string Charactor::getName()
{
    return name;
}

int Charactor::gethp()
{
    return hp;
}

int Charactor::getpwr()
{
    return power;
}

void Charactor::sethp(int newhp)
{
    hp = newhp;
}

void Charactor::printme()
{
    cout << name << " has hp: " << hp << " power: " << power << endl;
}

bool Charactor::isalive()
{
    return hp > 0;
}

// Player (Charactor)

void Player::setpwr(int newpwr)
{
    this->power = newpwr;
}

void Player::setPos(Room *pos)
{
    position = pos;
}

void Player::addItem(Item *anitem)
{
    package.push_back(anitem);
}

void Player::delItem()
{
    package.pop_front();
}

string Player::getName()
{
    return name;
}

Room* Player::getPos()
{
    return position;
}

bool Player::meet(Room* aroom)
{
    LISTROOM connectionList = position->getConnection();
    LISTROOM::iterator iter = find(connectionList.begin(), connectionList.end(), aroom);
    if (iter != connectionList.end()) {
        return true;
    }
    else {
        return false;
    }
}

bool Player::meet(Charactor* amonster)
{
    LISTCHAR monsterList = position->getMonster();
    LISTCHAR::iterator iter = find(monsterList.begin(), monsterList.end(), amonster);
    if (iter != monsterList.end()) {
        return true;
    }
    else {
        return false;
    }
}

void Player::moveto(Room* aroom)
{
    
    if (this->meet(aroom)) {
        setPos(aroom);
        cout << "you move to " << aroom->getName() << "\n";
        
        Player::printme();
    }
    else {
        cout << position->getName() << " is not connect with " << aroom->getName() << endl;
    }
}

void Player::pickUp()
{
	if (!this->position->getItem().empty()) {
		Item* item;
		item = this->position->getItem().front();
		this->position->delItem();
		addItem(item);
		cout << "You pick up a/an " << item->getName() << " on the floor!\n" << endl;
	}
	else {
		cout << "no useful thing on the floor!\n" << endl;
	}
    
}

void Player::fight()
{
    Charactor* monster;
    if (this->position->getMonster().empty())
    {
        cout << "no monster here!" << "\n";
    }
	else 
	{
		int winHp = (int)this->hp * 0.8;
		monster = this->position->getMonster().front();
		int mTempHp = monster->gethp();
		int pTempHp = this->hp;
		int deltaPower = this->power - monster->getpwr();
		if (deltaPower <= 0) deltaPower = 1;

		while (pTempHp > 0 && mTempHp > 0) {
			mTempHp -= deltaPower * 50;
			cout << "You deal " << deltaPower * 50 << " damage to the monster!\n";

			if (mTempHp <= 0)
			{
				break;
			}

			pTempHp -= 75;
			cout << "The monster deals " << 75 << " damage to you!\n" << endl;
		}
		this->sethp(pTempHp);
		if (this->isalive()) {
			cout << "you win this fight and defeat " << monster->getName() << "\n";
			this->position->delChars();
			//if player win, reset his hp
			if ((int)winHp > pTempHp) this->sethp(winHp);
		}
		else cout << monster->getName() << " defeats you!\n" << endl;
	}
}

void Player::use()
{
    Item* item;
    if (!package.empty()) {
        item = package.front();
        item->beUsed(this);
        delItem();
    }
    else {
        cout << "your package is empty!" << endl;
    }
}

void Player::printme()
{
    cout << "\n" << name << " has hp: " << hp << " power: " << power
    << "\nstands in: " << this->position->getName() << "\nBag: ";
    
    if (package.empty())
    {
        cout << "nothing\n\n";
    }
    
    else
    {
        for (LISTITEM::iterator iter = package.begin(); iter != package.end(); iter++)
        {
            cout << (*iter)->getName() << " ";
        }
        cout << "\n\n";
    }
    
    this->position->printme();
    
    if (!this->position->getMonster().empty())
    {
        cout << "1st monster: ";
        this->position->getMonster().front()->printme();
    }
}


// New player (extension)

void NewPlayer::drop()
{
    if (!this->package.empty()) {
        this->position->addItem(this->package.front());
		cout << "You drop a/an " << package.front()->getName() << " on the floor!\n" << endl;
        this->delItem();
    }
    else {
        cout <<  "your package is empty!" << endl;
    }
}

