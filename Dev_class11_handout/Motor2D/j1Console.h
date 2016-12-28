#ifndef _J1CONSOLE_H_
#define _J1CONSOLE_H_

#include "j1Module.h"
#include "UI_Text_Box.h"
#include "p2DynArray.h"
#include "SDL\include\SDL_rect.h"

struct _TTF_Font;
struct UI_String;
struct UI_Scroll;

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
	void Add_Label(const char* new_text);

public:

	SDL_Rect console_screen;
	SDL_Color Background;
	UI_Text_Box* Input_text;

	
	_TTF_Font* Console_font;
	p2DynArray<UI_String*> Labels;

private:
	int height;
	SDL_Texture* Labels_pre_update_phase;
	void Create_texture();

};



#endif
