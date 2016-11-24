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
	UI_String(iPoint pos, UI_TYPE type, const char* new_text);
	const char* Get_String() const;
	bool Update_Draw();
};

#endif // ! _UI_STRING_H_
