//
//  invoker.cpp
//  adventure
//
//  Created by Jing on 6/2/19.
//  Copyright © 2019 cs589-OSU. All rights reserved.
//

#include "invoker.hpp"

Invoker::Invoker()
{
    
}

void Invoker::AddCmd(Command *cmd)
{
    m_cmds.push_back(cmd);
}

void Invoker::DeleteCmd(Command *cmd)
{
    m_cmds.remove(cmd);
}

void Invoker::Notify()
{
    std::list<Command *>::iterator it = m_cmds.begin();
    while (it != m_cmds.end()) {
        (*it)->execute();
        ++it;
    }
}
