#ifndef _UI_TEXT_BOX_H_
#define _UI_TEXT_BOX_H_

#include "UI_element.h"
#include "UI_Image.h"
#include "UI_String.h"

class UI_Text_Box : public UI_element
{
public:

	UI_String text;
	UI_Image background;
	int cursor_pos, height;
	int cursor_virtual_pos;

public:

	UI_Text_Box(UI_TYPE type, SDL_Rect detection_box, char* new_text, const UI_Image& start_image, bool active = true, bool draggable = true);
	UI_Text_Box(const UI_Text_Box* other);

	void text_box_state();

	bool Update();
	bool Handle_input();
	bool Update_Draw();

	const char* get_string_pos(int cursor_pos);
};



#endif // !_UI_TEXT_BOX_H_

