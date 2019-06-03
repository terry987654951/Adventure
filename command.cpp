//
//  command.cpp
//  adventure
//
//  Created by Jing on 6/2/19.
//  Copyright © 2019 cs589-OSU. All rights reserved.
//

#include "command.hpp"
#include "receiver.hpp"
#include <iostream>
using namespace std;

Command::Command(Receiver *Receiver)
: m_pReceiver(Receiver)
{
    
}


// character movement
MoveCommand::MoveCommand(Receiver *Receiver)
: Command(Receiver)
{
    
}

void MoveCommand::execute()
{
    m_pReceiver->Move();
}


// room action
RoomActionCommand::RoomActionCommand(Receiver *Receiver)
: Command(Receiver)
{
    
}

void RoomActionCommand::execute()
{
    m_pReceiver->RoomAction();
}
