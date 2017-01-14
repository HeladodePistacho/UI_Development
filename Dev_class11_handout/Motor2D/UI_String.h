#ifndef _UI_STRING_H_
#define _UI_STRING_H_

#include "UI_element.h"
#include "p2SString.h"

struct _TTF_Font;
struct SDL_Texture;

class UI_String : public UI_element
{
public:
	p2SString text;
	int text_size;
	_TTF_Font* text_font = nullptr;
	SDL_Texture* text_texture;

public:

	UI_String(UI_TYPE, j1Module*);
	UI_String(UI_TYPE type, SDL_Rect detection_box, char* new_text, bool active = true, SCROLL_TYPE draggable = FREE_SCROLL);
	UI_String(const UI_String* other);

	
	bool Set_String(char* new_text);
	void Load_text_texture();
	
	bool Update();
	bool Update_Draw();
	bool Handle_input();
	
	bool Draw_console(int height);


};

#endif // ! _UI_STRING_H_

