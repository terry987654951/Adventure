//
//  receiver.cpp
//  adventure
//
//  Created by Jing on 6/2/19.
//  Copyright © 2019 cs589-OSU. All rights reserved.
//

#include "receiver.hpp"

#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iostream>
using namespace std;

bool key_received = false;

enum room_type{
    BATTLE = 1,
    CHEST,
    END
} room;


// move
void Receiver::Move()
{
    int input = 0;
    
    while (true) {
        cout << "-----------------------------" << endl;
        cout << "Which room do you want to go?" << endl;
        cout << "1. battle\n2. chest\n3. mysterious door (locked)\n" << endl;
        
        cin >> input;
        
        if (input < BATTLE || input > END)
        {
            cout << "Please input the correct room number." << endl;
            continue;
        }
        
        room = room_type(input);
        break;
    }
}


void Receiver::RoomAction()
{
    switch (room) {
        case BATTLE:
            cout << "You defeated a monster!" << endl;
            
            // 2/3 probability to get the key
            if (rand()%100 >= 33 && key_received == false)
            {
                cout << "* You found a key in the monster! *" << endl;
                key_received = true;
            }
            
            break;
            
        case CHEST:
            cout << "You opened a chest!" << endl;
            
            // 1/3 probability to get the key
            if (rand()%100 <= 33 && key_received == false)
            {
                cout << "* You found a key in the chest! *" << endl;
                key_received = true;
            }
            else
            {
                cout << "But it's empty..." << endl;
            }
            
            break;
            
        case END:
            if (key_received)
            {
                cout << "You escaped! Congratulation!\n" << endl;
                exit(0);
                
            }
            else
            {
                cout << "It seems you need a key to open that door." << endl;
            }
            
            break;
            
            
        default:
            break;
    }
    
    sleep(1);
}



