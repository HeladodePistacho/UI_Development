#ifndef _J1CONSOLE_H_
#define _J1CONSOLE_H_

#include "j1Module.h"
#include "UI_Text_Box.h"
#include "SDL\include\SDL_rect.h"

struct _TTF_Font;

class j1Console : public j1Module
{
public:

	j1Console();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	void Active_console();

public:

	SDL_Rect console_screen;
	SDL_Color Background;
	UI_Text_Box* Input_text;
	_TTF_Font* Console_font;

};



#endif
