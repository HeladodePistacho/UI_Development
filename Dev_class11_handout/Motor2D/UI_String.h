#ifndef _UI_STRING_H_
#define _UI_STRING_H_

#include "UI_element.h"

struct _TTF_Font;

class UI_String : public UI_element
{
public:
	const char* text;
	int text_size;
	_TTF_Font* text_font;

public:
	UI_String(UI_TYPE type, SDL_Rect detection_box, const char* new_text);
	UI_String(const UI_String* other);

	const char* Get_String() const;
	bool Update_Draw();
};

#endif // ! _UI_STRING_H_

