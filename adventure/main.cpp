//
//  main.cpp
//  adventure
//
//  Created by Jing on 5/26/19.
//  Copyright © 2019 cs589-OSU. All rights reserved.
//

#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#include "invoker.hpp"
#include "receiver.hpp"
#include "command.hpp"

int main()
{
	srand(int(time(0)));

	Receiver* rev = new Receiver();

	Command* cmd1 = new MoveCommand(rev);
	Command* cmd2 = new RoomActionCommand(rev);

	Invoker inv;

	while (true) {
		inv.AddCmd(cmd1);
		inv.AddCmd(cmd2);
		inv.Notify();
	}

	delete cmd1;
	delete cmd2;
	delete rev;

	return 0;
}
