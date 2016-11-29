#ifndef _UI_INTERACTIVE_STRING_H_
#define _UI_INTERACTIVE_STRING_H_

#include "UI_interactive_element.h"
struct _TTF_Font;

class UI_Interactive_String : public UI_interactive
{
public:
	const char* text;
	int text_size;
	_TTF_Font* text_font;

public:
	UI_Interactive_String(iPoint pos, UI_TYPE type, const char* new_text, SDL_Rect set_box);
	UI_Interactive_String(const UI_Interactive_String* other);

	bool Set_String(const char* new_text);
	const char* Get_String() const;
	bool Update();
	bool Update_Draw();
};

#endif