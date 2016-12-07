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
	uint cursor_pos = 0;

public:

	UI_Text_Box(UI_TYPE type, SDL_Rect detection_box, const char* new_text, const UI_Image& start_image, bool active = true, bool draggable = true);
	UI_Text_Box(const UI_Text_Box* other);

	bool Update();
	bool Update_Draw();

};



#endif // !_UI_TEXT_BOX_H_

