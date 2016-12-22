#include "j1Console.h"


j1Console::j1Console()
{
	name.create("console");
}

bool j1Console::Awake(pugi::xml_node& config)
{
	return true;
}

bool j1Console::Start()
{
	return true;
}

bool j1Console::Update()
{
	return true;
}

bool j1Console::CleanUp()
{
	return true;
}
