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
	_TTF_Font* text_font;
	SDL_Texture* text_texture;

public:
	UI_String(UI_TYPE type, SDL_Rect detection_box, char* new_text, bool active = true, bool draggable = true);
	UI_String(const UI_String* other);

	
	bool Set_String(char* new_text);
	
	bool Update();
	bool Update_Draw();
};

#endif // ! _UI_STRING_H_

