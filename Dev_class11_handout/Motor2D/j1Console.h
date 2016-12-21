#ifndef _J1CONSOLE_H_
#define _J1CONSOLE_H_

#include "j1Module.h"

class j1Console : public j1Module
{
public:

	j1Console();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool Update();
	bool CleanUp();

public:


};



#endif
