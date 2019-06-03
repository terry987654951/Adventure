//
//  invoker.hpp
//  adventure
//
//  Created by Jing on 6/2/19.
//  Copyright © 2019 cs589-OSU. All rights reserved.
//

#ifndef invoker_hpp
#define invoker_hpp

#include <stdio.h>
#include <list>
#include "command.hpp"

// command invoker
class Invoker
{
public:
    Invoker();
    void AddCmd(Command *cmd);      // add command
    void DeleteCmd(Command *cmd);   // delete command
    void Notify();                  // perform command
    
private:
    std::list<Command *> m_cmds;    // commands list
};

#endif /* invoker_hpp */
