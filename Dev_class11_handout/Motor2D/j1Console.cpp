#include "j1Console.h"


j1Console::j1Console()
{
	name.create("console");
}

bool j1Console::Awake(pugi::xml_node& config)
{
	return false;
}
