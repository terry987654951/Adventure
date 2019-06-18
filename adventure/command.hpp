//
//  command.hpp
//  adventure
//
//  Created by Jing on 6/2/19.
//  Copyright © 2019 cs589-OSU. All rights reserved.
//

#ifndef command_hpp
#define command_hpp

#include <stdio.h>

class Receiver;

// the interface for performing the command
class Command
{
public:
    Command(Receiver *Receiver);
    virtual void execute() = 0;
protected:
    Receiver *m_pReceiver;
};


// move command
class MoveCommand : public Command
{
public:
    MoveCommand(Receiver *Receiver);
    void execute();
};


// room action command
class RoomActionCommand : public Command
{
public:
    RoomActionCommand(Receiver *Receiver);
    void execute();
};

#endif /* command_hpp */
